#include "../libs/md5.h"
#include <iostream>
#include <cmath>
#include <cstring>
#include <cstdlib>
#include <ctime>
#include <cuda_runtime.h>

#include "../libs/cuPrintf.cu"



void create_md5_hash_str (const char *word, char *hash_str);
void break_down_hash (md5_byte_t *hash, char *hash_str);
int hex_to_decimal (char c);


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


#define STR_SIZE 6
// If the string has 4 chars, it has a size of 32 bits
// X is a unsigned int pointer, it points to 32 bit chuncks of data
// X[0] will be the whole 4 byte string
// the byte right after the string has the value 0x80, which was translating to 128 since the first nibble is 0 and the second is 8
// a byte with the second nibble as 8 is the decimal 128 --> 1000 0000
// the formula for X_14 is STR_SIZE << 3 as long the string has less than 32 bytes
// after that the formula is (STR_SIZE - 32) << 3 and X_15 will be 1
// We'll be focusing on string less than 32 bytes for now
#define X_1 128
// #define X_14 (STR_SIZE << 3)
#define X_14 48
#define ZERO 0
__global__ void do_md5(md5_word_t* hash_to_break, md5_byte_t* hash_word, md5_byte_t* ascii_codes,
  char start_loop, char end_loop) {

  char it;
  __shared__ md5_word_t cached_hash[16];
  for (it = 0; it < 4; it++) {
    cached_hash[it] = hash_to_break[it];
  }

  __shared__ md5_byte_t cached_ascii_codes[64];
  for (it = 0; it < 64; it++) {
    cached_ascii_codes[it] = ascii_codes[it];
  }

  md5_word_t a;
  md5_word_t b;
  md5_word_t c;
  md5_word_t d;

  md5_word_t t;

  char word[8];
  word[0] = cached_ascii_codes[threadIdx.x];
  word[6] = 0x80;
  word[7] = 0;
  
  char i_1, i_2, i_3, i_4, i_5;


  char begin_1 = 0 + (8 * threadIdx.y);
  char end_1 = 8 + (8 * threadIdx.y);

  char begin_2 = 0;
  char end_2 = 64;

  char cached_start_loop = start_loop;
  char cached_end_loop = end_loop;

  const md5_word_t *X; 

  // unsigned counter = 0;
  for (i_1 = begin_1; i_1 < end_1; i_1++) {
    word[1] = cached_ascii_codes[i_1];
    for (i_2 = begin_2; i_2 < end_2; i_2++) {
      word[2] = cached_ascii_codes[i_2];
      for (i_3 = 0; i_3 < 64; i_3++) {
        word[3] = cached_ascii_codes[i_3];
        for (i_4 = 0; i_4 < 4; i_4++) {
          word[4] = cached_ascii_codes[i_4];
          for (i_5 = cached_start_loop; i_5 < cached_end_loop; i_5++) {
            word[5] = cached_ascii_codes[i_5];

            // counter++;

            X = (const md5_word_t *)word;
            a = 0x67452301;
            b = /*0xefcdab89*/ T_MASK ^ 0x10325476;
            c = /*0x98badcfe*/ T_MASK ^ 0x67452301;
            d = 0x10325476;
            /* Round 1. */
            /* Let [abcd k s i] denote the operation
               a = b + ((a + F(b,c,d) + X[k] + T[i]) <<< s).
            */
            /* Do the following 16 operations. */
            // Set 1
            t = a + ((b & c) | (~b & d)) + X[0] + T1; a = ((t << 7) | (t >> (32 - 7))) + b;

            t = d + ((a & b) | (~a & c)) + X[1] + T2; d = ((t << 12) | (t >> (32 - 12))) + a;

            t = c + ((d & a) | (~d & b)) + T3; c = ((t << 17) | (t >> (32 - 17))) + d;

            t = b + ((c & d) | (~c & a)) + T4; b = ((t << 22) | (t >> (32 - 22))) + c;

            // Set 2
            t = a + ((b & c) | (~b & d)) + T5; a = ((t << 7) | (t >> (32 - 7))) + b;

            t = d + ((a & b) | (~a & c)) + T6; d = ((t << 12) | (t >> (32 - 12))) + a;

            t = c + ((d & a) | (~d & b)) + T7; c = ((t << 17) | (t >> (32 - 17))) + d;

            t = b + ((c & d) | (~c & a)) + T8; b = ((t << 22) | (t >> (32 - 22))) + c;

            // Set 3
            t = a + ((b & c) | (~b & d)) + T9; a = ((t << 7) | (t >> (32 - 7))) + b;

            t = d + ((a & b) | (~a & c)) + T10; d = ((t << 12) | (t >> (32 - 12))) + a;

            t = c + ((d & a) | (~d & b)) + T11; c = ((t << 17) | (t >> (32 - 17))) + d;

            t = b + ((c & d) | (~c & a)) + T12; b = ((t << 22) | (t >> (32 - 22))) + c;

            // Set 4
            t = a + ((b & c) | (~b & d)) + T13; a = ((t << 7) | (t >> (32 - 7))) + b;

            t = d + ((a & b) | (~a & c)) + T14; d = ((t << 12) | (t >> (32 - 12))) + a;

            t = c + ((d & a) | (~d & b)) + X_14 + T15; c = ((t << 17) | (t >> (32 - 17))) + d;

            t = b + ((c & d) | (~c & a)) + T16; b = ((t << 22) | (t >> (32 - 22))) + c;



            /* Round 2. */
            /* Let [abcd k s i] denote the operation
               a = b + ((a + G(b,c,d) + X[k] + T[i]) <<< s).
            */
            /* Do the following 16 operations. */
            // Set 1
            t = a + ((b & d) | (c & ~d)) + X[1] + T17; a = ((t << 5) | (t >> (32 - 5))) + b;

            t = d + ((a & c) | (b & ~c)) + T18; d = ((t << 9) | (t >> (32 - 9))) + a;

            t = c + ((d & b) | (a & ~b)) + T19; c = ((t << 14) | (t >> (32 - 14))) + d;

            t = b + ((c & a) | (d & ~a)) + X[0] + T20; b = ((t << 20) | (t >> (32 - 20))) + c;

            // Set 2
            t = a + ((b & d) | (c & ~d)) + T21; a = ((t << 5) | (t >> (32 - 5))) + b;

            t = d + ((a & c) | (b & ~c)) + T22; d = ((t << 9) | (t >> (32 - 9))) + a;

            t = c + ((d & b) | (a & ~b)) + T23; c = ((t << 14) | (t >> (32 - 14))) + d;

            t = b + ((c & a) | (d & ~a)) + T24; b = ((t << 20) | (t >> (32 - 20))) + c;

            // Set 3
            t = a + ((b & d) | (c & ~d)) + T25; a = ((t << 5) | (t >> (32 - 5))) + b;

            t = d + ((a & c) | (b & ~c)) + X_14 + T26; d = ((t << 9) | (t >> (32 - 9))) + a;

            t = c + ((d & b) | (a & ~b)) + T27; c = ((t << 14) | (t >> (32 - 14))) + d;

            t = b + ((c & a) | (d & ~a)) + T28; b = ((t << 20) | (t >> (32 - 20))) + c;

            // Set 4
            t = a + ((b & d) | (c & ~d)) + T29; a = ((t << 5) | (t >> (32 - 5))) + b;

            t = d + ((a & c) | (b & ~c)) + T30; d = ((t << 9) | (t >> (32 - 9))) + a;

            t = c + ((d & b) | (a & ~b)) + T31; c = ((t << 14) | (t >> (32 - 14))) + d;

            t = b + ((c & a) | (d & ~a)) + T32; b = ((t << 20) | (t >> (32 - 20))) + c;




            /* Round 3. */
            /* Let [abcd k s t] denote the operation
               a = b + ((a + H(b,c,d) + X[k] + T[i]) <<< s).
            */
            /* Do the following 16 operations. */
            // Set 1
            t = a + (b ^ c ^ d) + T33; a = ((t << 4) | (t >> (32 - 4))) + b;

            t = d + (a ^ b ^ c) + T34; d = ((t << 11) | (t >> (32 - 11))) + a;

            t = c + (d ^ a ^ b) + T35; c = ((t << 16) | (t >> (32 - 16))) + d;

            t = b + (c ^ d ^ a) + X_14 + T36; b = ((t << 23) | (t >> (32 - 23))) + c;

            // Set 2
            t = a + (b ^ c ^ d) + X[1] + T37; a = ((t << 4) | (t >> (32 - 4))) + b;

            t = d + (a ^ b ^ c) + T38; d = ((t << 11) | (t >> (32 - 11))) + a;

            t = c + (d ^ a ^ b) + T39; c = ((t << 16) | (t >> (32 - 16))) + d;

            t = b + (c ^ d ^ a) + T40; b = ((t << 23) | (t >> (32 - 23))) + c;

            // Set 3
            t = a + (b ^ c ^ d) + T41; a = ((t << 4) | (t >> (32 - 4))) + b;

            t = d + (a ^ b ^ c) + X[0] + T42; d = ((t << 11) | (t >> (32 - 11))) + a;

            t = c + (d ^ a ^ b) + T43; c = ((t << 16) | (t >> (32 - 16))) + d;

            t = b + (c ^ d ^ a) + T44; b = ((t << 23) | (t >> (32 - 23))) + c;

            // Set 4
            t = a + (b ^ c ^ d) + T45; a = ((t << 4) | (t >> (32 - 4))) + b;

            t = d + (a ^ b ^ c) + T46; d = ((t << 11) | (t >> (32 - 11))) + a;

            t = c + (d ^ a ^ b) + T47; c = ((t << 16) | (t >> (32 - 16))) + d;

            t = b + (c ^ d ^ a) + T48; b = ((t << 23) | (t >> (32 - 23))) + c;




            /* Round 4. */
            /* Let [abcd k s t] denote the operation
               a = b + ((a + I(b,c,d) + X[k] + T[i]) <<< s).
            */
            /* Do the following 16 operations. */
            // Set 1
            t = a + (c ^ (b | ~d)) + X[0] + T49; a = ((t << 6) | (t >> (32 - 6))) + b;

            t = d + (b ^ (a | ~c)) + T50; d = ((t << 10) | (t >> (32 - 10))) + a;

            t = c + (a ^ (d | ~b)) + X_14 + T51; c = ((t << 15) | (t >> (32 - 15))) + d;

            t = b + (d ^ (c | ~a)) + T52; b = ((t << 21) | (t >> (32 - 21))) + c;

            // Set 2
            t = a + (c ^ (b | ~d)) + T53; a = ((t << 6) | (t >> (32 - 6))) + b;

            t = d + (b ^ (a | ~c)) + T54; d = ((t << 10) | (t >> (32 - 10))) + a;

            t = c + (a ^ (d | ~b)) + T55; c = ((t << 15) | (t >> (32 - 15))) + d;

            t = b + (d ^ (c | ~a)) + X[1] + T56; b = ((t << 21) | (t >> (32 - 21))) + c;

            // Set 3
            t = a + (c ^ (b | ~d)) + T57; a = ((t << 6) | (t >> (32 - 6))) + b;

            t = d + (b ^ (a | ~c)) + T58; d = ((t << 10) | (t >> (32 - 10))) + a;

            t = c + (a ^ (d | ~b)) + T59; c = ((t << 15) | (t >> (32 - 15))) + d;

            t = b + (d ^ (c | ~a)) + T60; b = ((t << 21) | (t >> (32 - 21))) + c;

            // Set 4
            t = a + (c ^ (b | ~d)) + T61; a = ((t << 6) | (t >> (32 - 6))) + b;

            t = d + (b ^ (a | ~c)) + T62; d = ((t << 10) | (t >> (32 - 10))) + a;

            t = c + (a ^ (d | ~b)) + T63; c = ((t << 15) | (t >> (32 - 15))) + d;

            t = b + (d ^ (c | ~a)) + T64; b = ((t << 21) | (t >> (32 - 21))) + c;


            /* Then perform the following additions. (That is increment each
               of the four registers by the value it had before this block
               was started.)
            */
            a += 0x67452301;
            b += T_MASK ^ 0x10325476;
            c += T_MASK ^ 0x67452301;
            d += 0x10325476;
            
              if (cached_hash[0]  == a   &&
                  cached_hash[1]  == b   &&
                  cached_hash[2]  == c   &&
                  cached_hash[3]  == d
              ) {
              cuPrintf("\n**************************found*****************\n\n");              

              hash_word[0] = word[0];
              hash_word[1] = word[1];
              hash_word[2] = word[2];
              hash_word[3] = word[3];
              hash_word[4] = word[4];
              hash_word[5] = word[5];
              // cuPrintf("device word |%c%c%c%c%c%c|\n",
              //   hash_word[0], hash_word[1], hash_word[2], hash_word[3], hash_word[4], hash_word[5]);

            }
          } // END Loop 5
        } // END Loop 4
      } // END Loop 3
    } // END Loop 2
  } // END Loop 2
  // cuPrintf("counter: %lu - word[0]: %d - range1: %d- %d - range2: %d-%d\n",
  //   counter, word[0], begin_1, end_1, begin_2, end_2);
}





