#include "md5.h"
#include <iostream>
#include <cmath>
#include <cstring>
#include <cstdlib>
#include <ctime>

// static char hash[50] = "098890dde069e9abad63f19a0d9e1f32"; // AAAA
// static char hash[50] = "6dd075556effaa6e7f1e3e3ba9fdc5fa"; // !!!
// static char hash[50] = "98abe3a28383501f4bfd2d9077820f11"; // !!!!
static char hash[50] = "f1b89141cdb7825d6a49876be05447ea"; // ++++

static unsigned long long int counter = 0;

int checkHash (char* word) {
  char output_hash[50];
  int di;

  md5_state_t state;
  md5_byte_t digest[16];  

  md5_init(&state);
  md5_append(&state, (const md5_byte_t *)word, strlen(word));
  md5_finish(&state, digest);

  for (di = 0; di < 16; di++)
    sprintf(output_hash + di * 2, "%02x", digest[di]); 

  // fprintf(stderr, "word: |%s|\n", word);
  if (!strcmp(hash, output_hash)) {
    fprintf(stdout, "HASH DECRYPTED!!\n");
    return 1;
  }
  return 0;
}

void addLetter (char* word, int* numberOfLetters) {
  int i;
  (*numberOfLetters)++;
  fprintf(stdout, "adding another letter.... total of %d letters\n", *numberOfLetters);
  for (i = 0; i < *numberOfLetters; i++) {
    word[i] = char(32);
  }
  word[*numberOfLetters] = (char)0;
}

int changeLetters (char* word, int letterIndex) {
  int i;
  for (i = 32; i < 127; i++) {
    word[letterIndex] = (char)i;
    // fprintf(stdout, "c: %d - w: |%s|\n", ++counter, word);
    if (checkHash(word)) {
      return 1;
    }
  }

  return 0;
}

int main(int argc, char *argv[])
{
  int i;
  int numberOfLetters = 0;
  char word[20];

  addLetter(word, &numberOfLetters);

  while (1) {
    if (changeLetters(word, numberOfLetters - 1)) return 1;

    i = (numberOfLetters == 1) ? 1 : numberOfLetters - 1;
    while (i--) {
      if ((int)word[i] == 126) {
        if (!i) {
          addLetter(word, &numberOfLetters);
        } else {
          word[i] = (char)32; // reset to space
        }
      } else {
        // Increment letter by 1
        word[i]++;
        if (checkHash(word)) return 1;
        break;
      }
    }

  }

  fprintf(stdout, "done\n");
}
