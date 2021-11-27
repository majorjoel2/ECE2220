//Libraries used in this program
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

int openTerminal(FILE **curTermPtr, int *curTermNum);

int main(int argc, char *argv[]){
  FILE *terminal1, *terminal2, *terminal3, *terminal4;
  int currentTerminal = 1;
  openTerminal(&terminal1, &currentTerminal);
  openTerminal(&terminal2, &currentTerminal);
  openTerminal(&terminal3, &currentTerminal);
  openTerminal(&terminal4, &currentTerminal);
  return 0;
}

int openTerminal(FILE **curTermPtr, int *curTermNum){
  char terminalName[16];// "/dev/pts/#"
  sprintf(terminalName, "/dev/pts/%i", *curTermNum);
  (*curTermNum)++;
  printf("%s\n", terminalName);
  *curTermPtr = fopen(terminalName, "r");
  while(*curTermPtr == NULL){
    sprintf(terminalName, "/dev/pts/%i", *curTermNum);
    (*curTermNum)++;
    printf("%s\n", terminalName);
    *curTermPtr = fopen(terminalName, "r");
  }
  return 0;
}
