#include <iostream>
#include <cmath>
#include <cstring>
#include <cstdlib>
#include <ctime>
#include <cuda_runtime.h>
// #include "md5.cuh"
// #include "cuPrintf.cu"





typedef unsigned char md5_byte_t; /* 8-bit byte */
typedef unsigned int md5_word_t; /* 32-bit word */

/* Define the state of the MD5 Algorithm. */
typedef struct md5_state_s {
    md5_word_t count[2];  /* message length in bits, lsw first */
    md5_word_t abcd[4];   /* digest buffer */
    md5_byte_t buf[64];   /* accumulate block */
} md5_state_t;









#undef BYTE_ORDER /* 1 = big-endian, -1 = little-endian, 0 = unknown */
#ifdef ARCH_IS_BIG_ENDIAN
	#define BYTE_ORDER (ARCH_IS_BIG_ENDIAN ? 1 : -1)
#else
	#define BYTE_ORDER 0
#endif

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


__host__ __device__
static void md5_process(md5_state_t *pms, const md5_byte_t *data /*[64]*/) {
  md5_word_t a = pms->abcd[0], b = pms->abcd[1], c = pms->abcd[2], d = pms->abcd[3];
  md5_word_t t;

  /* Define storage for little-endian or both types of CPUs. */
  md5_word_t xbuf[16];
  const md5_word_t *X;

  {
    /*
     * Determine dynamically whether this is a big-endian or
     * little-endian machine, since we can use a more efficient
     * algorithm on the latter.
     */
    const int w = 1;

    if (*((const md5_byte_t *)&w)) /* dynamic little-endian */ {
      /*
      * On little-endian machines, we can process properly aligned
      * data without copying it.
      */
      if (!((data - (const md5_byte_t *)0) & 3)) {
        /* data are properly aligned */
        X = (const md5_word_t *)data;
      } else {
        /* not aligned */
        memcpy(xbuf, data, 64);
        X = xbuf;
      }
    } 
  }

  #define ROTATE_LEFT(x, n) (((x) << (n)) | ((x) >> (32 - (n))))

  /* Round 1. */
  /* Let [abcd k s i] denote the operation
     a = b + ((a + F(b,c,d) + X[k] + T[i]) <<< s). */
  #define F(x, y, z) (((x) & (y)) | (~(x) & (z)))
  #define SET(a, b, c, d, k, s, Ti)\
    t = a + F(b,c,d) + X[k] + Ti;\
    a = ROTATE_LEFT(t, s) + b
    /* Do the following 16 operations. */
    SET(a, b, c, d,  0,  7,  T1);
    SET(d, a, b, c,  1, 12,  T2);
    SET(c, d, a, b,  2, 17,  T3);
    SET(b, c, d, a,  3, 22,  T4);
    SET(a, b, c, d,  4,  7,  T5);
    SET(d, a, b, c,  5, 12,  T6);
    SET(c, d, a, b,  6, 17,  T7);
    SET(b, c, d, a,  7, 22,  T8);
    SET(a, b, c, d,  8,  7,  T9);
    SET(d, a, b, c,  9, 12, T10);
    SET(c, d, a, b, 10, 17, T11);
    SET(b, c, d, a, 11, 22, T12);
    SET(a, b, c, d, 12,  7, T13);
    SET(d, a, b, c, 13, 12, T14);
    SET(c, d, a, b, 14, 17, T15);
    SET(b, c, d, a, 15, 22, T16);
  #undef SET

  /* Round 2. */
  /* Let [abcd k s i] denote the operation
     a = b + ((a + G(b,c,d) + X[k] + T[i]) <<< s). */
  #define G(x, y, z) (((x) & (z)) | ((y) & ~(z)))
  #define SET(a, b, c, d, k, s, Ti)\
    t = a + G(b,c,d) + X[k] + Ti;\
    a = ROTATE_LEFT(t, s) + b
   /* Do the following 16 operations. */
  SET(a, b, c, d,  1,  5, T17);
  SET(d, a, b, c,  6,  9, T18);
  SET(c, d, a, b, 11, 14, T19);
  SET(b, c, d, a,  0, 20, T20);
  SET(a, b, c, d,  5,  5, T21);
  SET(d, a, b, c, 10,  9, T22);
  SET(c, d, a, b, 15, 14, T23);
  SET(b, c, d, a,  4, 20, T24);
  SET(a, b, c, d,  9,  5, T25);
  SET(d, a, b, c, 14,  9, T26);
  SET(c, d, a, b,  3, 14, T27);
  SET(b, c, d, a,  8, 20, T28);
  SET(a, b, c, d, 13,  5, T29);
  SET(d, a, b, c,  2,  9, T30);
  SET(c, d, a, b,  7, 14, T31);
  SET(b, c, d, a, 12, 20, T32);
  #undef SET

  /* Round 3. */
  /* Let [abcd k s t] denote the operation
     a = b + ((a + H(b,c,d) + X[k] + T[i]) <<< s). */
  #define H(x, y, z) ((x) ^ (y) ^ (z))
  #define SET(a, b, c, d, k, s, Ti)\
    t = a + H(b,c,d) + X[k] + Ti;\
    a = ROTATE_LEFT(t, s) + b
  /* Do the following 16 operations. */
  SET(a, b, c, d,  5,  4, T33);
  SET(d, a, b, c,  8, 11, T34);
  SET(c, d, a, b, 11, 16, T35);
  SET(b, c, d, a, 14, 23, T36);
  SET(a, b, c, d,  1,  4, T37);
  SET(d, a, b, c,  4, 11, T38);
  SET(c, d, a, b,  7, 16, T39);
  SET(b, c, d, a, 10, 23, T40);
  SET(a, b, c, d, 13,  4, T41);
  SET(d, a, b, c,  0, 11, T42);
  SET(c, d, a, b,  3, 16, T43);
  SET(b, c, d, a,  6, 23, T44);
  SET(a, b, c, d,  9,  4, T45);
  SET(d, a, b, c, 12, 11, T46);
  SET(c, d, a, b, 15, 16, T47);
  SET(b, c, d, a,  2, 23, T48);
  #undef SET

  /* Round 4. */
  /* Let [abcd k s t] denote the operation
     a = b + ((a + I(b,c,d) + X[k] + T[i]) <<< s). */
  #define I(x, y, z) ((y) ^ ((x) | ~(z)))
  #define SET(a, b, c, d, k, s, Ti)\
    t = a + I(b,c,d) + X[k] + Ti;\
    a = ROTATE_LEFT(t, s) + b
  /* Do the following 16 operations. */
  SET(a, b, c, d,  0,  6, T49);
  SET(d, a, b, c,  7, 10, T50);
  SET(c, d, a, b, 14, 15, T51);
  SET(b, c, d, a,  5, 21, T52);
  SET(a, b, c, d, 12,  6, T53);
  SET(d, a, b, c,  3, 10, T54);
  SET(c, d, a, b, 10, 15, T55);
  SET(b, c, d, a,  1, 21, T56);
  SET(a, b, c, d,  8,  6, T57);
  SET(d, a, b, c, 15, 10, T58);
  SET(c, d, a, b,  6, 15, T59);
  SET(b, c, d, a, 13, 21, T60);
  SET(a, b, c, d,  4,  6, T61);
  SET(d, a, b, c, 11, 10, T62);
  SET(c, d, a, b,  2, 15, T63);
  SET(b, c, d, a,  9, 21, T64);
  #undef SET

  /* Then perform the following additions. (That is increment each
     of the four registers by the value it had before this block
     was started.) */
  pms->abcd[0] += a;
  pms->abcd[1] += b;
  pms->abcd[2] += c;
  pms->abcd[3] += d;
}


