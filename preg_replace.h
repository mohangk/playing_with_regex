#ifndef _preg_replace_h
#define _preg_replace_h

#define PCRE2_CODE_UNIT_WIDTH 8
#include <pcre2.h>

pcre2_code *compile(char *pattern);
char *preg_replace(pcre2_code *pattern, char *replacement, char *subject);

#endif
