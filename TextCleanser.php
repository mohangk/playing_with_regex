<?php

class TextCleanser {

  public function cleanse($str) {

    $str = $this->cleanse_article_link_markup($str);
    $str = $this->cleanse_non_ascii_characters($str);
    $str = $this->cleanse_quotes($str);
    $str = $this->cleanse_brackets($str);
    $str = $this->cleanse_inbetween_commas($str);
    $str = $this->cleanse_html_entities($str);
    $str = $this->cleanse_newline_characters($str);
    $str = $this->cleanse_preceding_and_following_special_characters($str);

    return $str;
  }

  private function cleanse_inbetween_commas($str) {
    return preg_replace('/((?![a-zA-Z+]),(?=[a-zA-Z+]))/', ' ', $str);
  }

  private function cleanse_quotes($str) {
    return preg_replace('/[\'\"\`\*]/', '', $str);
  }

  private function cleanse_brackets($str) {
    return preg_replace('/[\(\)\[\]\{\}]/', ' ' , $str);
  }

  private function cleanse_html_entities($str) {
    return preg_replace("/&#?[a-zA-Z0-9]+;/", ' ',$str);
  }

  private function cleanse_newline_characters($str) {
    return str_ireplace(["\n", "\x0D"], " ", $str);
  }

  private function cleanse_article_link_markup($str) {
    return preg_replace('/\[.+?\]\(\d+\s\".*?\"\)/', "", $str);
  }

  private function cleanse_non_ascii_characters($str) {
    return preg_replace('/[^\x00-\x7F]/', '', $str);
  }

  private function cleanse_preceding_and_following_special_characters($str) {
    // chars to be removed only on beginning of word
    $patterns[] = '/(^|\s|\.\,)([\@\#\$])+\b/';

    // chars to be removed only on end of word
    $patterns[] = '/\b([\!\?\%\.\,\:\;\/\$])+(\Z|\s|\.|\,)/';

    return preg_replace($patterns, ' ', $str);
  }

}
