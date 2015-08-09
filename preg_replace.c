#define PCRE2_STATIC

#define PCRE2_CODE_UNIT_WIDTH 8

#include <stdio.h>
#include <string.h>
#include <pcre2.h>
#include "uthash/uthash.h"
#include "preg_replace.h"

struct re_cache {
  char *re;
  pcre2_code *compiled_re;
  UT_hash_handle hh;
};

struct re_cache *active_re_cache;

pcre2_code *compile(char *pattern) {

  PCRE2_SPTR pcre2_pattern = (PCRE2_SPTR)pattern;

  pcre2_code *re;
  int errornumber;
  PCRE2_SIZE erroroffset;


  re = pcre2_compile(
    pcre2_pattern,               /* the pattern */
    PCRE2_ZERO_TERMINATED, /* indicates pattern is zero-terminated */
    0,                     /* default options */
    &errornumber,          /* for error number */
    &erroroffset,          /* for error offset */
    NULL);                 /* use default compile context */

  pcre2_jit_compile(re, PCRE2_JIT_COMPLETE);

  if (re == NULL) {
    PCRE2_UCHAR buffer[256];
    pcre2_get_error_message(errornumber, buffer, sizeof(buffer));
    printf("PCRE2 compilation failed at offset %d: %s\n for pattern: %s", (int)erroroffset,
      buffer, pattern);
    exit(1);
  }

  return re;
}

pcre2_code *get_compiled_re(char *re)
{
  struct re_cache *re_cache_item;
  HASH_FIND_STR(active_re_cache, re, re_cache_item);
  if(re_cache_item == NULL) {
    re_cache_item = malloc(sizeof(struct re_cache));
    re_cache_item->re = strndup(re, strlen(re));
    re_cache_item->compiled_re = compile(re_cache_item->re);
    HASH_ADD_KEYPTR(hh, active_re_cache, re_cache_item->re, strlen(re_cache_item->re), re_cache_item);
  }   
  return re_cache_item->compiled_re;
}


char *preg_replace(char *re, char *replacement, char *subject) {
  int rc;
 
  pcre2_code *compiled_re = get_compiled_re(re);

  PCRE2_SPTR pcre2_subject = (PCRE2_SPTR)subject;
  size_t subject_length = strlen((char *)subject);

  PCRE2_SPTR pcre2_replacement = (PCRE2_SPTR)replacement;
  size_t replacement_length = strlen((char *)replacement);

  PCRE2_UCHAR output[256];
  size_t output_length = 256;

  rc = pcre2_substitute(
    compiled_re,
    pcre2_subject,
    subject_length,
    0,
    PCRE2_SUBSTITUTE_GLOBAL,
    NULL,
    NULL,
    pcre2_replacement,
    replacement_length,
    output,
    &output_length
    );


  if (rc < 0) {

    switch(rc) {
      case PCRE2_ERROR_NOMEMORY: 
        printf("Output buffer not large enough\n"); break;
      case PCRE2_ERROR_BADREPLACEMENT:
        printf("Invalid replacement string %s\n", replacement); break;
      default: 
       printf("Unknown error %d \n", rc); break; 
    }

    exit(1);
  }

  return strndup((char *)output, output_length);
}
