
//Libraries used in this program
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

int numberOfLines(FILE *inputFile);
int lengthOfLine(FILE *inputFile);
int dictBinarySearch(char **dictionary, int first, int last, char *word);
void loadMemFromFile(FILE *fileToLoad, char **memPointer, int numOfLines, int *lineLengths);

int main(int argc, char *argv[]){
  char **lines, **dict;

  char dictLocation[64] = "/usr/share/dict/";
  FILE *dictFile = fopen(strcat(dictLocation, argv[1]), "r");
  printf("Dictionary: %p\n", dictFile);
  FILE *inputFile = fopen(argv[2], "r");
  printf("Input File: %p\n", inputFile);
  printf("1: %li\t", ftell(inputFile));
  int nol = numberOfLines(inputFile);
  int dictl = numberOfLines(dictFile);
  printf("4: %li\n", ftell(inputFile));
  printf("NOL: %i\n", nol);
  int i, *len, *dictLen;
  len = (int *)malloc(nol*sizeof(int));
  lines = (char **)malloc(nol*sizeof(char*));
  for(i = 0; i < nol; i++){
    len[i] = lengthOfLine(inputFile);
    //printf("Line Len %i = %i\n", i, len[i]);
    lines[i] = (char *)malloc(len[i]*sizeof(char));
  }
  dictLen = (int *)malloc(dictl*sizeof(int));
  dict = (char **)malloc(dictl*sizeof(char*));
  for(i = 0; i <dictl; i++){
    dictLen[i] = lengthOfLine(dictFile);
    //printf("Dict line Len %i = %i\n", i, dictLen[i]);
    dict[i] = (char *)malloc(dictLen[i]*sizeof(char));
  }
  loadMemFromFile(inputFile, lines, nol, len);
  //loadMemFromFile(dictFile, dict, dictl, dictLen);

  /*printf("Dict 102384: ");
  for(i = 0; i < dictLen[102400]; i++){
    printf("%c", dict[102400][i]);
  }
  printf("\n");*/

  printf("len 894 %i\n", len[894]);
  printf("TXT 894: ");
  for(i = 0; i < len[894]; i++){
    printf("%c", *((*(lines+894))+i));//lines[896][i]);
  }
  printf("\n");

  return 0;
}

int numberOfLines(FILE *inputFile){
  int output = 0;
  char c, cLast;
  printf("2: %li\t", ftell(inputFile));
  for(c = getc(inputFile); c != EOF; c = getc(inputFile)){
    if(c == '\n'){
      output++;
    }
    cLast = c;
  }
  if(cLast != '\n'){
    output++;
  }
  printf("3: %li\t", ftell(inputFile));
  rewind(inputFile);
  return output;
}

int lengthOfLine(FILE * inputFile){
  int output = 0;
  char c;
  for(c = getc(inputFile); c != '\n' && c != EOF; c = getc(inputFile)){
    output++;
  }
  //c = getc(inputFile);
  return output;
}

int dictBinarySearch(char **dictionary, int first, int last, char *word){
  int i;
  if(last >= first){
    int middle = 1 + (last-1) / 2;
    char *wordLower, *dictWordLower;
    wordLower = (char *)malloc(strlen(word)*sizeof(char));
    for(i = 0; i < strlen(word); i++){
      wordLower[i] = tolower(word[i]);
    }
  }
  return -1;
}

void loadMemFromFile(FILE *fileToLoad, char **memPointer, int numOfLines, int *lineLengths){
  rewind(fileToLoad);
  int i, j;
  char c;
  for(i = 0; i < numOfLines; i++){
    for(j = 0; j < lineLengths[i]; j++){
      c = getc(fileToLoad);
      if(c == 13){
        c = getc(fileToLoad);
      }
      memPointer[i][j] = c;
      //printf("c:i:j:mem\t%i:%i:%i:%i\n", c, i, j, memPointer[i][j]);
      //printf("%c", memPointer[i][j]);
    }
  }
  rewind(fileToLoad);
}
