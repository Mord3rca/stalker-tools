#include <stdio.h>
//#include <stdlib.h>

#include "dltx.h"

void print_all_key(DLTXSection s, FILE *out) {
	DLTXKey *k;

	for(int i = 0; i < s.keys->size; i++) {
		k = (DLTXKey*)s.keys->arr[i];
#ifdef DLTX_TRACE
		fprintf(
			out, "%8s%-32s = %-32s  ; Defined here %s:%lu\r\n",
			" ", k->name, k->value ? k->value : "", k->file, k->line
		);
#else
		if (k->value && *(k->value) != 0)
			fprintf(out, "%8s%-32s = %s\r\n", " ", k->name, k->value);
		else
			fprintf(out, "%8s%-32s =\r\n", " ", k->name);
#endif
	}
}

void write_section(DLTXSection s, FILE *out) {
	if (out == NULL)
		out = stdout;
#ifdef DLTX_TRACE
	fprintf(out, "[%s]%-72s; Defined here %s:%lu\r\n", s.name, " ", s.file, s.line);
#else
	fprintf(out, "[%s]\r\n", s.name);
#endif
	print_all_key(s, out);
	fprintf(out, " \r\n");
}

int main(int argc, char *argv[]) {
	DLTX *ini;
	DLTX_RETURN_CODE err;

	if (argc < 2) {
		puts("usage: dltx-reader <path/to/file.dltx>");
		return -1;
	}

	if (dltx_init() != NO_ERROR) {
		puts("Failed to init");
		return -1;
	}

	ini = dltx_create_from_file(argv[1], &err);
	if(err != NO_ERROR) {
		puts(dltx_return_code_to_str(err));
		return -err;
	}

	for(int i = 0; i < ini->sections->size; i++)
		write_section(*((DLTXSection*)ini->sections->arr[i]), NULL);

	free_dltx(ini);
	dltx_cleanup();
	return 0;
}
