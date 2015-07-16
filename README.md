# Regex performance benchmark between C, PHP5, PHP7 and HHVM3.8
## Introduction

Ini bermula dengan niat saya untuk mempelajari library regex dalam bahasa C. Dalam proses itu saya cuba mengimplementasi semula sebuah class kecil yang ada diapplikasi kita kedalam bahasa C untuk membandingkan peformance code C saya, HHVM 3.8, PHP7 dan PHP5. Code C saya kemungkinan besar tidak begitu optimal karena pengetahuan C saya masih basic. 

Namun menjadi harapan saya hasil experimen ini mungkin menarik bagi kalian.

## Code
Saya menulis sebuah class yang kecil yang bernama TextCleanser. Kelas ini bisa digunakan untuk membuang character tertentu dari satu string. 

Versi PHP bisa dilihat disini [TextCleanser.php](http://github.com/mohangk/playing_with_regex/blob/master/TextCleanser.php)

Versi C bisa dilihat disini [text_cleanser.c](https://github.com/mohangk/playing_with_regex/blob/master/text_cleanser.c)

Kedua-duanya berfungsi persis sama. Apabila diberi string seperti 

<pre>
Given =&gt; test L'oreal `` "test" ' *hoho*"
Result=&gt; test Loreal  test  hoho
</pre>

Saya juga menulis test runner untuk [PHP](http://github.com/mohangk/playing_with_regex/blob/master/TextCleanserTest.php) dan [C](https://github.com/mohangk/playing_with_regex/blob/master/test_text_cleanser.c) yang mengetest kedua-dua implementasi text cleanser ini dengan sebelas string tertentu dan bisa menjalankan-nya didalam loop yand ditentukan berdasarkan command-line parameter yang diberi.

### Version information

Kesemua test ini dijalankan didalam VM Ubuntu 14.04. Untuk semua kasus, test diloop sebanyak 1,000,000 kali dan diambil hasil rata-rata. 

Untuk versi C, ia dicompile dengan menggunakan gcc (Ubuntu 4.8.2-19ubuntu1) 4.8.2 dan optimization flag -O3. 

Untuk HHVM, versi yang dipakai adalah - HipHop VM 3.8.0 (rel)
Untuk PHP7, versi yang dipakai adalah - PHP 7.0.0beta1
Untuk PHP5, versi yang dipakai adalah - PHP 5.5.9-1ubuntu4.11

Untuk ketiga-tiga PHP5, PHP7 dan HHVM saya menjalankan test ini dengan menggunakan default configuration.


## Hasilnya

### PHP5
<pre>
$ time php5 TextCleanserTest.php 1000000

        Run1       Run2       Run3
real	1m39.198s  1m39.167s  1m38.978s
user	1m38.613s  1m38.444s  1m38.358s
sys	    0m0.028s   0m0.088s   0m0.060s
</pre>

**Average real: 1m39.114s**

### PHP7

<pre>
$ time php7.0 TextCleanserTest.php 1000000
       
        Run1       Run2       Run3
real	0m42.677s  0m43.271s  0m44.700s
user	0m42.429s  0m43.009s  0m44.401s
sys	    0m0.016s   0m0.016s   0m0.024s
</pre>

**Average real: 43.549s**

### C

<pre>
$ time ./test_text_cleanser 1000000
        
        Run1       Run2       Run3
real	0m23.155s  0m22.750s  0m23.131s
user	0m23.029s  0m22.621s  0m22.998s  
sys	    0m0.016s   0m0.004s   0m0.012s
</pre>

**Average real: 23.012s**

### HHVM

<pre>
$ hhvm TextCleanserTest.php 1000000

real	0m22.391s  0m21.950s  0m22.156s
user	0m22.233s  0m21.806s  0m21.995s 
sys	    0m0.016s   0m0.020s   0m0.032s
</pre>

**Average real: 22.166s**

## Kesimpulan

**Final result: HHVM &lt; C &lt; PHP7 &lt; PHP5**

Harus diingat bahawa use case test ini sangat specific dan kemungkinan besar ada yang  bisa menulis kode C yang jauh lebih baik dari kode yang saya tulis untuk test ini. 

Namun secara garis besar ada tiga kesimpulan yang saya rasa boleh diambil:

1. Compiler + runtime sesuatu language memainkan peranan sangat besar dalam menentukan performance language tersebut. Dalam erti kata lain, gak usah bahas sama ada PHP lebih cepat dari Ruby atau Python kalau compiler + runtime bahasa itu tidak diambil kira dalam perbahasan.
1. Compiler yang bisa menghasilkan code JIT seperti HHVM, Java Hotspot Compiler dan compiler berbasis [LLVM](https://en.wikipedia.org/wiki/LLVM) akan bisa menghasilkan kode yang hampir secepat C-code setelah cukup matang.
1. Benchmarking dan performance analisis adalah cukup penting dalam menentukan sama ada usaha yang akan dimasukkan untuk porting sebahagian code kamu ke bahasa yang lebih low level karena performance akan berhasil atau tidak. Daripada tukar language, mungkin lebih baik tukar compiler dan runtime sahaja. 


## Mengulangi eksperimen

Bagi mereka yang mahu mengulangi eksperimen ini, anda boleh ulangi step-nya berikut untuk compile C-codenya di Ubuntu.

 * Download PCRE2 library from SourceForge  http://sourceforge.net/projects/pcre/files/latest/download?source=files
 * Uncompress and install <pre>
$ tar -xvjf pcre2-10.20.tar.bz2
$ ./configure --enable-jit
$ make
$ make install
</pre>
 * Compile test_text_cleanser<pre>
$ git clone git@github.com:mohangk/playing_with_regex.git
$ cd playing_with_regex
$ make
</pre>
 * Kamu seharusnya bisa run ./test_text_cleanser seperti diatas sekarang.


# JOIN US!

**Apakah kamu rasa menggunakan tools seperti HHVM, membuat performance analysis atau menulis C menarik ? Kalau ya, join us! KMKLabs masih ada banyak lowongan kerja yang terbuka. Kamu bisa apply melewati [http://www.kmklabs.com/careers](http://www.kmklabs.com/careers)**