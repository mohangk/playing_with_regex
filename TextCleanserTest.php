<?php
include './TextCleanser.php';

$cleanser = new TextCleanser();

$testQuery = array();
$testQuery[0]  = "test abc,def test";
$testQuery[1]  = "test L'oreal `` \"test\" ' *hoho*";
$testQuery[2]  = "test (test1) (test2) ()";
$testQuery[3]  = "test abc, def, ghi";
$testQuery[4]  = "test.(abc @def #g (h [i {j 'k `l";
$testQuery[5]  = "test a) b] c} d! e? f. g' h: i; j% k` test) a";
$testQuery[6]  = "http://www.google.co.id/search";
$testQuery[7]  = "test&nbsp;test123 abc &amp; def";
$testQuery[8]  = "test 123\n234 b\r";
$testQuery[9]  = "test [link text](1234567 \"link title\") abc [link text](1234567 \"\")";
$testQuery[10] = "‘Tembok China’";

for($i=0; $i < $argv[1]; $i++) {
  for($j=0; $j < 11; $j++) {
    $cleanser->cleanse($testQuery[$j]);
  }
}

?>
