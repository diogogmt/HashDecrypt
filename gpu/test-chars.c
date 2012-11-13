#include <stdio.h>


int main () {

  for (;;){
    printf("inside the new scope - before\n");
    break;
    printf("inside the new scope - after\n");
  }

  printf("inside main\n");

  char a = 1;
  char b = 2;
  char c = a + b;
  char d = 128;
  printf ("c: %d\n", c);
  printf ("d: %d\n", d);

  char test[4];
  test[0] = 'a';
  test[1] = 'b';
  test[2] = 'c';
  test[3] = 'd';

  printf("test+1: %c\n", test+1);

  return 0;
}
