#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

static unsigned textsize = 0, codesize = 0;

/********** LZSS compression **********/

#define N 4096 /* buffer size */
#define F 60 /* lookahead buffer size */
#define THRESHOLD 2
#define NIL N /* leaf of tree */

#define N_CHAR (256 - THRESHOLD + F) /* kinds of characters (character code = 0..N_CHAR-1) */
#define T (N_CHAR * 2 - 1) /* size of table */
#define R (T - 1) /* position of root */
#define MAX_FREQ 0x4000 /* updates tree when the */


static unsigned char text_buf[N + F];
static int match_position, match_length, lson[N + 1], rson[N + 257], dad[N + 1];

static unsigned code, len;
static unsigned tim_size = 0;

static unsigned freq[T + 1]; /* frequency table */

static int prnt[T + N_CHAR + 1]; /* pointers to parent nodes, except for the */
/* elements [T..T + N_CHAR - 1] which are used to get */
/* the positions of leaves corresponding to the codes. */

static int son[T]; /* pointers to child nodes (son[], son[] + 1) */

struct LZfs
{
	unsigned getbuf;
	unsigned getlen;

	unsigned putbuf;
	unsigned putlen;

	unsigned char *in_start;
	unsigned char *in_end;
	unsigned char *in_iterator;

	unsigned char *out_start;
	unsigned char *out_end;
	unsigned char *out_iterator;
};

static struct LZfs fs;

static inline int _getb()
{
	if (fs.in_iterator == fs.in_end) return EOF;
	return *(fs.in_iterator++);
}

static inline void _putb(int c)
{
	if (fs.out_iterator == fs.out_end)
	{
		uint32_t out_size = (uint32_t)(fs.out_end - fs.out_start);
		fs.out_start = realloc(fs.out_start, out_size + 1024);
		fs.out_iterator = fs.out_start + out_size;
		fs.out_end = fs.out_iterator + 1024;
	}
	*(fs.out_iterator++) = (unsigned char)(c & 0xFF);
}

static inline void Init_Input(unsigned char *_start, unsigned char *_end)
{
	// input
	fs.in_start = _start;
	fs.in_end = _end;
	fs.in_iterator = fs.in_start;

	// bitwise input/output
	fs.getbuf = fs.getlen = fs.putbuf = fs.putlen = 0;
}

static inline void Init_Output(int _rsize)
{
	// output
	fs.out_start = malloc(_rsize);
	fs.out_end = fs.out_start + _rsize;
	fs.out_iterator = fs.out_start;
}

static inline uint32_t InputSize()
{
	return fs.in_end - fs.in_start;
}

static inline uint32_t OutSize()
{
	return fs.out_iterator - fs.out_start;
}

static inline unsigned char *OutPointer()
{
	return fs.out_start;
}

static inline void OutRelease()
{
	free(fs.out_start);
	fs.out_start = 0;
	fs.out_end = 0;
	fs.out_iterator = 0;
}

static inline int GetBit(void) /* get one bit */
{
	unsigned i;

	while (fs.getlen <= 8)
	{
		if ((int)(i = _getb()) < 0) i = 0;
		fs.getbuf |= i << (8 - fs.getlen);
		fs.getlen += 8;
	}
	i = fs.getbuf;
	fs.getbuf <<= 1;
	fs.getlen--;
	return (int)((i & 0x8000) >> 15);
}

static inline int GetByte(void) /* get one byte */
{
	unsigned i;

	while (fs.getlen <= 8)
	{
		if ((int)(i = _getb()) < 0) i = 0;
		fs.getbuf |= i << (8 - fs.getlen);
		fs.getlen += 8;
	}
	i = fs.getbuf;
	fs.getbuf <<= 8;
	fs.getlen -= 8;
	return (int)((i & 0xff00) >> 8);
}

static inline void PutCode(int l, unsigned c) /* output c bits of code */
{
	fs.putbuf |= c >> fs.putlen;
	if ((fs.putlen += l) >= 8)
	{
		_putb(fs.putbuf >> 8);
		if ((fs.putlen -= 8) >= 8)
		{
			_putb(fs.putbuf);
			codesize += 2;
			fs.putlen -= 8;
			fs.putbuf = c << (l - fs.putlen);
		}
		else
		{
			fs.putbuf <<= 8;
			codesize++;
		}
	}
}

static inline void PutFlush()
{
	if (fs.putlen)
	{
		_putb(fs.putbuf >> 8);
		codesize++;
	}
}

static inline void InitTree(void) /* initialize trees */
{
	int i;

	for (i = N + 1; i <= N + 256; i++) rson[i] = NIL; /* root */
	for (i = 0; i < N; i++) dad[i] = NIL; /* node */
}

