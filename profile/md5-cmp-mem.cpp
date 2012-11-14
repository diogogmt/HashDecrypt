#include "md5.h"
#include <iostream>
#include <cmath>
#include <cstring>
#include <cstdlib>
#include <ctime>

static char hash_str[32];
static char hash[32];



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

void break_down_hash () {
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


// Generate MD5 hash for |word|
// Comparae the newly generated hash with the orginal hash we are trying to break
// We do a memcmp to check if the hashes are equal
int do_md5(const char* word) {
  char hex_output[16*2 + 1];
  int di;

  md5_state_t state;
  md5_byte_t digest[16];  

  md5_init(&state);
  md5_append(&state, (const md5_byte_t *)word, strlen(word));
  md5_finish(&state, digest);
  
  return !memcmp(digest, hash, sizeof(md5_byte_t) * 16);
}


// Create hash string for |word|
// This is the hash string to the original hash we are trying to break
// We use the hash string to create the 16 8bit hexadecinal chunks
void create_md5_hash_str(const char* word) {
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


int checkHash (char* word) {
  // fprintf(stdout, "checkHash\n");

  // check md5
  // fprintf(stdout, "word: |%s|\n", word);
  if (do_md5(word)) {
    fprintf(stdout, "HASH DECRYPTED!!\n");
    return 1;
  }

  return 0;
}

// Add a new char to the word array
// Initialize all the chats of the array to ascii value 32(space)
void addLetter (char* word, int* numberOfLetters) {
  // fprintf(stdout, "addLetter\n");
  int i;
  (*numberOfLetters)++;
  for (i = 0; i < *numberOfLetters; i++) {
    word[i] = char(32);
  }
  word[*numberOfLetters] = (char)0;
}

// Iterate through ASCII codes 32 to 127 in the word array
// only in the char with index equal to letterIndex
// Everytime the ascii value change a new md5 hash is generated and compared
// wit the hash being cracked
int changeAsciiCode (char* word, int letterIndex) {
  // fprintf(stdout, "changeAsciiCode\n");
  // fprintf(stdout, "letterIndex: %d\n", letterIndex);
  int i;
  for (i = 32; i < 127; i++) {
    word[letterIndex] = (char)i;
    if (checkHash(word)) {
      return 1;
    }
  }

  return 0;
}



void decrypt () {
  fprintf(stdout, "decrypt\n");

  int i;
  int numberOfLetters = 0;
  char word[20];

  addLetter(word, &numberOfLetters);

  while (1) {
    // fprintf(stdout, "\n\nanother iteration\n");
    // Change the last char on the word
    // Iterate through ascii values 32-126
    // it always the last char that gets change, since the other chars will be incremented
    // inside the other loop below in the code
    // the reason being  that we need to test all the possible combinations, for exmple
    // lets say a word of 4 chars: 32 32 32 32
    // changeAsciiCode would test 32 32 32 32-126
    // Then on the loop below would increment the char position numberOfLetter - 2
    // 32 32 33 32
    // The back again to changeAscciCode 32 32 33 32-126
    // And so on until all possible char combinations are tested for a word of n length

    if (changeAsciiCode(word, numberOfLetters - 1)) {
      return;
    }

    // In the first iteration the word only has 1 char
    // So i would be 0
    // To fix that we assign 1 to i only during the first iteration
    // After that i gets assigned the number of chars in the other minus 1
    i = (numberOfLetters == 1) ? 1 : numberOfLetters - 1;
    // fprintf(stdout, "numberOfLetters: %d\n", numberOfLetters);
    // fprintf(stdout, "i: %d\n", i);
    // We do i-- since we don't care about the last char in the word
    // changeAsciiCode is changing all the values for the last char above in the code
    // So what happens here:
    // If the word has 4 chars
    // i would be 3
    // the loop checks if i is true(!0) then subtracts 1 from it
    // In the first iteration of the loop i would be 2
    // 2 is the third letter in the word
    while (i--) {
      // fprintf(stdout, "inside while i: %d\n", i);
      // If we reached at the last ascci value 126 ~
      // It means we tested all the combinations from i >
      // so in a word of 4 chars
      // when i == 2 and word[i] == 126
      // we know that all the combinations for word[2] and word[3] have been tested
      // however word[0] and word[1] could be in their first iteration, thats why we have other
      // checkes below
      // else we increment the ascii value of the char at position i in the word
      // and then hash that string and check with the has we are trying to break
      // then we break the loop and start the process all over again
      if ((int)word[i] == 126) {
        // if i == 0 means we tested all the possible combinations for a word of n chars
        // so then we add another char to the word and start the process all over again
        // else we set the current char at i to 32 and go to the next char
        if (!i) {
          addLetter(word, &numberOfLetters);
          break;
        } else {
          // fprintf(stdout, "letter index %d - ascii value %d, setting to 32(space)\n", i, (int)word[i]);
          word[i] = (char)32;
        }

      } else {
        // fprintf(stdout, "letter index %d - ascii value %d, incrementing by 1\n", i, (int)word[i]);
        word[i]++;
        if (checkHash(word)) {
          return;
        }
        break;
      }     
    }
  }

  fprintf(stdout, "done\n");
}


int main (int argc, char *argv[]) {
	fprintf(stdout, "main\n");

  if (argc != 2) {
    printf("**invalid number of arguments**\n");
    return 1;
  }

  // Generate a MD5 hash string for the word passed in as an arg
  // The generated hash is the one we'll try to break
  create_md5_hash_str(argv[1]);

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
  break_down_hash();
  // fprintf(stdout, "hash to break: %s\n", hash);


	decrypt();
}