int main (int argc, char *argv[]) {
  fprintf(stdout, "main\n");

  if (argc != 2) {
    printf("**invalid number of arguments**\n");
    return 1;
  }

  char hash_str[32];
  md5_byte_t h_hash[16];

  // Generate a MD5 hash string for the word passed in as an arg
  // The generated hash is the one we'll try to break
  create_md5_hash_str(argv[1], hash_str);

  char word_to_break[7];

  strcpy(word_to_break, argv[1]);

  fprintf(stdout, "original_word: |%s|\n", word_to_break);
  fprintf(stdout, "hash to break: %s\n", hash_str);

  // Split the MD5 hash into 16 8bit char chunks
  // The idea is split the 32 bit char string into 16 chunks of 2 chars each
  // Then convert the ASCII value of the pair of chars to their hexadecimal
  // The reason being because when the MD5 hash is generated instead of creting a string
  // the hash is outputed in 16 chunks of hexadecimal value
  // So to increase the speed during comparasion we convert the hash we are trying to break to 16 chunks of hexadecimal
  // values so when it comes the time to compare the generated hashes with the hash that we are tying to break
  // we only need to issue a memcmp insetad of converting the bytes to a string and doing a strcmp
  break_down_hash(h_hash, hash_str);


  md5_word_t* X = (md5_word_t *)h_hash;
  printf("X[0]: %u\n", X[0]);
  printf("X[1]: %u\n", X[1]);
  printf("X[2]: %u\n", X[2]);
  printf("X[3]: %u\n", X[3]);

  cudaError_t error;

  // Declare device hash
  md5_word_t* d_hash;
  error = cudaMalloc((void**)&d_hash, sizeof(md5_word_t) * 4);
  if (error != cudaSuccess) {
    printf("%s:%d error: %d - %s\n", __FILE__, __LINE__, error, cudaGetErrorString(error));
  }

  error = cudaMemcpy(d_hash, X, sizeof(md5_word_t) * 4, cudaMemcpyHostToDevice);
  if (error != cudaSuccess) {
    printf("%s:%d error: %d - %s\n", __FILE__, __LINE__, error, cudaGetErrorString(error));
  }

  // Declare device word
  md5_byte_t* d_word;
  error = cudaMalloc((void**)&d_word, sizeof(md5_byte_t) * 6);
  if (error != cudaSuccess) {
    printf("%s:%d error: %d - %s\n", __FILE__, __LINE__, error, cudaGetErrorString(error));
  }


  int ascci_counter = 0;
  md5_byte_t h_ascii_codes[64];
  for (int i = 48; i <= 57; i++) {
    h_ascii_codes[ascci_counter++] = i;
  }
  for (int i = 65; i <= 90; i++) {
    h_ascii_codes[ascci_counter++] = i;
  }
  for (int i = 97; i <= 122; i++) {
    h_ascii_codes[ascci_counter++] = i;
  }
  h_ascii_codes[62] = 63; // ?
  h_ascii_codes[63] = 64; // @

  for (int i = 0; i < 64; i++) {
    // printf("h_ascii_codes[%d]: %d\n", i, h_ascii_codes[i]);
  }

  // Declare device hash
  md5_byte_t* d_ascii_codes;
  error = cudaMalloc((void**)&d_ascii_codes, sizeof(md5_byte_t) * 64);
  if (error != cudaSuccess) {
    printf("%s:%d error: %d - %s\n", __FILE__, __LINE__, error, cudaGetErrorString(error));
  }

  error = cudaMemcpy(d_ascii_codes, h_ascii_codes, sizeof(md5_byte_t) * 64, cudaMemcpyHostToDevice);
  if (error != cudaSuccess) {
    printf("%s:%d error: %d - %s\n", __FILE__, __LINE__, error, cudaGetErrorString(error));
  }  


  cudaPrintfInit();

  // dim3 dimBlock(64, 16, 1);
  // dim3 dimGrid(32, 1, 1);

  dim3 dimBlock(64, 8, 1);
  dim3 dimGrid(1, 1, 1);

  for (int i = 0; i < 64; i+=16) {
    printf("launching kernel...\n");
    do_md5<<<dimGrid, dimBlock>>>(d_hash, d_word, d_ascii_codes, 0+i, 8+i);
    printf("finished launching kernel...\n");

    // synchronize the device and the host
    cudaDeviceSynchronize();
    error = cudaGetLastError();
    if (error != cudaSuccess) {
      printf("%s:%d error: %d - %s\n", __FILE__, __LINE__, error, cudaGetErrorString(error));
    }

    
    md5_byte_t h_word[6];
    error = cudaMemcpy(h_word, d_word, sizeof(md5_byte_t) * 6, cudaMemcpyDeviceToHost);
    if (error != cudaSuccess) {
      printf("%s:%d error: %d - %s\n", __FILE__, __LINE__, error, cudaGetErrorString(error));
    }

    printf("device word |%c%c%c%c%c%c|\n", h_word[0], h_word[1], h_word[2], h_word[3], h_word[4], h_word[5]);
    printf("original    |%s|\n", word_to_break);

    if (!memcmp(word_to_break, h_word, sizeof(md5_byte_t) * 6)) {
      printf("Broke hash!\n");
      break;
    }
    printf("going to the next iteration...\n");
  }

  printf("finished!\n");

  cudaPrintfDisplay(stdout, true);
  cudaPrintfEnd();

  error = cudaFree(d_hash);
  if (error != cudaSuccess) {
    printf("%s:%d error: %d - %s\n", __FILE__, __LINE__, error, cudaGetErrorString(error));
  }

  error = cudaFree(d_word);
  if (error != cudaSuccess) {
    printf("%s:%d error: %d - %s\n", __FILE__, __LINE__, error, cudaGetErrorString(error));
  }

  return 1;
}




