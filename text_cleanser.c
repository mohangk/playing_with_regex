#define PCRE2_STATIC

#define PCRE2_CODE_UNIT_WIDTH 8

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "text_cleanser.h"
#include "preg_replace.h"

char *cleanse(char *subject);

char *cleanse_inbetween_commas(char *subject) {
  static pcre2_code *re0  = NULL;

  if(re0 == NULL) {
    re0 = compile("((?![a-zA-Z]+),(?=[a-zA-Z+]))");
  }

  char *output;
  output = preg_replace(re0, " ", subject);
  free(subject);
  return output;
}

char *cleanse_quotes(char *subject) {
  static pcre2_code *re1  = NULL;

  if(re1 == NULL) {
    re1 = compile("['\"`*]");
  }

  char *output;
  output = preg_replace(re1, "", subject);
  free(subject);
  return output;
}

char *cleanse_brackets(char *subject) {
  static pcre2_code *re2  = NULL;

  if(re2 == NULL) {
    re2 = compile("[\\(\\)\\[\\]\\{\\}]");
  }

  char *output;
  output =  preg_replace(re2, " " , subject);
  free(subject);
  return output;
}

char *cleanse_html_entities(char *subject) {
  static pcre2_code *re3  = NULL;

  if(re3 == NULL) {
    re3 = compile("&#?[a-zA-Z0-9]+;");
  }
  char *output;
  output = preg_replace(re3, " ", subject);
  free(subject);
  return output;
}

char *cleanse_newline_characters(char *subject) {
  static pcre2_code *re4  = NULL;

  if(re4 == NULL) {
    re4 = compile("(\\n|\\x0D)");
  }

  char *output;
  output =  preg_replace(re4, " ", subject);
  free(subject);
  return output;
}


char *cleanse_article_link_markup(char *subject) {
  static pcre2_code *re5  = NULL;

  if(re5 == NULL) {
    re5 = compile("\\[.+?\\]\\(\\d+\\s\\\".*?\\\"\\)");
  }
  char *output;
  output =  preg_replace(re5, "", subject);
  free(subject);
  return output;
}

char *cleanse_non_ascii_characters(char *subject) {
  static pcre2_code *re6  = NULL;

  if(re6 == NULL) {
    re6 = compile("[^\\x00-\\x7F]");
  }
  char *output;
  output = preg_replace(re6, "", subject);
  free(subject);
  return output;
}

char *cleanse_preceding_special_characters(char *subject) {
  static pcre2_code *re7  = NULL;

  if(re7 == NULL) {
    re7 = compile("(^|\\s|\\.\\,)([\\@\\#\\$])+\\b");
  }

  char *output;
  output = preg_replace(re7, " ", subject);
  free(subject);
  return output;
}

char *cleanse_following_special_characters(char *subject) {
  static pcre2_code *re8  = NULL;

  if(re8 == NULL) {
    re8 = compile("\\b([\\!\\?\\%\\.\\,\\:\\;\\/\\$])+(\\Z|\\s|\\.|\\,)");
  }
  char *output;
  output = preg_replace(re8, " ",subject);
  free(subject);
  return output;
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





