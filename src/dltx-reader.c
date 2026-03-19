#include <stdio.h>
//#include <stdlib.h>

#include "dltx.h"

void print_all_key(DLTXSection s, FILE *out) {
	char *v;

	for(int i = 0; i < s.keys_size; i++) {
		v = s.keys[i]->value;
		if (v == NULL)
			v = "";
		fprintf(out, "%s = %s\r\n", s.keys[i]->name, v);
	}
}

void write_section(DLTXSection s, FILE *out) {
	if (out == NULL)
		out = stdout;

	fprintf(out, "[%s]\r\n", s.name);
	print_all_key(s, out);
	fprintf(out, "\n");
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

	for(int i = 0; i < ini->sections_size; i++)
		write_section(*ini->sections[i], NULL);

	free_dltx(ini);
	dltx_cleanup();
	return 0;
}
