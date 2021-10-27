
//Libraries used in this program
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

int numberOfLines(FILE *inputFile);
int lengthOfLine(FILE *inputFile);
int lengthOfDict(FILE *inputFile);
int dictBinarySearch(char **dictionary, int *wordlen, int first, int last, char *word);
void loadMemFromFile(FILE *fileToLoad, char **memPointer, int numOfLines, int *lineLengths);
int searchFileByLine(char **file, int *lens, int start, int end, int *lineFound, int *charFound, char *word);
void writeMemToFile(FILE *fileToSave, char **memPointer, int numOfLines, int *lineLengths);

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
  if(len == NULL) printf("ERROR: Failed to allocate len\n");
  lines = (char **)malloc(nol*sizeof(char*));
  if(lines == NULL) printf("ERROR: Failed to allocate lines\n");
  for(i = 0; i < nol; i++){
    len[i] = lengthOfLine(inputFile);
    //printf("Line Len %i = %i\n", i, len[i]);
    lines[i] = (char *)malloc(len[i]*sizeof(char));
    if(lines[i] == NULL) printf("ERROR: Failed to allocate lines[%i]\n", i);
  }
  dictLen = (int *)malloc(dictl*sizeof(int));
  if(dictLen == NULL) printf("ERROR: Failed to allocate dictLen\n");
  dict = (char **)malloc(dictl*sizeof(char*));
  if(dict == NULL) printf("ERROR: Failed to allocate dict\n");
  for(i = 0; i <dictl; i++){
    dictLen[i] = lengthOfDict(dictFile);
    //printf("Dict line Len %i = %i\n", i, dictLen[i]);
    dict[i] = (char *)malloc(dictLen[i]*sizeof(char));
    if(dict[i] == NULL) printf("ERROR: Failed to allocate dict[%i]\n", i);
  }
  loadMemFromFile(inputFile, lines, nol, len);
  loadMemFromFile(dictFile, dict, dictl, dictLen);

  FILE *outputFile;
  outputFile = fopen(argv[3], "w");
  writeMemToFile(outputFile, lines, nol, len);
  fclose(outputFile);

  /*printf("Dict 102384: ");
  for(i = 0; i < dictLen[102400]; i++){
    printf("%c", dict[102400][i]);
  }
  printf("\n");*/

  /*printf("len 894 %i\n", len[894]);
  printf("TXT 894: ");
  for(i = 0; i < len[894]; i++){
    printf("%c", *((*(lines+894))+i));//lines[896][i]);
  }
  printf("\n");*/

  //printf("dict 102400: %s\n", dict[500]);

  //printf("Search for A: %i\n", dictBinarySearch(dict, dictLen, 0, dictl-1, "Sus"));

  /*int fLN = 0, fCOL = 0;
  printf("wordLen: %i\n", searchFileByLine(lines, len, 9, nol, &fLN, &fCOL, "to"));
  printf("ln: %i\tcol: %i\n", fLN, fCOL);
  printf("wordLen: %i\n", searchFileByLine(lines, len, fLN, nol, &fLN, &fCOL, "to"));
  printf("ln: %i\tcol: %i\n", fLN, fCOL);*/

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

int lengthOfDict(FILE * inputFile){
  int output = 0;
  char c;
  for(c = getc(inputFile); c != '\n' && c != EOF; c = getc(inputFile)){
    output++;
  }
  //c = getc(inputFile);
  return ++output;
}

int dictBinarySearch(char **dictionary, int *wordlen, int first, int last, char *word){
  int i, middle;
  char *wordLower, *dictWordLower;
  wordLower = (char *)malloc(strlen(word)*sizeof(char));
  if(wordLower == NULL) printf("ERROR: Failed to allocate wordLower\n");
  for(i = 0; i < strlen(word); i++){
    wordLower[i] = tolower(word[i]);
  }

  while(first <= last){
    middle = first + (last-first) / 2;

    dictWordLower = (char *)malloc(wordlen[middle]*sizeof(char));
    if(dictWordLower == NULL) printf("ERROR: Failed to allocate dictWordLower\n");
    for(i = 0; i < wordlen[middle]; i++){
      dictWordLower[i] = tolower(dictionary[middle][i]);
    }
    dictWordLower[wordlen[middle]-1] = 0;

    //printf("Searching %i/%i/%s\n", middle, strcmp(wordLower, dictWordLower), dictWordLower);

    if(strcmp(wordLower, dictWordLower) == 0){
      free(wordLower);free(dictWordLower);
      return middle;
    }

    if(strcmp(wordLower, dictWordLower) > 0){
      first = middle + 1;
    } else {
      last = middle - 1;
    }

    free(dictWordLower);
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

int searchFileByLine(char **fileSearch, int *lens, int start, int end, int *lineFound, int *charFound, char *word){
  int wordLength = strlen(word);
  int i;
  char *found;
  for(i = start; i < end; i++){
    found = strstr(fileSearch[i], word);
    if(start == *lineFound && *charFound != 0){
      char *subString;
      subString = (char *)memcpy((void *)subString, (void *)(&fileSearch[start][*charFound+wordLength]), lens[start]-*charFound);
      //printf("Total: %s\nSub:%s", fileSearch[start], subString);
      found = strstr(subString, word);
      if(found){
        printf("Found %i, %p, %p\n", i, found, subString);
        *lineFound = i;
        *charFound = ((int)(found-subString)) + *charFound + wordLength;
        return wordLength;
      }
    } else {
      if(found){
        printf("Found %i, %p, %p\n", i, found, fileSearch[i]);
        *lineFound = i;
        *charFound = (int)(found-fileSearch[i]);
        return wordLength;
      }
    }
  }
  return -1;
}

void writeMemToFile(FILE *fileToSave, char **memPointer, int numOfLines, int *lineLengths){
  rewind(fileToSave);
  int i, j;
  char c;
  for(i = 0; i < numOfLines; i++){
    for(j = 0; j < lineLengths[i]; j++){
      c = memPointer[i][j];
      if(c == 10){
        putc(13, fileToSave);
      }
      putc(c, fileToSave);
      //printf("c:i:j:mem\t%i:%i:%i:%i\n", c, i, j, memPointer[i][j]);
      //printf("%c", memPointer[i][j]);
    }
  }
}
