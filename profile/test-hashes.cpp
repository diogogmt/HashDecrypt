#include "md5.h"
#include <iostream>
#include <cmath>
#include <cstring>
#include <cstdlib>
#include <ctime>


#define T_MASK ((md5_word_t)~0)
#define T1 /* 0xd76aa478 */ (T_MASK ^ 0x28955b87)
#define T2 /* 0xe8c7b756 */ (T_MASK ^ 0x173848a9)
#define T3    0x242070db
#define T4 /* 0xc1bdceee */ (T_MASK ^ 0x3e423111)
#define T5 /* 0xf57c0faf */ (T_MASK ^ 0x0a83f050)
#define T6    0x4787c62a
#define T7 /* 0xa8304613 */ (T_MASK ^ 0x57cfb9ec)
#define T8 /* 0xfd469501 */ (T_MASK ^ 0x02b96afe)
#define T9    0x698098d8
#define T10 /* 0x8b44f7af */ (T_MASK ^ 0x74bb0850)
#define T11 /* 0xffff5bb1 */ (T_MASK ^ 0x0000a44e)
#define T12 /* 0x895cd7be */ (T_MASK ^ 0x76a32841)
#define T13    0x6b901122
#define T14 /* 0xfd987193 */ (T_MASK ^ 0x02678e6c)
#define T15 /* 0xa679438e */ (T_MASK ^ 0x5986bc71)
#define T16    0x49b40821
#define T17 /* 0xf61e2562 */ (T_MASK ^ 0x09e1da9d)
#define T18 /* 0xc040b340 */ (T_MASK ^ 0x3fbf4cbf)
#define T19    0x265e5a51
#define T20 /* 0xe9b6c7aa */ (T_MASK ^ 0x16493855)
#define T21 /* 0xd62f105d */ (T_MASK ^ 0x29d0efa2)
#define T22    0x02441453
#define T23 /* 0xd8a1e681 */ (T_MASK ^ 0x275e197e)
#define T24 /* 0xe7d3fbc8 */ (T_MASK ^ 0x182c0437)
#define T25    0x21e1cde6
#define T26 /* 0xc33707d6 */ (T_MASK ^ 0x3cc8f829)
#define T27 /* 0xf4d50d87 */ (T_MASK ^ 0x0b2af278)
#define T28    0x455a14ed
#define T29 /* 0xa9e3e905 */ (T_MASK ^ 0x561c16fa)
#define T30 /* 0xfcefa3f8 */ (T_MASK ^ 0x03105c07)
#define T31    0x676f02d9
#define T32 /* 0x8d2a4c8a */ (T_MASK ^ 0x72d5b375)
#define T33 /* 0xfffa3942 */ (T_MASK ^ 0x0005c6bd)
#define T34 /* 0x8771f681 */ (T_MASK ^ 0x788e097e)
#define T35    0x6d9d6122
#define T36 /* 0xfde5380c */ (T_MASK ^ 0x021ac7f3)
#define T37 /* 0xa4beea44 */ (T_MASK ^ 0x5b4115bb)
#define T38    0x4bdecfa9
#define T39 /* 0xf6bb4b60 */ (T_MASK ^ 0x0944b49f)
#define T40 /* 0xbebfbc70 */ (T_MASK ^ 0x4140438f)
#define T41    0x289b7ec6
#define T42 /* 0xeaa127fa */ (T_MASK ^ 0x155ed805)
#define T43 /* 0xd4ef3085 */ (T_MASK ^ 0x2b10cf7a)
#define T44    0x04881d05
#define T45 /* 0xd9d4d039 */ (T_MASK ^ 0x262b2fc6)
#define T46 /* 0xe6db99e5 */ (T_MASK ^ 0x1924661a)
#define T47    0x1fa27cf8
#define T48 /* 0xc4ac5665 */ (T_MASK ^ 0x3b53a99a)
#define T49 /* 0xf4292244 */ (T_MASK ^ 0x0bd6ddbb)
#define T50    0x432aff97
#define T51 /* 0xab9423a7 */ (T_MASK ^ 0x546bdc58)
#define T52 /* 0xfc93a039 */ (T_MASK ^ 0x036c5fc6)
#define T53    0x655b59c3
#define T54 /* 0x8f0ccc92 */ (T_MASK ^ 0x70f3336d)
#define T55 /* 0xffeff47d */ (T_MASK ^ 0x00100b82)
#define T56 /* 0x85845dd1 */ (T_MASK ^ 0x7a7ba22e)
#define T57    0x6fa87e4f
#define T58 /* 0xfe2ce6e0 */ (T_MASK ^ 0x01d3191f)
#define T59 /* 0xa3014314 */ (T_MASK ^ 0x5cfebceb)
#define T60    0x4e0811a1
#define T61 /* 0xf7537e82 */ (T_MASK ^ 0x08ac817d)
#define T62 /* 0xbd3af235 */ (T_MASK ^ 0x42c50dca)
#define T63    0x2ad7d2bb
#define T64 /* 0xeb86d391 */ (T_MASK ^ 0x14792c6e)

