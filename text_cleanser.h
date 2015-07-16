#define PCRE2_STATIC

#define PCRE2_CODE_UNIT_WIDTH 8

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "preg_replace.h"

char *cleanse(char *subject);

char *cleanse_inbetween_commas(char *subject);
char *cleanse_quotes(char *subject);
char *cleanse_brackets(char *subject);
char *cleanse_html_entities(char *subject);
char *cleanse_newline_characters(char *subject);
char *cleanse(char *subject);