// Create hash string for |word|
// This is the hash string to the original hash we are trying to break
// We use the hash string to create the 16 8bit hexadecinal chunks
void create_md5_hash_str(const char* word, char* hash_str) {
  int di;

  md5_state_t state;
  md5_byte_t digest[16];  

  md5_init(&state);
  md5_append(&state, (const md5_byte_t *)word, strlen(word));
  md5_finish(&state, digest);
  
  for (di = 0; di < 16; di++) {
    sprintf(hash_str + di * 2, "%02x", digest[di]); 
  }
}

void break_down_hash (md5_byte_t* hash, char* hash_str) {
  int i, j;
  int digest = 0;
  int dec1 = 0;
  int dec2 = 0;
  for (i = 0, j = 0; i < 32; i += 2, j++) {
    dec1 = hex_to_decimal(hash_str[i]);
    dec2 = hex_to_decimal(hash_str[i+1]);
    // fprintf(stdout, "dec1: %d\n", dec1);
    // fprintf(stdout, "dec2: %d\n", dec2);
    digest =  dec1 * 16 + dec2;
    hash[j] = digest;
    // fprintf(stdout, "i %d - digest: %d\n", i, digest);
  }
}

int hex_to_decimal (char c) {
  switch (c) {
    case '0':
      return 0;
    case '1':
      return 1;
    case '2':
      return 2;
    case '3':
      return 3;
    case '4':
      return 4;
    case '5':
      return 5;
    case '6':
      return 6;
    case '7':
      return 7;
    case '8':
      return 8;
    case '9':
      return 9;
    case 'a':
    case 'A':
      return 10;
    case 'b':
    case 'B':
      return 11;
    case 'c':
    case 'C':
      return 12;
    case 'd':
    case 'D':
      return 13;
    case 'e':
    case 'E':
      return 14;
    case 'f':
    case 'F':
      return 15;
    default:
      fprintf(stdout, "FAILED to get convert %c to decimal\n", c);
  }

  return -1;
}