__host__ __device__
void md5_init(md5_state_t *pms) {
  pms->count[0] = pms->count[1] = 0;
  pms->abcd[0] = 0x67452301;
  pms->abcd[1] = /*0xefcdab89*/ T_MASK ^ 0x10325476;
  pms->abcd[2] = /*0x98badcfe*/ T_MASK ^ 0x67452301;
  pms->abcd[3] = 0x10325476;
}

__host__ __device__
void
md5_append(md5_state_t *pms, const md5_byte_t *data, int nbytes) {
  const md5_byte_t *p = data;
  int left = nbytes;
  int offset = (pms->count[0] >> 3) & 63;
  md5_word_t nbits = (md5_word_t)(nbytes << 3);

  if (nbytes <= 0) {
    return;
  }

  /* Update the message length. */
  pms->count[1] += nbytes >> 29;
  pms->count[0] += nbits;
  if (pms->count[0] < nbits) {
    pms->count[1]++;
  }

  /* Process an initial partial block. */
  if (offset) {
    int copy = (offset + nbytes > 64 ? 64 - offset : nbytes);

    memcpy(pms->buf + offset, p, copy);
    if (offset + copy < 64) {
      return;
    }
    p += copy;
    left -= copy;
    md5_process(pms, pms->buf);
  }

  /* Process full blocks. */
  for (; left >= 64; p += 64, left -= 64) {
    md5_process(pms, p);
  }

  /* Process a final partial block. */
  if (left) {
    memcpy(pms->buf, p, left);
  }
}

__host__ __device__ void
md5_finish(md5_state_t *pms, md5_byte_t digest[16]) {
  // static const md5_byte_t pad[64] = {
  const md5_byte_t pad[64] = {
    0x80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
  };
  md5_byte_t data[8];
  int i;

  /* Save the length before padding. */
  for (i = 0; i < 8; ++i) {
    data[i] = (md5_byte_t)(pms->count[i >> 2] >> ((i & 3) << 3));
  }
  /* Pad to 56 bytes mod 64. */
  md5_append(pms, pad, ((55 - (pms->count[0] >> 3)) & 63) + 1);
  /* Append the length. */
  md5_append(pms, data, 8);
  for (i = 0; i < 16; ++i) {
    digest[i] = (md5_byte_t)(pms->abcd[i >> 2] >> ((i & 3) << 3));
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
      break;
  }

  return -1;
}