static void InsertNode(int r) /* insert to tree */
{
	int i, p, cmp;
	unsigned char *key;
	unsigned c;

	cmp = 1;
	key = &text_buf[r];
	p = N + 1 + key[0];
	rson[r] = lson[r] = NIL;
	match_length = 0;
	for (;;)
	{
		if (cmp >= 0)
		{
			if (rson[p] != NIL)
				p = rson[p];
			else
			{
				rson[p] = r;
				dad[r] = p;
				return;
			}
		}
		else
		{
			if (lson[p] != NIL)
				p = lson[p];
			else
			{
				lson[p] = r;
				dad[r] = p;
				return;
			}
		}
		for (i = 1; i < F; i++)
			if ((cmp = key[i] - text_buf[p + i]) != 0)
				break;
		if (i > THRESHOLD)
		{
			if (i > match_length)
			{
				match_position = ((r - p) & (N - 1)) - 1;
				if ((match_length = i) >= F)
					break;
			}
			if (i == match_length)
			{
				if ((c = ((r - p) & (N - 1)) - 1) < (unsigned)match_position)
				{
					match_position = c;
				}
			}
		}
	}
	dad[r] = dad[p];
	lson[r] = lson[p];
	rson[r] = rson[p];
	dad[lson[p]] = r;
	dad[rson[p]] = r;
	if (rson[dad[p]] == p)
		rson[dad[p]] = r;
	else
		lson[dad[p]] = r;
	dad[p] = NIL; /* remove p */
}

static void DeleteNode(int p) /* remove from tree */
{
	int q;

	if (dad[p] == NIL) return; /* not registered */
	if (rson[p] == NIL)
		q = lson[p];
	else
	{
		if (lson[p] == NIL)
		{
			q = rson[p];
		}
		else
		{
			q = lson[p];
			if (rson[q] != NIL)
			{
				do { q = rson[q]; }
				while (rson[q] != NIL);

				rson[dad[q]] = lson[q];
				dad[lson[q]] = dad[q];
				lson[q] = lson[p];
				dad[lson[p]] = q;
			}
			rson[q] = rson[p];
			dad[rson[p]] = q;
		}
	}
	dad[q] = dad[p];
	if (rson[dad[p]] == p)
		rson[dad[p]] = q;
	else
		lson[dad[p]] = q;
	dad[p] = NIL;
}

/* Huffman coding */

/* table for encoding and decoding the upper 6 bits of position */
/* for encoding */
static unsigned char p_len[64] =
{
	0x03, 0x04, 0x04, 0x04, 0x05, 0x05, 0x05, 0x05,
	0x05, 0x05, 0x05, 0x05, 0x06, 0x06, 0x06, 0x06,
	0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06,
	0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07,
	0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07,
	0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07,
	0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08,
	0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08
};

static unsigned char p_code[64] =
{
	0x00, 0x20, 0x30, 0x40, 0x50, 0x58, 0x60, 0x68,
	0x70, 0x78, 0x80, 0x88, 0x90, 0x94, 0x98, 0x9C,
	0xA0, 0xA4, 0xA8, 0xAC, 0xB0, 0xB4, 0xB8, 0xBC,
	0xC0, 0xC2, 0xC4, 0xC6, 0xC8, 0xCA, 0xCC, 0xCE,
	0xD0, 0xD2, 0xD4, 0xD6, 0xD8, 0xDA, 0xDC, 0xDE,
	0xE0, 0xE2, 0xE4, 0xE6, 0xE8, 0xEA, 0xEC, 0xEE,
	0xF0, 0xF1, 0xF2, 0xF3, 0xF4, 0xF5, 0xF6, 0xF7,
	0xF8, 0xF9, 0xFA, 0xFB, 0xFC, 0xFD, 0xFE, 0xFF
};

