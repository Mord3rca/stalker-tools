#ifndef _DLTX_READER_PRIVATE_HEADER
#define _DLTX_READER_PRIVATE_HEADER

#include "dltx.h"

DLTX_RETURN_CODE dltx_parser_init(void);
void dltx_parser_cleanup(void);

DLTX_RETURN_CODE dltx_parser_parse_file(DLTX*, const char[]);
DLTX_RETURN_CODE dltx_parser_parse_buffer(DLTX*, char[], size_t);

#endif //_DLTX_READER_PRIVATE_HEADER
