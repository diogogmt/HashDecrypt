#include "md5.h"
#include <iostream>
#include <cmath>
#include <cstring>
#include <cstdlib>
#include <ctime>

static char hash[50] = "c746fa0a74266205f92157f0f3f17f50";


void do_md5(const char * word, char * output)
{

	char hex_output[16*2 + 1];
	int di;

	md5_state_t state;
	md5_byte_t digest[16];	

	md5_init(&state);
	md5_append(&state, (const md5_byte_t *)word, strlen(word));
	md5_finish(&state, digest);

	for (di = 0; di < 16; di++)
		sprintf(output + di * 2, "%02x", digest[di]); 
}


int checkHash (char* word) {
	// fprintf(stderr, "checkHash\n");

	char output_hash[50];

	// check md5
	fprintf(stderr, "word: |%s|\n", word);
	do_md5(word, output_hash);

	if (!strcmp(hash, output_hash)) {
		fprintf(stderr, "HASH DECRYPTED!!\n");
		return 1;
	}

	return 0;
}

void addLetter (char* word, int* numberOfLetters) {
	fprintf(stderr, "addLetter\n");
	int i;
	(*numberOfLetters)++;
	for (i = 0; i < *numberOfLetters; i++) {
		word[i] = char(32);
	}
	word[*numberOfLetters] = (char)0;
}

int changeLetters (char* word, int letterIndex) {
	fprintf(stderr, "changeWord\n");
	int i;
	for (i = 32; i < 127; i++) {
		word[letterIndex] = (char)i;
		if (checkHash(word)) {
			return 1;
		}
	}

	return 0;
}



void decrypt (char* hash) {

	fprintf(stderr, "decrypt\n");


	int i;
	int numberOfLetters = 0;
	char word[20];

	addLetter(word, &numberOfLetters);

	while (1) {
		if (changeLetters(word, numberOfLetters - 1)) {
			return;
		}

		if (numberOfLetters == 5) {
			fprintf(stderr, "ERROR!!\n");
			return;
		}

		i = (numberOfLetters == 1) ? 1 : numberOfLetters - 1;
		while (i--) {
			if ((int)word[i] == 126 && !i) {
				addLetter(word, &numberOfLetters);
			} else {
				word[i]++;
				if (checkHash(word)) {
					return;
				}
				break;
			}			
		}
	}

	fprintf(stderr, "done\n");
}

int main(int argc, char *argv[])
{
	fprintf(stderr, "main\n");


	decrypt(hash);
}



