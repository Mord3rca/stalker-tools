#ifndef _LTX_READER_PRIVATE_HEADER
#define _LTX_READER_PRIVATE_HEADER

#include "ltx.h"

LTX_RETURN_CODE ltx_parser_init(void);
void ltx_parser_cleanup(void);

LTX_RETURN_CODE ltx_parser_parse_file(LTX*, const char[]);

#endif //_LTX_READER_PRIVATE_HEADER
