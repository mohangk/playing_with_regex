#ifndef _preg_replace_h
#define _preg_replace_h

#define PCRE2_CODE_UNIT_WIDTH 8
#include <pcre2.h>

char *preg_replace(char *pattern, char *replacement, char *subject);

#endif