int do_md5 (const md5_byte_t* word, int index);
void gen_hashes (char** hash_table);
void init (char** hash_table);

#define STR_SIZE 4

int do_md5(const md5_byte_t* word, char* hash) {
  char output[33];
  int di;
  int it;

  md5_byte_t buf[64];
  md5_byte_t digest[16]; 

  md5_word_t t;

  /* Define storage for little-endian or both types of CPUs. */
  const md5_word_t *X; 

  md5_word_t a = 0x67452301;
  md5_word_t b = /*0xefcdab89*/ T_MASK ^ 0x10325476;
  md5_word_t c = /*0x98badcfe*/ T_MASK ^ 0x67452301;
  md5_word_t d = 0x10325476;

  md5_byte_t data_0;
  md5_byte_t data_1;

  if (strlen((char*) word) < 32) {
    data_0 = strlen((char*) word) << 3;
    data_1 = 0;
  } else {
    data_0 = (strlen((char*) word) - 32) << 3;
    data_1 = 1;
  }

  memcpy(buf, word, strlen((char*)word));
  // for (it = 0; it < strlen((char*)word); it++) {
  //   buf[it] = word[it];
  // }
  //

  memset(buf + strlen((char*)word), 0x80, 1);
  // it = strlen((char*)word);
  // buf[it] = 0x80;
  //

  // This memset is causing a segmentation fault when string with more than 55 bytes are hashed
  // memset(buf + strlen((char*)word) + 1, 0, 55 - strlen((char*) word));
  for (it = strlen((char*)word) + 1; it < 56; it++) {
    buf[it] = 0;
  }
  //

  buf[56] = data_0;
  buf[57] = data_1;
  memset(buf + 58, 0, 6);
  // for (it = 58; it < 64; it++) {
  //   buf[it] = 0;
  // }
  //

  /*
   * Determine dynamically whether this is a big-endian or
   * little-endian machine, since we can use a more efficient
   * algorithm on the latter.
   */
  
  /* data are properly aligned */
  X = (const md5_word_t *)buf;


  /* Round 1. */
  /* Let [abcd k s i] denote the operation
     a = b + ((a + F(b,c,d) + X[k] + T[i]) <<< s).
  */
  /* Do the following 16 operations. */
  // Set 1
  // SET(a, b, c, d,  0,  7,   T1);
  t = a + ((b & c) | (~b & d)) + X[0] + T1;
  a = ((t << 7) | (t >> (32 - 7))) + b;
  // SET(d, a, b, c,  1,   12,  T2);
  t = d + ((a & b) | (~a & c)) + X[1] + T2;
  d = ((t << 12) | (t >> (32 - 12))) + a;
  // SET(c, d, a, b,  2,  17,   T3);
  t = c + ((d & a) | (~d & b)) + X[2] + T3;
  c = ((t << 17) | (t >> (32 - 17))) + d;
  // SET(b, c, d, a,  3,   22,  T4);
  t = b + ((c & d) | (~c & a)) + X[3] + T4;
  b = ((t << 22) | (t >> (32 - 22))) + c;

  // Set 2
  // SET(a, b, c, d,  4,  7,  T5);
  t = a + ((b & c) | (~b & d)) + X[4] + T5;
  a = ((t << 7) | (t >> (32 - 7))) + b;
  // SET(d, a, b, c,  5, 12,  T6);
  t = d + ((a & b) | (~a & c)) + X[5] + T6;
  d = ((t << 12) | (t >> (32 - 12))) + a;
  // SET(c, d, a, b,  6, 17,  T7);
  t = c + ((d & a) | (~d & b)) + X[6] + T7;
  c = ((t << 17) | (t >> (32 - 17))) + d;
  // SET(b, c, d, a,  7, 22,  T8);
  t = b + ((c & d) | (~c & a)) + X[7] + T8;
  b = ((t << 22) | (t >> (32 - 22))) + c;

  // Set 3
  // SET(a, b, c, d,  8,  7,  T9);
  t = a + ((b & c) | (~b & d)) + X[8] + T9;
  a = ((t << 7) | (t >> (32 - 7))) + b;
  // SET(d, a, b, c,  9, 12, T10);
  t = d + ((a & b) | (~a & c)) + X[9] + T10;
  d = ((t << 12) | (t >> (32 - 12))) + a;
  // SET(c, d, a, b, 10, 17, T11);
  t = c + ((d & a) | (~d & b)) + X[10] + T11;
  c = ((t << 17) | (t >> (32 - 17))) + d;
  // SET(b, c, d, a, 11, 22, T12);
  t = b + ((c & d) | (~c & a)) + X[11] + T12;
  b = ((t << 22) | (t >> (32 - 22))) + c;

  // Set 4
  // SET(a, b, c, d, 12,  7, T13);
  t = a + ((b & c) | (~b & d)) + X[12] + T13;
  a = ((t << 7) | (t >> (32 - 7))) + b;
  // SET(d, a, b, c, 13, 12, T14);
  t = d + ((a & b) | (~a & c)) + X[13] + T14;
  d = ((t << 12) | (t >> (32 - 12))) + a;
  // SET(c, d, a, b, 14, 17, T15);
  t = c + ((d & a) | (~d & b)) + X[14] + T15;
  c = ((t << 17) | (t >> (32 - 17))) + d;
  // SET(b, c, d, a, 15, 22, T16);
  t = b + ((c & d) | (~c & a)) + X[15] + T16;
  b = ((t << 22) | (t >> (32 - 22))) + c;



  /* Round 2. */
  /* Let [abcd k s i] denote the operation
     a = b + ((a + G(b,c,d) + X[k] + T[i]) <<< s).
  */
  /* Do the following 16 operations. */
  // Set 1
  // SET(a, b, c, d,  1,  5, T17);
  t = a + ((b & d) | (c & ~d)) + X[1] + T17;
  a = ((t << 5) | (t >> (32 - 5))) + b;
  // SET(d, a, b, c,  6,  9, T18);
  t = d + ((a & c) | (b & ~c)) + X[6] + T18;
  d = ((t << 9) | (t >> (32 - 9))) + a;
  // SET(c, d, a, b, 11,  14,  T19);
  t = c + ((d & b) | (a & ~b)) + X[11] + T19;
  c = ((t << 14) | (t >> (32 - 14))) + d;
  // SET(b, c, d, a,  0,  20,  T20);
  t = b + ((c & a) | (d & ~a)) + X[0] + T20;
  b = ((t << 20) | (t >> (32 - 20))) + c;

  // Set 2
  // SET(a, b, c, d,  5,  5, T21);
  t = a + ((b & d) | (c & ~d)) + X[5] + T21;
  a = ((t << 5) | (t >> (32 - 5))) + b;
  // SET(d, a, b, c, 10,  9, T22);
  t = d + ((a & c) | (b & ~c)) + X[10] + T22;
  d = ((t << 9) | (t >> (32 - 9))) + a;
  // SET(c, d, a, b, 15, 14, T23);
  t = c + ((d & b) | (a & ~b)) + X[15] + T23;
  c = ((t << 14) | (t >> (32 - 14))) + d;
  // SET(b, c, d, a,  4, 20, T24);
  t = b + ((c & a) | (d & ~a)) + X[4] + T24;
  b = ((t << 20) | (t >> (32 - 20))) + c;

  // Set 3
  // SET(a, b, c, d,  9,  5, T25);
  t = a + ((b & d) | (c & ~d)) + X[9] + T25;
  a = ((t << 5) | (t >> (32 - 5))) + b;
  // SET(d, a, b, c, 14,  9, T26);
  t = d + ((a & c) | (b & ~c)) + X[14] + T26;
  d = ((t << 9) | (t >> (32 - 9))) + a;
  // SET(c, d, a, b,  3, 14, T27);
  t = c + ((d & b) | (a & ~b)) + X[3] + T27;
  c = ((t << 14) | (t >> (32 - 14))) + d;
  // SET(b, c, d, a,  8, 20, T28);
  t = b + ((c & a) | (d & ~a)) + X[8] + T28;
  b = ((t << 20) | (t >> (32 - 20))) + c;

  // Set 4
  // SET(a, b, c, d, 13,  5, T29);
  t = a + ((b & d) | (c & ~d)) + X[13] + T29;
  a = ((t << 5) | (t >> (32 - 5))) + b;
  // SET(d, a, b, c,  2,  9, T30);
  t = d + ((a & c) | (b & ~c)) + X[2] + T30;
  d = ((t << 9) | (t >> (32 - 9))) + a;
  // SET(c, d, a, b,  7, 14, T31);
  t = c + ((d & b) | (a & ~b)) + X[7] + T31;
  c = ((t << 14) | (t >> (32 - 14))) + d;
  // SET(b, c, d, a, 12, 20, T32);
  t = b + ((c & a) | (d & ~a)) + X[12] + T32;
  b = ((t << 20) | (t >> (32 - 20))) + c;




  /* Round 3. */
  /* Let [abcd k s t] denote the operation
     a = b + ((a + H(b,c,d) + X[k] + T[i]) <<< s).
  */
  /* Do the following 16 operations. */
  // Set 1
  // SET(a, b, c, d,  5,  4, T33);
  t = a + (b ^ c ^ d) + X[5] + T33;
  a = ((t << 4) | (t >> (32 - 4))) + b;
  // SET(d, a, b, c,  8, 11, T34);
  t = d + (a ^ b ^ c) + X[8] + T34;
  d = ((t << 11) | (t >> (32 - 11))) + a;
  // SET(c, d, a, b, 11, 16, T35);
  t = c + (d ^ a ^ b) + X[11] + T35;
  c = ((t << 16) | (t >> (32 - 16))) + d;
  // SET(b, c, d, a, 14, 23, T36);
  t = b + (c ^ d ^ a) + X[14] + T36;
  b = ((t << 23) | (t >> (32 - 23))) + c;

  // Set 2
  // SET(a, b, c, d,  1,  4, T37);
  t = a + (b ^ c ^ d) + X[1] + T37;
  a = ((t << 4) | (t >> (32 - 4))) + b;
  // SET(d, a, b, c,  4, 11, T38);
  t = d + (a ^ b ^ c) + X[4] + T38;
  d = ((t << 11) | (t >> (32 - 11))) + a;
  // SET(c, d, a, b,  7, 16, T39);
  t = c + (d ^ a ^ b) + X[7] + T39;
  c = ((t << 16) | (t >> (32 - 16))) + d;
  // SET(b, c, d, a, 10, 23, T40);
  t = b + (c ^ d ^ a) + X[10] + T40;
  b = ((t << 23) | (t >> (32 - 23))) + c;

  // Set 3
  // SET(a, b, c, d, 13,  4, T41);
  t = a + (b ^ c ^ d) + X[13] + T41;
  a = ((t << 4) | (t >> (32 - 4))) + b;
  // SET(d, a, b, c,  0, 11, T42);
  t = d + (a ^ b ^ c) + X[0] + T42;
  d = ((t << 11) | (t >> (32 - 11))) + a;
  // SET(c, d, a, b,  3, 16, T43);
  t = c + (d ^ a ^ b) + X[3] + T43;
  c = ((t << 16) | (t >> (32 - 16))) + d;
  // SET(b, c, d, a,  6, 23, T44);
  t = b + (c ^ d ^ a) + X[6] + T44;
  b = ((t << 23) | (t >> (32 - 23))) + c;

  // Set 4
  // SET(a, b, c, d,  9,  4, T45);
  t = a + (b ^ c ^ d) + X[9] + T45;
  a = ((t << 4) | (t >> (32 - 4))) + b;
  // SET(d, a, b, c, 12, 11, T46);
  t = d + (a ^ b ^ c) + X[12] + T46;
  d = ((t << 11) | (t >> (32 - 11))) + a;
  // SET(c, d, a, b, 15, 16, T47);
  t = c + (d ^ a ^ b) + X[15] + T47;
  c = ((t << 16) | (t >> (32 - 16))) + d;
  // SET(b, c, d, a,  2, 23, T48);
  t = b + (c ^ d ^ a) + X[2] + T48;
  b = ((t << 23) | (t >> (32 - 23))) + c;




  /* Round 4. */
  /* Let [abcd k s t] denote the operation
     a = b + ((a + I(b,c,d) + X[k] + T[i]) <<< s).
  */
  /* Do the following 16 operations. */
  // Set 1
  // SET(a, b, c, d,  0,  6, T49);
  t = a + (c ^ (b | ~d)) + X[0] + T49;
  a = ((t << 6) | (t >> (32 - 6))) + b;
  // SET(d, a, b, c,  7, 10, T50);
  t = d + (b ^ (a | ~c)) + X[7] + T50;
  d = ((t << 10) | (t >> (32 - 10))) + a;
  // SET(c, d, a, b, 14, 15, T51);
  t = c + (a ^ (d | ~b)) + X[14] + T51;
  c = ((t << 15) | (t >> (32 - 15))) + d;
  // SET(b, c, d, a,  5, 21, T52);
  t = b + (d ^ (c | ~a)) + X[5] + T52;
  b = ((t << 21) | (t >> (32 - 21))) + c;

  // Set 2
  // SET(a, b, c, d, 12,  6, T53);
  t = a + (c ^ (b | ~d)) + X[12] + T53;
  a = ((t << 6) | (t >> (32 - 6))) + b;
  // SET(d, a, b, c,  3, 10, T54);
  t = d + (b ^ (a | ~c)) + X[3] + T54;
  d = ((t << 10) | (t >> (32 - 10))) + a;
  // SET(c, d, a, b, 10, 15, T55);
  t = c + (a ^ (d | ~b)) + X[10] + T55;
  c = ((t << 15) | (t >> (32 - 15))) + d;
  // SET(b, c, d, a,  1, 21, T56);
  t = b + (d ^ (c | ~a)) + X[1] + T56;
  b = ((t << 21) | (t >> (32 - 21))) + c;

  // Set 3
  // SET(a, b, c, d,  8,  6, T57);
  t = a + (c ^ (b | ~d)) + X[8] + T57;
  a = ((t << 6) | (t >> (32 - 6))) + b;
  // SET(d, a, b, c, 15, 10, T58);
  t = d + (b ^ (a | ~c)) + X[15] + T58;
  d = ((t << 10) | (t >> (32 - 10))) + a;
  // SET(c, d, a, b,  6, 15, T59);
  t = c + (a ^ (d | ~b)) + X[6] + T59;
  c = ((t << 15) | (t >> (32 - 15))) + d;
  // SET(b, c, d, a, 13, 21, T60);
  t = b + (d ^ (c | ~a)) + X[13] + T60;
  b = ((t << 21) | (t >> (32 - 21))) + c;

  // Set 4
  // SET(a, b, c, d,  4,  6, T61);
  t = a + (c ^ (b | ~d)) + X[4] + T61;
  a = ((t << 6) | (t >> (32 - 6))) + b;
  // SET(d, a, b, c, 11, 10, T62);
  t = d + (b ^ (a | ~c)) + X[11] + T62;
  d = ((t << 10) | (t >> (32 - 10))) + a;
  // SET(c, d, a, b,  2, 15, T63);
  t = c + (a ^ (d | ~b)) + X[2] + T63;
  c = ((t << 15) | (t >> (32 - 15))) + d;
  // SET(b, c, d, a,  9, 21, T64);
  t = b + (d ^ (c | ~a)) + X[9] + T64;
  b = ((t << 21) | (t >> (32 - 21))) + c;


  /* Then perform the following additions. (That is increment each
     of the four registers by the value it had before this block
     was started.)
  */
  a += 0x67452301;
  b += T_MASK ^ 0x10325476;
  c += T_MASK ^ 0x67452301;
  d += 0x10325476;
  
  digest[0] = (md5_byte_t)(a >> 0);
  digest[1] = (md5_byte_t)(a >> 8);
  digest[2] = (md5_byte_t)(a >> 16);
  digest[3] = (md5_byte_t)(a >> 24);

  digest[4] = (md5_byte_t)(b >> 0);
  digest[5] = (md5_byte_t)(b >> 8);
  digest[6] = (md5_byte_t)(b >> 16);
  digest[7] = (md5_byte_t)(b >> 24);

  digest[8]  = (md5_byte_t)(c >> 0);
  digest[9]  = (md5_byte_t)(c >> 8);
  digest[10] = (md5_byte_t)(c >> 16);
  digest[11] = (md5_byte_t)(c >> 24);

  digest[12] = (md5_byte_t)(d >> 0);
  digest[13] = (md5_byte_t)(d >> 8);
  digest[14] = (md5_byte_t)(d >> 16);
  digest[15] = (md5_byte_t)(d >> 24);


  // digest[i] = (md5_byte_t)(pms->abcd[i >> 2] >> ((i & 3) << 3));

  for (di = 0; di < 16; di++) {
    sprintf(output + di * 2, "%02x", digest[di]); 
  }

  if (strcmp(output, hash)) {
    printf("hash for word(%d) |%s| should be %s but got %s\n\n", (int) strlen((char*) word), word, hash, output);
    return 0;
  }
  // printf("hash: %s\n", output);
  return 1;
}





