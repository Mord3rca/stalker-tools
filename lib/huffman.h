#ifndef _HUFFMAN_HEADER
#define _HUFFMAN_HEADER

void huffman_compress(void **dest, size_t *dest_sz, void *src, size_t src_sz);
void huffman_decompress(void **dest, size_t *dest_sz, void *src, size_t src_sz);

#endif  // _HUFFMAN_HEADER
