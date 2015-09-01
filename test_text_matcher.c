#define PCRE2_STATIC

#define PCRE2_CODE_UNIT_WIDTH 8

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "preg_replace.h"
#include <assert.h>


int main(int argc, char **argv)
{

  char *testQuery[11];

  testQuery[0]     = "test abc,def test";
  testQuery[1]     = "test L'oreal `` \"test\" ' *hoho*";
  testQuery[2]     = "test (test1) (test2) ()";
  testQuery[3]     = "test abc, def, ghi";
  testQuery[4]     = "test.(abc @def #g (h [i {j 'k `l";
  testQuery[5]     = "test a) b] c} d! e? f. g' h: i; j% k` test) a";
  testQuery[6]     = "http://www.google.co.id/search";
  testQuery[7]     = "test&nbsp;test123 abc &amp; def";
  testQuery[8]     = "test 123\n234 b\r";
  testQuery[9]     = "test [link text](1234567 \"link title\") abc [link text](1234567 \"\")";
  testQuery[10]    = "‘Tembok China’";


  char **matches = NULL;
  int count = preg_match("(\\w+) (\\w+)", testQuery[0], matches);

  printf("%d matches!", count);

  /* for (int i = 0; i < count; i++) */
  /* { */
  /*   printf("%s",matches[i]); */
  /* } */

  return 0;
}
