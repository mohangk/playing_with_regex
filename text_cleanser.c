#define PCRE2_STATIC

#define PCRE2_CODE_UNIT_WIDTH 8

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <string.h>
#include "uthash/uthash.h"
#include "text_cleanser.h"
#include "preg_replace.h"

char *replace(char *re, char *replacement, char *subject) {

  char *output;
  output = preg_replace(re, replacement, subject);
  free(subject);
  return output;

}

char *cleanse_inbetween_commas(char *subject) {
  return replace("((?![a-zA-Z]+),(?=[a-zA-Z+]))", " ", subject);
}

char *cleanse_quotes(char *subject) {
  return replace("['\"`*]", "", subject);
}

char *cleanse_brackets(char *subject) {
  return replace("[\\(\\)\\[\\]\\{\\}]", " " , subject);
}

char *cleanse_html_entities(char *subject) {
  return replace("&#?[a-zA-Z0-9]+;", " ", subject);
}

char *cleanse_newline_characters(char *subject) {
  return replace("(\\n|\\x0D)", " ", subject);
}


char *cleanse_article_link_markup(char *subject) {
  return replace("\\[.+?\\]\\(\\d+\\s\\\".*?\\\"\\)", "", subject);
}

char *cleanse_non_ascii_characters(char *subject) {
  return replace("[^\\x00-\\x7F]", "", subject);
}

char *cleanse_preceding_special_characters(char *subject) {
  return replace("(^|\\s|\\.\\,)([\\@\\#\\$])+\\b", " ", subject);
}

char *cleanse_following_special_characters(char *subject) {
  return replace("\\b([\\!\\?\\%\\.\\,\\:\\;\\/\\$])+(\\Z|\\s|\\.|\\,)", " ",subject);
}

char *cleanse(char *subject) {
  char *input = strdup(subject);

  input = cleanse_non_ascii_characters(input);
  input = cleanse_article_link_markup(input);
  input = cleanse_quotes(input);
  input = cleanse_brackets(input);
  input = cleanse_inbetween_commas(input);
  input = cleanse_html_entities(input);
  input = cleanse_newline_characters(input);
  input = cleanse_preceding_special_characters(input);
  input = cleanse_following_special_characters(input);
  return input;
}





