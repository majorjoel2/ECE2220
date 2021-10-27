
//Libraries used in this program
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

int numberOfLines(FILE *inputFile);
int lengthOfLine(FILE * inputFile);

int main(int argc, char *argv[]){
  char dictLocation[64] = "/usr/share/dict/";
  printf("Dictionary: %p\n", fopen(strcat(dictLocation, argv[1]), "r"));
  FILE *inputFile = fopen(argv[2], "r");
  printf("Input File: %p\n", inputFile);
  printf("1: %li\t", ftell(inputFile));
  int nol = numberOfLines(inputFile);
  printf("4: %li\n", ftell(inputFile));
  printf("NOL: %i\n", nol);
  int i, *len;
  len = (int *)malloc(nol*sizeof(int));
  for(i = 0; i < nol; i++){
    len[i] = lengthOfLine(inputFile);
    printf("Line Len %i = %i\n", i, len[i]);
  }
  return 0;
}

int numberOfLines(FILE *inputFile){
  int output = 0;
  char c;
  printf("2: %li\t", ftell(inputFile));
  for(c = getc(inputFile); c != EOF; c = getc(inputFile)){
    if(c == '\n'){
      output++;
    }
  }
  printf("3: %li\t", ftell(inputFile));
  rewind(inputFile);
  return output;
}

int lengthOfLine(FILE * inputFile){
  int output = 0;
  char c;
  for(c = getc(inputFile); c != '\n'; c = getc(inputFile)){
    output++;
  }
  //c = getc(inputFile);
  return output;
}