int main (int argc, char *argv[]) {
  printf("main\n");

  char** hash_table;
  int i;
  hash_table = (char**) malloc(sizeof(char*) * 60);

  for (i = 0; i < 60; i++) {
    hash_table[i] = (char*) malloc(sizeof(char) * 60 + 1);
  } // END loop 0

  init(hash_table);
  gen_hashes(hash_table);

  for (i = 0; i < 60; i++) { 
    free(hash_table[i]);
  }
  free(hash_table);

  return 1;
}



void gen_hashes (char** hash_table) {
  printf("gen_hashes\n");

  md5_byte_t word[61];
  int i, j;
  int fails = 0;

  for (i = 0; i < 60; i++) {
    for (j = 0; j < i; j++) {
      word[j] = (char) 97;
    }
    word[j] = (char) 0;
    printf("\n\ni: %d - word: %s\n", i, word);
    if (!do_md5(word, hash_table[i])) {
      fails++;
    }
  } // END loop 0
  printf("total fails: %d\n", fails);
}


void init (char** hash_table) {
  printf("init\n");

  strcpy(hash_table[0], "d41d8cd98f00b204e9800998ecf8427e"); 

  strcpy(hash_table[1], "0cc175b9c0f1b6a831c399e269772661"); 

  strcpy(hash_table[2], "4124bc0a9335c27f086f24ba207a4912"); 

  strcpy(hash_table[3], "47bce5c74f589f4867dbd57e9ca9f808"); 

  strcpy(hash_table[4], "74b87337454200d4d33f80c4663dc5e5"); 

  strcpy(hash_table[5], "594f803b380a41396ed63dca39503542"); 

  strcpy(hash_table[6], "0b4e7a0e5fe84ad35fb5f95b9ceeac79"); 

  strcpy(hash_table[7], "5d793fc5b00a2348c3fb9ab59e5ca98a"); 

  strcpy(hash_table[8], "3dbe00a167653a1aaee01d93e77e730e"); 

  strcpy(hash_table[9], "552e6a97297c53e592208cf97fbb3b60"); 

  strcpy(hash_table[10], "e09c80c42fda55f9d992e59ca6b3307d"); 

  strcpy(hash_table[11], "d57f21e6a273781dbf8b7657940f3b03"); 

  strcpy(hash_table[12], "45e4812014d83dde5666ebdf5a8ed1ed"); 

  strcpy(hash_table[13], "c162de19c4c3731ca3428769d0cd593d"); 

  strcpy(hash_table[14], "451599a5f9afa91a0f2097040a796f3d"); 

  strcpy(hash_table[15], "12f9cf6998d52dbe773b06f848bb3608"); 

  strcpy(hash_table[16], "23ca472302f49b3ea5592b146a312da0"); 

  strcpy(hash_table[17], "88e42e96cc71151b6e1938a1699b0a27"); 

  strcpy(hash_table[18], "2c60c24e7087e18e45055a33f9a5be91"); 

  strcpy(hash_table[19], "639d76897485360b3147e66e0a8a3d6c"); 

  strcpy(hash_table[20], "22d42eb002cefa81e9ad604ea57bc01d"); 

  strcpy(hash_table[21], "bd049f221af82804c5a2826809337c9b"); 

  strcpy(hash_table[22], "ff49cfac3968dbce26ebe7d4823e58bd"); 

  strcpy(hash_table[23], "d95dbfee231e34cccb8c04444412ed7d"); 

  strcpy(hash_table[24], "40edae4bad0e5bf6d6c2dc5615a86afb"); 

  strcpy(hash_table[25], "a5a8bfa3962f49330227955e24a2e67c"); 

  strcpy(hash_table[26], "ae791f19bdf77357ff10bb6b0e97e121"); 

  strcpy(hash_table[27], "aaab9c59a88bf0bdfcb170546c5459d6"); 

  strcpy(hash_table[28], "b0f0545856af1a340acdedce23c54b97"); 

  strcpy(hash_table[29], "f7ce3d7d44f3342107d884bfa90c966a"); 

  strcpy(hash_table[30], "59e794d45697b360e18ba972bada0123"); 

  strcpy(hash_table[31], "3b0845db57c200be6052466f87b2198a"); 

  strcpy(hash_table[32], "5eca9bd3eb07c006cd43ae48dfde7fd3"); 

  strcpy(hash_table[33], "b4f13cb081e412f44e99742cb128a1a5"); 

  strcpy(hash_table[34], "4c660346451b8cf91ef50f4634458d41"); 

  strcpy(hash_table[35], "11db24dc3f6c2145701db08625dd6d76"); 

  strcpy(hash_table[36], "80dad3aad8584778352c68ab06250327"); 

  strcpy(hash_table[37], "1227fe415e79db47285cb2689c93963f"); 

  strcpy(hash_table[38], "8e084f489f1bdf08c39f98ff6447ce6d"); 

  strcpy(hash_table[39], "08b2f2b0864bac1ba1585043362cbec9"); 

  strcpy(hash_table[40], "4697843037d962f62a5a429e611e0f5f"); 

  strcpy(hash_table[41], "10c4da18575c092b486f8ab96c01c02f"); 

  strcpy(hash_table[42], "af205d729450b663f48b11d839a1c8df"); 

  strcpy(hash_table[43], "0d3f91798fac6ee279ec2485b25f1124"); 

  strcpy(hash_table[44], "4c3c7c067634daec9716a80ea886d123"); 

  strcpy(hash_table[45], "d1e358e6e3b707282cdd06e919f7e08c"); 

  strcpy(hash_table[46], "8c6ded4f0af86e0a7e301f8a716c4363"); 

  strcpy(hash_table[47], "4c2d8bcb02d982d7cb77f649c0a2dea8"); 

  strcpy(hash_table[48], "bdb662f765cd310f2a547cab1cfecef6"); 

  strcpy(hash_table[49], "08ff5f7301d30200ab89169f6afdb7af"); 

  strcpy(hash_table[50], "6eb6a030bcce166534b95bc2ab45d9cf"); 

  strcpy(hash_table[51], "1bb77918e5695c944be02c16ae29b25e"); 

  strcpy(hash_table[52], "b6fe77c19f0f0f4946c761d62585bfea"); 

  strcpy(hash_table[53], "e9e7e260dce84ffa6e0e7eb5fd9d37fc"); 

  strcpy(hash_table[54], "eced9e0b81ef2bba605cbc5e2e76a1d0"); 

  strcpy(hash_table[55], "ef1772b6dff9a122358552954ad0df65"); 

  strcpy(hash_table[56], "3b0c8ac703f828b04c6c197006d17218"); 

  strcpy(hash_table[57], "652b906d60af96844ebd21b674f35e93"); 

  strcpy(hash_table[58], "dc2f2f2462a0d72358b2f99389458606"); 

  strcpy(hash_table[59], "762fc2665994b217c52c3c2eb7d9f406");
}