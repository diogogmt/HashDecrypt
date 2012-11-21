#include "md5.h"
#include <iostream>
#include <cmath>
#include <cstring>
#include <cstdlib>
#include <ctime>
#include <cuda_runtime.h>

#include "cuPrintf.cu"



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


#define STR_SIZE 4
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
#define X_14 32
#define ZERO 0
__global__ void do_md5(md5_byte_t* hash_to_break, md5_byte_t* hash_word) {

  __shared__ md5_byte_t cached_hash[16];
  for (char it = 0; it < 16; it++) {
    cached_hash[it] = hash_to_break[it];
  }

  md5_word_t a;
  md5_word_t b;
  md5_word_t c;
  md5_word_t d;

  md5_word_t t;

  md5_word_t word;

  cuPrintf("word: %u\n", threadIdx.x | 0x00F);

  char i_1, i_2, i_3;

  for (i_1 = 32; i_1 < 127; i_1++) {
    for (i_2 = 32; i_2 < 127; i_2++) {
      for (i_3 = 32; i_3 < 127; i_3++) {
        word = (threadIdx.x + 32) | (i_1 << 8) | (i_2 << 16) | (i_3 << 24);

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
        t = a + ((b & c) | (~b & d)) + word + T1;
        a = ((t << 7) | (t >> (32 - 7))) + b;

        t = d + ((a & b) | (~a & c)) + X_1 + T2;
        d = ((t << 12) | (t >> (32 - 12))) + a;

        t = c + ((d & a) | (~d & b)) + ZERO + T3;
        c = ((t << 17) | (t >> (32 - 17))) + d;

        t = b + ((c & d) | (~c & a)) + ZERO + T4;
        b = ((t << 22) | (t >> (32 - 22))) + c;

        // Set 2
        t = a + ((b & c) | (~b & d)) + ZERO + T5;
        a = ((t << 7) | (t >> (32 - 7))) + b;

        t = d + ((a & b) | (~a & c)) + ZERO + T6;
        d = ((t << 12) | (t >> (32 - 12))) + a;

        t = c + ((d & a) | (~d & b)) + ZERO + T7;
        c = ((t << 17) | (t >> (32 - 17))) + d;

        t = b + ((c & d) | (~c & a)) + ZERO + T8;
        b = ((t << 22) | (t >> (32 - 22))) + c;

        // Set 3
        t = a + ((b & c) | (~b & d)) + ZERO + T9;
        a = ((t << 7) | (t >> (32 - 7))) + b;

        t = d + ((a & b) | (~a & c)) + ZERO + T10;
        d = ((t << 12) | (t >> (32 - 12))) + a;

        t = c + ((d & a) | (~d & b)) + ZERO + T11;
        c = ((t << 17) | (t >> (32 - 17))) + d;

        t = b + ((c & d) | (~c & a)) + ZERO + T12;
        b = ((t << 22) | (t >> (32 - 22))) + c;

        // Set 4
        t = a + ((b & c) | (~b & d)) + ZERO + T13;
        a = ((t << 7) | (t >> (32 - 7))) + b;

        t = d + ((a & b) | (~a & c)) + ZERO + T14;
        d = ((t << 12) | (t >> (32 - 12))) + a;

        t = c + ((d & a) | (~d & b)) + X_14 + T15;
        c = ((t << 17) | (t >> (32 - 17))) + d;

        t = b + ((c & d) | (~c & a)) + ZERO + T16;
        b = ((t << 22) | (t >> (32 - 22))) + c;



        /* Round 2. */
        /* Let [abcd k s i] denote the operation
           a = b + ((a + G(b,c,d) + X[k] + T[i]) <<< s).
        */
        /* Do the following 16 operations. */
        // Set 1
        t = a + ((b & d) | (c & ~d)) + X_1 + T17;
        a = ((t << 5) | (t >> (32 - 5))) + b;

        t = d + ((a & c) | (b & ~c)) + ZERO + T18;
        d = ((t << 9) | (t >> (32 - 9))) + a;

        t = c + ((d & b) | (a & ~b)) + ZERO + T19;
        c = ((t << 14) | (t >> (32 - 14))) + d;

        t = b + ((c & a) | (d & ~a)) + word + T20;
        b = ((t << 20) | (t >> (32 - 20))) + c;

        // Set 2
        t = a + ((b & d) | (c & ~d)) + ZERO + T21;
        a = ((t << 5) | (t >> (32 - 5))) + b;

        t = d + ((a & c) | (b & ~c)) + ZERO + T22;
        d = ((t << 9) | (t >> (32 - 9))) + a;

        t = c + ((d & b) | (a & ~b)) + ZERO + T23;
        c = ((t << 14) | (t >> (32 - 14))) + d;

        t = b + ((c & a) | (d & ~a)) + ZERO + T24;
        b = ((t << 20) | (t >> (32 - 20))) + c;

        // Set 3
        t = a + ((b & d) | (c & ~d)) + ZERO + T25;
        a = ((t << 5) | (t >> (32 - 5))) + b;

        t = d + ((a & c) | (b & ~c)) + X_14 + T26;
        d = ((t << 9) | (t >> (32 - 9))) + a;

        t = c + ((d & b) | (a & ~b)) + ZERO + T27;
        c = ((t << 14) | (t >> (32 - 14))) + d;

        t = b + ((c & a) | (d & ~a)) + ZERO + T28;
        b = ((t << 20) | (t >> (32 - 20))) + c;

        // Set 4
        t = a + ((b & d) | (c & ~d)) + ZERO + T29;
        a = ((t << 5) | (t >> (32 - 5))) + b;

        t = d + ((a & c) | (b & ~c)) + ZERO + T30;
        d = ((t << 9) | (t >> (32 - 9))) + a;

        t = c + ((d & b) | (a & ~b)) + ZERO + T31;
        c = ((t << 14) | (t >> (32 - 14))) + d;

        t = b + ((c & a) | (d & ~a)) + ZERO + T32;
        b = ((t << 20) | (t >> (32 - 20))) + c;




        /* Round 3. */
        /* Let [abcd k s t] denote the operation
           a = b + ((a + H(b,c,d) + X[k] + T[i]) <<< s).
        */
        /* Do the following 16 operations. */
        // Set 1
        t = a + (b ^ c ^ d) + ZERO + T33;
        a = ((t << 4) | (t >> (32 - 4))) + b;

        t = d + (a ^ b ^ c) + ZERO + T34;
        d = ((t << 11) | (t >> (32 - 11))) + a;

        t = c + (d ^ a ^ b) + ZERO + T35;
        c = ((t << 16) | (t >> (32 - 16))) + d;

        t = b + (c ^ d ^ a) + X_14 + T36;
        b = ((t << 23) | (t >> (32 - 23))) + c;

        // Set 2
        t = a + (b ^ c ^ d) + X_1 + T37;
        a = ((t << 4) | (t >> (32 - 4))) + b;

        t = d + (a ^ b ^ c) + ZERO + T38;
        d = ((t << 11) | (t >> (32 - 11))) + a;

        t = c + (d ^ a ^ b) + ZERO + T39;
        c = ((t << 16) | (t >> (32 - 16))) + d;

        t = b + (c ^ d ^ a) + ZERO + T40;
        b = ((t << 23) | (t >> (32 - 23))) + c;

        // Set 3
        t = a + (b ^ c ^ d) + ZERO + T41;
        a = ((t << 4) | (t >> (32 - 4))) + b;

        t = d + (a ^ b ^ c) + word + T42;
        d = ((t << 11) | (t >> (32 - 11))) + a;

        t = c + (d ^ a ^ b) + ZERO + T43;
        c = ((t << 16) | (t >> (32 - 16))) + d;

        t = b + (c ^ d ^ a) + ZERO + T44;
        b = ((t << 23) | (t >> (32 - 23))) + c;

        // Set 4
        t = a + (b ^ c ^ d) + ZERO + T45;
        a = ((t << 4) | (t >> (32 - 4))) + b;

        t = d + (a ^ b ^ c) + ZERO + T46;
        d = ((t << 11) | (t >> (32 - 11))) + a;

        t = c + (d ^ a ^ b) + ZERO + T47;
        c = ((t << 16) | (t >> (32 - 16))) + d;

        t = b + (c ^ d ^ a) + ZERO + T48;
        b = ((t << 23) | (t >> (32 - 23))) + c;




        /* Round 4. */
        /* Let [abcd k s t] denote the operation
           a = b + ((a + I(b,c,d) + X[k] + T[i]) <<< s).
        */
        /* Do the following 16 operations. */
        // Set 1
        t = a + (c ^ (b | ~d)) + word + T49;
        a = ((t << 6) | (t >> (32 - 6))) + b;

        t = d + (b ^ (a | ~c)) + ZERO + T50;
        d = ((t << 10) | (t >> (32 - 10))) + a;

        t = c + (a ^ (d | ~b)) + X_14 + T51;
        c = ((t << 15) | (t >> (32 - 15))) + d;

        t = b + (d ^ (c | ~a)) + ZERO + T52;
        b = ((t << 21) | (t >> (32 - 21))) + c;

        // Set 2
        t = a + (c ^ (b | ~d)) + ZERO + T53;
        a = ((t << 6) | (t >> (32 - 6))) + b;

        t = d + (b ^ (a | ~c)) + ZERO + T54;
        d = ((t << 10) | (t >> (32 - 10))) + a;

        t = c + (a ^ (d | ~b)) + ZERO + T55;
        c = ((t << 15) | (t >> (32 - 15))) + d;

        t = b + (d ^ (c | ~a)) + X_1 + T56;
        b = ((t << 21) | (t >> (32 - 21))) + c;

        // Set 3
        t = a + (c ^ (b | ~d)) + ZERO + T57;
        a = ((t << 6) | (t >> (32 - 6))) + b;

        t = d + (b ^ (a | ~c)) + ZERO + T58;
        d = ((t << 10) | (t >> (32 - 10))) + a;

        t = c + (a ^ (d | ~b)) + ZERO + T59;
        c = ((t << 15) | (t >> (32 - 15))) + d;

        t = b + (d ^ (c | ~a)) + ZERO + T60;
        b = ((t << 21) | (t >> (32 - 21))) + c;

        // Set 4
        t = a + (c ^ (b | ~d)) + ZERO + T61;
        a = ((t << 6) | (t >> (32 - 6))) + b;

        t = d + (b ^ (a | ~c)) + ZERO + T62;
        d = ((t << 10) | (t >> (32 - 10))) + a;

        t = c + (a ^ (d | ~b)) + ZERO + T63;
        c = ((t << 15) | (t >> (32 - 15))) + d;

        t = b + (d ^ (c | ~a)) + ZERO + T64;
        b = ((t << 21) | (t >> (32 - 21))) + c;


        /* Then perform the following additions. (That is increment each
           of the four registers by the value it had before this block
           was started.)
        */
        a += 0x67452301;
        b += T_MASK ^ 0x10325476;
        c += T_MASK ^ 0x67452301;
        d += 0x10325476;
        
        if (cached_hash[0]   == (md5_byte_t)(a >> 0)   &&
            cached_hash[1]   == (md5_byte_t)(a >> 8)   &&
            cached_hash[2]   == (md5_byte_t)(a >> 16)  &&
            cached_hash[3]   == (md5_byte_t)(a >> 24)  &&

            cached_hash[4]   == (md5_byte_t)(b >> 0)   &&
            cached_hash[5]   == (md5_byte_t)(b >> 8)   &&
            cached_hash[6]   == (md5_byte_t)(b >> 16)  &&
            cached_hash[7]   == (md5_byte_t)(b >> 24)  &&

            cached_hash[8]   == (md5_byte_t)(c >> 0)   &&
            cached_hash[9]   == (md5_byte_t)(c >> 8)   &&
            cached_hash[10]  == (md5_byte_t)(c >> 16)  &&
            cached_hash[11]  == (md5_byte_t)(c >> 24)  &&

            cached_hash[12]  == (md5_byte_t)(d >> 0)   &&
            cached_hash[13]  == (md5_byte_t)(d >> 8)   &&
            cached_hash[14]  == (md5_byte_t)(d >> 16)  &&
            cached_hash[15]  == (md5_byte_t)(d >> 24)
          ) {
          cuPrintf("found.\n");
          hash_word[0] = word & 0xff;
          hash_word[1] = i_1;
          hash_word[2] = i_2;
          hash_word[3] = i_3;
          // hash_word[0] = word[0];
          // hash_word[1] = word[1];
          // hash_word[2] = word[2];
          // hash_word[3] = word[3];
        }
      } // END Loop 3
    } // END Loop 2
  } // END Loop 2
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


  fprintf(stdout, "original_word: |%s|\n", argv[1]);
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

  cudaError_t error;

  // Declare device hash
  md5_byte_t* d_hash;
  error = cudaMalloc((void**)&d_hash, sizeof(md5_byte_t) * 16);
  if (error != cudaSuccess) {
    printf("%s:%d error: %d - %s\n", __FILE__, __LINE__, error, cudaGetErrorString(error));
  }

  error = cudaMemcpy(d_hash, h_hash, sizeof(md5_byte_t) * 16, cudaMemcpyHostToDevice);
  if (error != cudaSuccess) {
    printf("%s:%d error: %d - %s\n", __FILE__, __LINE__, error, cudaGetErrorString(error));
  }

  // Declare device hash
  md5_byte_t* d_word;
  error = cudaMalloc((void**)&d_word, sizeof(md5_byte_t) * 4);
  if (error != cudaSuccess) {
    printf("%s:%d error: %d - %s\n", __FILE__, __LINE__, error, cudaGetErrorString(error));
  }

  cudaPrintfInit();

  do_md5<<<1,94>>>(d_hash, d_word);

  // synchronize the device and the host
  cudaDeviceSynchronize();
  error = cudaGetLastError();
  if (error != cudaSuccess) {
    printf("%s:%d error: %d - %s\n", __FILE__, __LINE__, error, cudaGetErrorString(error));
  }

  cudaPrintfDisplay(stdout, true);
  cudaPrintfEnd();
  md5_byte_t h_word[4];
  error = cudaMemcpy(h_word, d_word, sizeof(md5_byte_t) * 4, cudaMemcpyDeviceToHost);
  if (error != cudaSuccess) {
    printf("%s:%d error: %d - %s\n", __FILE__, __LINE__, error, cudaGetErrorString(error));
  }

  printf("|%c%c%c%c|\n", h_word[0], h_word[1], h_word[2], h_word[3]);

  error = cudaFree(d_hash);
  if (error != cudaSuccess) {
    printf("%s:%d error: %d - %s\n", __FILE__, __LINE__, error, cudaGetErrorString(error));
  }

  error = cudaFree(d_word);
  if (error != cudaSuccess) {
    printf("%s:%d error: %d - %s\n", __FILE__, __LINE__, error, cudaGetErrorString(error));
  }

  printf("finished!\n");

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