/* for decoding */
static unsigned char d_code[256] =
{
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
	0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
	0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02,
	0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02,
	0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03,
	0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03,
	0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04,
	0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05,
	0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06,
	0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07,
	0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08,
	0x09, 0x09, 0x09, 0x09, 0x09, 0x09, 0x09, 0x09,
	0x0A, 0x0A, 0x0A, 0x0A, 0x0A, 0x0A, 0x0A, 0x0A,
	0x0B, 0x0B, 0x0B, 0x0B, 0x0B, 0x0B, 0x0B, 0x0B,
	0x0C, 0x0C, 0x0C, 0x0C, 0x0D, 0x0D, 0x0D, 0x0D,
	0x0E, 0x0E, 0x0E, 0x0E, 0x0F, 0x0F, 0x0F, 0x0F,
	0x10, 0x10, 0x10, 0x10, 0x11, 0x11, 0x11, 0x11,
	0x12, 0x12, 0x12, 0x12, 0x13, 0x13, 0x13, 0x13,
	0x14, 0x14, 0x14, 0x14, 0x15, 0x15, 0x15, 0x15,
	0x16, 0x16, 0x16, 0x16, 0x17, 0x17, 0x17, 0x17,
	0x18, 0x18, 0x19, 0x19, 0x1A, 0x1A, 0x1B, 0x1B,
	0x1C, 0x1C, 0x1D, 0x1D, 0x1E, 0x1E, 0x1F, 0x1F,
	0x20, 0x20, 0x21, 0x21, 0x22, 0x22, 0x23, 0x23,
	0x24, 0x24, 0x25, 0x25, 0x26, 0x26, 0x27, 0x27,
	0x28, 0x28, 0x29, 0x29, 0x2A, 0x2A, 0x2B, 0x2B,
	0x2C, 0x2C, 0x2D, 0x2D, 0x2E, 0x2E, 0x2F, 0x2F,
	0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37,
	0x38, 0x39, 0x3A, 0x3B, 0x3C, 0x3D, 0x3E, 0x3F,
};

static unsigned char d_len[256] =
{
	0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03,
	0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03,
	0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03,
	0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03,
	0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04,
	0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04,
	0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04,
	0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04,
	0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04,
	0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04,
	0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05,
	0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05,
	0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05,
	0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05,
	0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05,
	0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05,
	0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05,
	0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05,
	0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06,
	0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06,
	0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06,
	0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06,
	0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06,
	0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06,
	0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07,
	0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07,
	0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07,
	0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07,
	0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07,
	0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07,
	0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08,
	0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08,
};


/* initialization of tree */

static void StartHuff(void)
{
	int i, j;

	for (i = 0; i < N_CHAR; i++)
	{
		freq[i] = 1;
		son[i] = i + T;
		prnt[i + T] = i;
	}
	i = 0;
	j = N_CHAR;
	while (j <= R)
	{
		freq[j] = freq[i] + freq[i + 1];
		son[j] = i;
		prnt[i] = prnt[i + 1] = j;
		i += 2;
		j++;
	}
	freq[T] = 0xffff;
	prnt[R] = 0;
}


/* reconstruction of tree */
static void reconst(void)
{
	int i, j, k;
	unsigned f, l;

	/* collect leaf nodes in the first half of the table */
	/* and replace the freq by (freq + 1) / 2. */
	j = 0;
	for (i = 0; i < T; i++)
	{
		if (son[i] >= T)
		{
			freq[j] = (freq[i] + 1) / 2;
			son[j] = son[i];
			j++;
		}
	}
	/* begin constructing tree by connecting sons */
	for (i = 0, j = N_CHAR; j < T; i += 2, j++)
	{
		k = i + 1;
		f = freq[j] = freq[i] + freq[k];
		for (k = j - 1; f < freq[k]; k--);
		k++;
		l = (j - k) * sizeof(unsigned);
		memmove(&freq[k + 1], &freq[k], l);
		freq[k] = f;
		memmove(&son[k + 1], &son[k], l);
		son[k] = i;
	}
	/* connect prnt */
	for (i = 0; i < T; i++)
	{
		if ((k = son[i]) >= T)
		{
			prnt[k] = i;
		}
		else
		{
			prnt[k] = prnt[k + 1] = i;
		}
	}
}


/* increment frequency of given code by one, and update tree */
static void update(int c)
{
	int i, j, k, l;

	if (freq[R] == MAX_FREQ)
	{
		reconst();
	}
	c = prnt[c + T];
	do
	{
		k = ++freq[c];

		/* if the order is disturbed, exchange nodes */
		if ((unsigned)k > freq[l = c + 1])
		{
			while ((unsigned)k > freq[++l]);
			l--;
			freq[c] = freq[l];
			freq[l] = k;

			i = son[c];
			prnt[i] = l;
			if (i < T) prnt[i + 1] = l;

			j = son[l];
			son[l] = i;

			prnt[j] = c;
			if (j < T) prnt[j + 1] = c;
			son[c] = j;

			c = l;
		}
	}
	while ((c = prnt[c]) != 0); /* repeat up to root */
}

static void EncodeChar(unsigned c)
{
	unsigned i;
	int j, k;

	i = 0;
	j = 0;
	k = prnt[c + T];

	/* travel from leaf to root */
	do
	{
		i >>= 1;

		/* if node's address is odd-numbered, choose bigger brother node */
		if (k & 1) i += 0x8000;

		j++;
		k = prnt[k];
	}
	while (k != R);
	PutCode(j, i);
	code = i;
	len = j;
	update(c);
}

