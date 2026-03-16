#ifndef _LTX_READER_PRIVATE_HEADER
#define _LTX_READER_PRIVATE_HEADER

#include "ltx.h"

LTX_RETURN_CODE ltx_reader_init(void);
void ltx_reader_cleanup(void);

LTX_RETURN_CODE ltx_reader_parse_file(LTX*, const char[]);

#endif //_LTX_READER_PRIVATE_HEADER
