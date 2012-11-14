#include "md5.h"
#include <iostream>
#include <cmath>
#include <cstring>
#include <cstdlib>
#include <ctime>


int do_md5 (const md5_byte_t* word, int index);
void gen_hashes (char** hash_table);
void init (char** hash_table);

int do_md5(const md5_byte_t* word, char* hash) {
  char output[33];
  int di;

  md5_state_t state;
  md5_byte_t digest[16];  

  md5_init(&state);
  // BEGIN append 1
    // md5_append(&state, (const md5_byte_t *)word, strlen(word));
    int nbytes = strlen((char*)word);
    int offset = (state.count[0] >> 3) & 63;
    md5_word_t nbits = (md5_word_t)(nbytes << 3);

    /* Update the message length. */
    state.count[1] += nbytes >> 29;
    state.count[0] += nbits;

    /* Process a final partial block. */
    memcpy(state.buf, word, nbytes);
  // END append 1

  md5_finish(&state, digest);
  
  for (di = 0; di < 16; di++) {
    sprintf(output + di * 2, "%02x", digest[di]); 
  }

  if (strcmp(output, hash)) {
    printf("hash for word |%s| should be %s but got %s\n\n", word, hash, output);
    return 0;
  }

  return 1;
}





int main (int argc, char *argv[]) {

  char** hash_table;
  int i;
  hash_table = (char**) malloc(sizeof(char*) * 60);

  for (i = 0; i < 60; i++) {
    hash_table[i] = (char*) malloc(sizeof(char) * 60 + 1);
  } // END loop 0

  init(hash_table);
  gen_hashes(hash_table);

  return 1;
}



void gen_hashes (char** hash_table) {
  md5_byte_t word[61];
  int i, j;
  int fails = 0;

  for (i = 0; i < 60; i++) {
    for (j = 0; j < i; j++) {
      word[j] = (char) 97;
    }
    word[j] = (char) 0;
    if (!do_md5(word, hash_table[i])) {
      fails++;
    }
  } // END loop 0
  printf("total fails: %d\n", fails);
}


void init (char** hash_table) {
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