static void EncodePosition(unsigned c)
{
	unsigned i;

	/* output upper 6 bits by table lookup */
	i = c >> 6;
	PutCode(p_len[i], (unsigned)p_code[i] << 8);

	/* output lower 6 bits verbatim */
	PutCode(6, (c & 0x3f) << 10);
}

static int DecodeChar(void)
{
	unsigned c;

	c = son[R];

	/* travel from root to leaf, */
	/* choosing the smaller child node (son[]) if the read bit is 0, */
	/* the bigger (son[]+1} if 1 */
	while (c < T)
	{
		c += GetBit();
		c = son[c];
	}
	c -= T;
	update(c);
	return (int)c;
}

static int DecodePosition(void)
{
	unsigned i, j, c;

	/* recover upper 6 bits from table */
	i = GetByte();
	c = (unsigned)d_code[i] << 6;
	j = d_len[i];

	/* read lower 6 bits verbatim */
	j -= 2;
	while (j--)
	{
		i = (i << 1) + GetBit();
	}
	return (int)(c | (i & 0x3f));
}

/* compression */
static void Encode(void) /* compression */
{
	int i, c, len, r, s, last_match_length;

	textsize = InputSize();
	Init_Output(textsize);
	_putb((textsize & 0xff));
	_putb((textsize & 0xff00) >> 8);
	_putb((textsize & 0xff0000L) >> 16);
	_putb((textsize & 0xff000000L) >> 24);
	if (textsize == 0)
		return;
	textsize = 0; /* rewind and re-read */
	StartHuff();
	InitTree();
	s = 0;
	r = N - F;
	for (i = s; i < r; i++)
		text_buf[i] = 0x20;
	for (len = 0; len < F && (c = _getb()) != EOF; len++)
		text_buf[r + len] = (unsigned char)c;
	textsize = len;
	for (i = 1; i <= F; i++)
		InsertNode(r - i);
	InsertNode(r);
	do
	{
		if (match_length > len)
			match_length = len;
		if (match_length <= THRESHOLD)
		{
			match_length = 1;
			// textsize==56158 - FATAL :(
			EncodeChar(text_buf[r]);
		}
		else
		{
			EncodeChar(255 - THRESHOLD + match_length);
			EncodePosition(match_position);
		}
		last_match_length = match_length;
		for (i = 0; i < last_match_length &&
		     (c = _getb()) != EOF; i++)
		{
			DeleteNode(s);
			text_buf[s] = (unsigned char)c;
			if (s < F - 1)
				text_buf[s + N] = (unsigned char)c;
			s = (s + 1) & (N - 1);
			r = (r + 1) & (N - 1);
			InsertNode(r);
		}
		textsize += i;
		while (i++ < last_match_length)
		{
			DeleteNode(s);
			s = (s + 1) & (N - 1);
			r = (r + 1) & (N - 1);
			if (--len) InsertNode(r);
		}
	}
	while (len > 0);
	PutFlush();
	tim_size = textsize;
}

static void Decode(void) /* recover */
{
	int i, j, k, r, c;
	unsigned int count;

	textsize = (_getb());
	textsize |= (_getb() << 8);
	textsize |= (_getb() << 16);
	textsize |= (_getb() << 24);
	if (textsize == 0) return;

	Init_Output(textsize);

	StartHuff();
	for (i = 0; i < N - F; i++)
		text_buf[i] = 0x20;
	r = N - F;
	for (count = 0; count < textsize;)
	{
		c = DecodeChar();
		if (c < 256)
		{
			_putb(c);
			text_buf[r++] = (unsigned char)c;
			r &= (N - 1);
			count++;
		}
		else
		{
			i = (r - DecodePosition() - 1) & (N - 1);
			j = c - 255 + THRESHOLD;
			for (k = 0; k < j; k++)
			{
				c = text_buf[(i + k) & (N - 1)];
				_putb(c);
				text_buf[r++] = (unsigned char)c;
				r &= (N - 1);
				count++;
			}
		}
	}
	tim_size = count;
}

void huffman_compress(void** dest, size_t *dest_sz, void* src, size_t src_sz)
{
	unsigned char *start = src;
	Init_Input(start, start + src_sz);
	Encode();
	*dest = OutPointer();
	*dest_sz = OutSize();
}

void huffman_decompress(void** dest, size_t* dest_sz, void* src, size_t src_sz)
{
	unsigned char *start = src;
	Init_Input(start, start + src_sz);
	Decode();
	*dest = OutPointer();
	*dest_sz = OutSize();
}
