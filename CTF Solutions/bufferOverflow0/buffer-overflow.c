/* How to compile 
 * gcc -m32 -g -z execstack -fno-stack-protector -o buffer-flow  buffer-flow .c -lcrypt */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <crypt.h>
int i;

int verify_pass(char *password) {
  char buffer[16];
  int verified = 0;
  i = 0;
  while(password[i]) { buffer[i]=password[i]; i++;}
  if(strcmp(crypt(buffer,"CS"), "CSrCDBjX240fc") == 0)
    verified = 1;
  return verified;
}

void prize() {
  printf("You won a hidden prize.\n");
}

int main(int argc, char *argv[], char *envp[]) {
  char input[500];
  scanf(input);
  if(verify_pass(argv[1])) {
      printf("\n      Correct Password Entered.\n");
  } else {
      printf("\n      Wrong Password Entered.\n");
  }
  return (0);
}

