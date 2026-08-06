#ifndef _DLTX_READER_PRIVATE_HEADER
#define _DLTX_READER_PRIVATE_HEADER

#include "dltx.h"

DLTX_RETURN_CODE dltx_parser_init(void);
void dltx_parser_cleanup(void);

DLTX_RETURN_CODE dltx_parser_parse_file(DLTX *dltx, const char filename[]);
DLTX_RETURN_CODE dltx_parser_parse_buffer(DLTX *dltx, char buffer[], size_t buffer_size);

#endif //_DLTX_READER_PRIVATE_HEADER