void break_down_hash (char* hash_str, md5_byte_t* hash) {
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


// Create hash string for |word|
// This is the hash string to the original hash we are trying to break
// We use the hash string to create the 16 8bit hexadecinal chunks
void create_md5_hash_str(const char* word, char* hash_str) {
  // char hex_output[16*2 + 1];
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



__global__ void testKernel (md5_byte_t* hash_to_break, char* hash_word) {

	char di = 0;
  md5_byte_t cached_hash[16];
  for (di = 0; di < 16; di++) {
    cached_hash[di] = hash_to_break[di];
  }


  //  __shared__ const md5_byte_t pad[64] = {
  //    0x80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  //    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  //    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  //    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
  //  };
    __shared__ md5_byte_t pad[64];
    pad[0] = 0x80;
    for (di = 1; di < 64; di++) {
      pad[di] = 0;
    }

  char word[4];
  word[0] = (char) threadIdx.x + 32;
  word[1] = (char) 32;
  word[2] = (char) 32;
  word[3] = (char) 32;

  // We need to print here because cuPrintf doesnt work
  // if any cuPrintfs are inside a control structure statements such as if statement os for loops
  // cuPrintf("%c\n", word[0]);

  char i_1, i_2, i_3;

  char cached_hash_word[4];
  cached_hash_word[0] = (char)0;

  md5_state_t state;
  md5_byte_t digest[16]; 
  char counter = 0;

  for (i_1 = 32; i_1 < 42; i_1++) {
    word[1] = (char) i_1;
    for (i_2 = 32; i_2 < 42; i_2++) {
      word[2] = (char) i_2;
      for (i_3 = 32; i_3 < 42; i_3++) {
        word[3] = (char) i_3;
        //md5_init(&state);
        state.count[0] = state.count[1] = 0;
        state.abcd[0] = 0x67452301;
        state.abcd[1] = /*0xefcdab89*/ T_MASK ^ 0x10325476;
        state.abcd[2] = /*0x98badcfe*/ T_MASK ^ 0x67452301;
        state.abcd[3] = 0x10325476;
        // end md5_init

        md5_append(&state, (const md5_byte_t *)word, 4);
        //md5_finish(&state, digest);
        //md5_finish(md5_state_t *pms, md5_byte_t digest[16]) {
        // static const md5_byte_t pad[64] = {
        // const md5_byte_t pad[64] = {
        //   0x80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        //   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        //   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        //   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
        // };
        md5_byte_t data[8];
        int i;

        /* Save the length before padding. */
        for (i = 0; i < 8; ++i) {
          data[i] = (md5_byte_t)(state.count[i >> 2] >> ((i & 3) << 3));
        }
        /* Pad to 56 bytes mod 64. */
        md5_append(&state, pad, ((55 - (state.count[0] >> 3)) & 63) + 1);
        /* Append the length. */
        md5_append(&state, data, 8);
        for (i = 0; i < 16; ++i) {
          digest[i] = (md5_byte_t)(state.abcd[i >> 2] >> ((i & 3) << 3));
        }
        // end md5_finish

        counter = 0;
        for (di = 0; di < 16; di++) {
          if (digest[di] == cached_hash[di]) {
            counter++;
          }
        }
        if (counter == 16) {
        	for (di = 0; di < 4; di++) {
        		cached_hash_word[di] = word[di];
        	}
        }
      } // END Loop 3
    } // END Loop 2
  } // END Loop 1
  if (cached_hash_word[0] != (char)0) {
	  for (di = 0; di < 4; di++) {
			hash_word[di] = cached_hash_word[di];
		}
  }
} // END kernel

int main (int argc, char *argv[]) {
  if (argc != 2) {
    printf("**invalid number of arguments**\n");
    return 1;
  }

  char hash_str[32];
  md5_byte_t h_hash[16];

  create_md5_hash_str(argv[1], hash_str);

  printf("original_word: %s\n", argv[1]);
  printf("hash to break: %s\n", hash_str);

  break_down_hash(hash_str, h_hash);

  // Declare device hash
  md5_byte_t* d_hash;
  cudaMalloc((void**)&d_hash, sizeof(md5_byte_t) * 16);
  cudaMemcpy(d_hash, h_hash, sizeof(md5_byte_t) * 16, cudaMemcpyHostToDevice);

  // Declare device hash
char* d_word;
cudaMalloc((void**)&d_word, sizeof(char) * 4);

  // cudaPrintfInit();

  testKernel<<<1,10>>>(d_hash, d_word);

  // cudaPrintfDisplay(stdout, true);
  // cudaPrintfEnd();
  char h_word[4];
  cudaMemcpy(h_word, d_word, sizeof(char) * 4, cudaMemcpyDeviceToHost);
  printf("|%c%c%c%c|\n", h_word[0], h_word[1], h_word[2], h_word[3]);

  cudaFree(d_hash);
  cudaFree(d_word);

  printf("finished!\n");
}


