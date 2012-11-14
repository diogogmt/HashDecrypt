#include "md5.h"
#include <iostream>
#include <cmath>
#include <cstring>
#include <cstdlib>
#include <ctime>


int do_md5 (const char* word, md5_byte_t* hash);



void try_to_break_hash (md5_byte_t *hash);
void create_md5_hash_str (const char *word, char *hash_str);
void break_down_hash (md5_byte_t *hash, char *hash_str);
int hex_to_decimal (char c);








// Generate MD5 hash for |word|
// Comparae the newly generated hash with the orginal hash we are trying to break
// We do a memcmp to check if the hashes are equal
int do_md5(const char* word, md5_byte_t* hash) {
  char hex_output[16*2 + 1];
  int di;

  md5_state_t state;
  md5_byte_t digest[16];  

  md5_init(&state);
  md5_append(&state, (const md5_byte_t *)word, strlen(word));
  md5_finish(&state, digest);
  
  return !memcmp(digest, hash, sizeof(md5_byte_t) * 16);
}





int main (int argc, char *argv[]) {
	fprintf(stdout, "main\n");

  if (argc != 2) {
    printf("**invalid number of arguments**\n");
    return 1;
  }

  char hash_str[32];
  md5_byte_t hash[16];

  // Generate a MD5 hash string for the word passed in as an arg
  // The generated hash is the one we'll try to break
  create_md5_hash_str(argv[1], hash_str);


  fprintf(stdout, "original_word: %s\n", argv[1]);
  fprintf(stdout, "hash to break: %s\n", hash_str);

  // Split the MD5 hash into 16 8bit char chunks
  // The idea is split the 32 bit char string into 16 chunks of 2 chars each
  // Then convert the ASCII value of the pair of chars to their hexadecimal
  // The reason being because when the MD5 hash is generated instead of creting a string
  // the hash is outputed in 16 chunks of hexadecimal value
  // So to increase the speed during comparasion we convert the hash we are trying to break to 16 chunks of hexadecimal
  // values so when it comes the time to compare the generated hashes with the hash that we are tying to break
  // we only need to issue a memcmp insetad of converting the bytes to a string and doing a strcmp
  break_down_hash(hash, hash_str);


  try_to_break_hash(hash);

  return 1;
}



void try_to_break_hash (md5_byte_t *hash) {
  printf("try_to_break_hash\n");
  char word[4];
  word[0] = (char) 32;
  word[1] = (char) 32;
  word[2] = (char) 32;
  word[3] = (char) 32;

  // We need to print here because cuPrintf doesnt work
  // if any cuPrintfs are inside a control structure statements such as if statement os for loops
  // cuPrintf("%c\n", word[0]);

  int i_0, i_1, i_2, i_3;

  md5_state_t state;
  md5_byte_t digest[16]; 
  int counter = 0;
  int di = 0;

 for (i_0 = 32; i_0 < 42; i_0++) {
    word[0] = (char) i_0;
    for (i_1 = 32; i_1 < 42; i_1++) {
      word[1] = (char) i_1;
      for (i_2 = 32; i_2 < 42; i_2++) {
        word[2] = (char) i_2;
        for (i_3 = 32; i_3 < 42; i_3++) {
          word[3] = (char) i_3;
          if (do_md5(word, hash)) {
            printf("Broke hash!\n");
            printf("word: %c%c%c%c\n", word[0], word[1], word[2], word[3]);
            return;
          }
        } // END Loop 3
      } // END Loop 2
    } // END Loop 1
  } // END loop 0
}


























// Create hash string for |word|
// This is the hash string to the original hash we are trying to break
// We use the hash string to create the 16 8bit hexadecinal chunks
void create_md5_hash_str(const char* word, char* hash_str) {
  char hex_output[16*2 + 1];
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
}
