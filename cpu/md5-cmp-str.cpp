#include "md5.h"
#include "main.h"
#include <iostream>
#include <cmath>
#include <cstring>
#include <cstdlib>
#include <ctime>

static char hash[32];

int do_md5(const char* word, char* output) {
  char hex_output[16*2 + 1];
  int di;

  md5_state_t state;
  md5_byte_t digest[16];  

  md5_init(&state);
  md5_append(&state, (const md5_byte_t *)word, strlen(word));
  md5_finish(&state, digest);
  
  for (di = 0; di < 16; di++) {
    sprintf(output + di * 2, "%02x", digest[di]); 
  }
}


int checkHash (char* word) {
  // fprintf(stdout, "checkHash\n");
  char output_hash[32];

  // check md5
  // fprintf(stdout, "word: |%s|\n", word);
  do_md5(word, output_hash);
  if (!strcmp(hash, output_hash)) {
    fprintf(stdout, "HASH DECRYPTED!!\n");
    return 1;
  }

  return 0;
}

// Add a new char to the word array
// Initialize all the chats of the array to ascii value 32(space)
void addLetter (char* word, int* numberOfLetters) {
  fprintf(stdout, "addLetter\n");
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

    if (numberOfLetters == 5) {
      fprintf(stdout, "ERROR!!\n");
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
  char original_word[20];
  strcpy(original_word, argv[1]);

  do_md5(original_word, hash);
  fprintf(stdout, "original_word: %s\n", original_word);
  fprintf(stdout, "hash to break: %s\n", hash);

	decrypt();
}


