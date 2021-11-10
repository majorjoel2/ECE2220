
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
void dumpMem(char ***memPointer, int numOfLines, int **lineLengths);
void allocateMem(FILE *openFile, char ***memPointer, int *numOfLines, int **lineLengths);
void allocateDict(FILE *openFile, char ***memPointer, int *numOfLines, int **lineLengths);
void replaceWord(char **memPointer, int *lineLengths, int lineIndex, int charIndex, int oldWordLength, char *newWord);
int dictLinearSearch(char **dictionary, int *wordlen, int first, int last, char *word);

int main(int argc, char *argv[]){

  if(argc != 4){
    printf("Wrong number of args\n");
    return 1;
  }
  char **lines, **dict;

  char dictLocation[64] = "/usr/share/dict/";
  FILE *dictFile = fopen(strcat(dictLocation, argv[3]), "r");
  if(dictFile == NULL){
    printf("ERROR: Failed to load Dictionary\n");
    return 1;
  }
  FILE *inputFile = fopen(argv[1], "r");
  if(inputFile == NULL) {
    printf("ERROR: Failed to load Input File\n");
    return 1;
  }

  int fileNOL = 0, *fileLineLengths, dictNOL = 0, *dictLineLengths;
  allocateMem(inputFile, &lines, &fileNOL, &fileLineLengths);
  allocateDict(dictFile, &dict, &dictNOL, &dictLineLengths);
  printf("NOL: %i:%i\n", fileNOL, dictNOL);

  loadMemFromFile(inputFile, lines, fileNOL, fileLineLengths);
  loadMemFromFile(dictFile, dict, dictNOL, dictLineLengths);

  int exitLoop = 0;
  while(exitLoop == 0){
    printf("[SP]Spell check\n[SE]Search\n[SR]Search and Replace\n[SA]Save\n[EX]Exit\n");
    char optionInput[32];
    scanf("%s", optionInput);

    if(tolower(optionInput[0]) == 's' && tolower(optionInput[1]) == 'p'){
      //spell check
      int exitSP = 0, line, length, word;
      char spellingWord[128];
      while(exitSP == 0){

        //printf("line:%i,len:%i\n", line, length);
        //printf("dict:(%i,%c)\n", lines[line][length],lines[line][length]);
        if(isalpha(lines[line][length]) != 0){
          //printf("is alpha %c\n", lines[line][length]);
          spellingWord[word] = lines[line][length];
          word++;
        }

        if(isalpha(lines[line][length]) == 0 && word != 0){
          //printf("found word\n");
          //found a word
          spellingWord[word] = 0;
          if(dictBinarySearch(dict, dictLineLengths, 0, dictNOL, spellingWord) == -1){
            printf("Word not found %s at line %i with index %i\n", spellingWord, line, length);
          } else {
            //printf("Word found %s\n", spellingWord);
          }
          word = 0;
        }

        length++;
        if(length >= fileLineLengths[line]){
          if(line+1 >= fileNOL){
            spellingWord[word] = 0;
            if(dictBinarySearch(dict, dictLineLengths, 0, dictNOL, spellingWord) == -1){
              printf("Word not found %s at line %i with index %i\n", spellingWord, line, length);
            } else {
              //printf("Word found %s\n", spellingWord);
            }
            word = 0;
          }
          //printf("new line\n");
          length = 0;
          line++;
          word = 0;
        }
        if(line >= fileNOL){
          exitSP = 1;
        }
      }

    }
    if(tolower(optionInput[0]) == 's' && tolower(optionInput[1]) == 'e'){
      //Search
      char searchString[65];
      char currentLetter, dummyClear = 0;
      int validInput, i;
      while(dummyClear != 10){
        scanf("%c", &dummyClear);
      }
      printf("Enter string to search: ");
      scanf("%c", &currentLetter);
      if(currentLetter != 10){
        searchString[0] = currentLetter;
        i = 1;
        validInput = 0;
        while(!validInput){
          scanf("%c", &currentLetter);
          if(currentLetter == 10 || i == 64){
            validInput = 1;
            searchString[i] = 0;
            if(i == 64 && currentLetter != 10){
              dummyClear = 0;
              while(dummyClear != 10){
                scanf("%c", &dummyClear);
              }
            }
          } else {
            searchString[i] = currentLetter;
          }
          i++;
        }
      } else {
        //error out if nothing passed in
        printf("Bad/no Input\n");
        return 1;
      }
      //String input read
      int foundLine = 0, foundIndex = 0;
      int lengthOfFoundWord = searchFileByLine(lines, fileLineLengths, foundLine, fileNOL, &foundLine, &foundIndex, searchString);
      if(lengthOfFoundWord == -1){
        printf("None found!\n");
      } else {
        while(lengthOfFoundWord != -1){
          printf("Found string at line: %i with index: %i and length: %i\nThe line is: %s", foundLine+1, foundIndex, lengthOfFoundWord, lines[foundLine]);
          lengthOfFoundWord = searchFileByLine(lines, fileLineLengths, foundLine, fileNOL, &foundLine, &foundIndex, searchString);
        }
      }
    }
    if(tolower(optionInput[0]) == 'e' && tolower(optionInput[1]) == 'x'){
      return 0;
    }
  }

  FILE *outputFile;
  outputFile = fopen(argv[2], "w");
  writeMemToFile(outputFile, lines, fileNOL, fileLineLengths);
  fclose(outputFile);

  return 0;
}

int numberOfLines(FILE *inputFile){
  int output = 0;
  char c, cLast;
  //printf("2: %li\t", ftell(inputFile));
  for(c = getc(inputFile); c != EOF; c = getc(inputFile)){
    if(c == '\n'){
      output++;
    }
    cLast = c;
  }
  if(cLast != '\n'){
    output++;
  }
  //printf("3: %li\t", ftell(inputFile));
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
  wordLower = (char *)malloc((strlen(word)+1)*sizeof(char));
  if(wordLower == NULL) printf("ERROR: Failed to allocate wordLower\n");
  //printf("len:%li ", strlen(word));
  for(i = 0; i < strlen(word); i++){
    wordLower[i] = tolower(word[i]);
    //printf("char:%i,%c ", wordLower[i], wordLower[i]);
  }
  //printf("i:%i ", i);
  wordLower[i] = 0;
  return dictLinearSearch(dictionary, wordlen, first, last, wordLower);
  //printf("B_lenw:%li\n",strlen(wordLower));

  while(first <= last){
    middle = first + (last-first) / 2;

    dictWordLower = (char *)malloc(wordlen[middle]*sizeof(char));
    if(dictWordLower == NULL) printf("ERROR: Failed to allocate dictWordLower\n");
    for(i = 0; i < strlen(word); i++){
      dictWordLower[i] = tolower(dictionary[middle][i]);
    }
    dictWordLower[wordlen[middle]-1] = 0;

    //printf("SearchingB %i/%i/%s\n", middle, strcmp(wordLower, dictWordLower), dictWordLower);

    if(strcmp(wordLower, dictWordLower) == 0){
      free(dictWordLower);
      return dictLinearSearch(dictionary, wordlen, first, middle+1, wordLower);
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

int dictLinearSearch(char **dictionary, int *wordlen, int first, int last, char *word){
  int i, curLine;
  char *dictWordLower;

  //printf("First: %i, last: %i\n", first, last);
  for(curLine = first; curLine < last; curLine++){
    dictWordLower = (char *)malloc(wordlen[curLine]*sizeof(char));
    if(dictWordLower == NULL) printf("ERROR: Failed to allocate dictWordLower\n");
    for(i = 0; i < wordlen[curLine]; i++){
      dictWordLower[i] = tolower(dictionary[curLine][i]);
    }
    dictWordLower[wordlen[curLine]-1] = 0;

    //if(curLine == first) printf("SearchingL %i/%i/%s/%s\n", curLine, strcmp(word, dictWordLower), dictWordLower, word);
    //printf("SearchingL %i/%i/%s/%s\n", curLine, strcmp(word, dictWordLower), dictWordLower, word);

    if(strcmp(word, dictWordLower) == 0){
      free(word);free(dictWordLower);
      return curLine;
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
    if(i == *lineFound && *charFound != 0){
      char *subString;
      subString = (char *)malloc((lens[start]-*charFound)*sizeof(char));
      memcpy(subString, (&fileSearch[start][*charFound+wordLength]), lens[start]-*charFound);
      //printf("Total: %s\nSub:%s", fileSearch[start], subString);
      found = strstr(subString, word);
      if(found){
        //printf("Found %i, %p, %p\n", i, found, subString);
        *lineFound = i;
        *charFound = ((int)(found-subString)) + *charFound + wordLength;
        free(subString);
        return wordLength;
      }
      free(subString);
    } else {
      if(found){
        //printf("Found %i, %p, %p\n", i, found, fileSearch[i]);
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

void dumpMem(char ***memPointer, int numOfLines, int **lineLengths){
  int i;
  for(i = 0; i < numOfLines; i++){
    free(*memPointer[i]);
  }
  free(*memPointer);
  free(*lineLengths);
}

void allocateMem(FILE *openFile, char ***memPointer, int *numOfLines, int **lineLengths){
  int i;
  *numOfLines = numberOfLines(openFile);
  *lineLengths = (int *)malloc(*numOfLines*sizeof(int));
  if(*lineLengths == NULL) printf("ERROR: Failed to allocate lineLengths\nCode: %p\n", openFile);
  *memPointer = (char **)malloc(*numOfLines*sizeof(char*));
  if(*memPointer == NULL) printf("ERROR: Failed to allocate memPointer\nCode: %p\n", openFile);
  for(i = 0; i < *numOfLines; i++){
    (*lineLengths)[i] = lengthOfLine(openFile);
    //printf("Line Len %i = %i\n", i, len[i]);
    (*memPointer)[i] = (char *)malloc(((*lineLengths)[i])*sizeof(char));
    if((*memPointer)[i] == NULL) printf("ERROR: Failed to allocate memPointer[%i]\nCode: %p\n", i, openFile);
  }
}

void allocateDict(FILE *openFile, char ***memPointer, int *numOfLines, int **lineLengths){
  int i;
  *numOfLines = numberOfLines(openFile);
  *lineLengths = (int *)malloc(*numOfLines*sizeof(int));
  if(*lineLengths == NULL) printf("ERROR: Failed to allocate lineLengths\nCode: %p\n", openFile);
  *memPointer = (char **)malloc(*numOfLines*sizeof(char*));
  if(*memPointer == NULL) printf("ERROR: Failed to allocate memPointer\nCode: %p\n", openFile);
  for(i = 0; i < *numOfLines; i++){
    (*lineLengths)[i] = lengthOfDict(openFile);
    //printf("Line Len %i = %i\n", i, len[i]);
    (*memPointer)[i] = (char *)malloc(((*lineLengths)[i])*sizeof(char));
    if((*memPointer)[i] == NULL) printf("ERROR: Failed to allocate memPointer[%i]\nCode: %p\n", i, openFile);
  }
}

void replaceWord(char **memPointer, int *lineLengths, int lineIndex, int charIndex, int oldWordLength, char *newWord){
  int oldLineLength = lineLengths[lineIndex];
  int newLineLength = oldLineLength - oldWordLength + strlen(newWord);
  char *newLine = (char *)malloc(newLineLength*sizeof(char));
  if(newLine == NULL) printf("ERROR: Failed to allocate newLine\n");
  lineLengths[lineIndex] = newLineLength;
  char *subString, *subString2;
  subString = (char *)malloc(charIndex*sizeof(char));
  if(subString == NULL) printf("ERROR: Failed to allocate subString\n");
  subString = (char *)memcpy((void *)subString, (void *)memPointer[lineIndex], charIndex);
  strcpy(newLine, subString);
  strcat(newLine, newWord);
  subString2 = (char *)malloc((newLineLength - charIndex - strlen(newWord))*sizeof(char));
  if(subString2 == NULL) printf("ERROR: Failed to allocate subString2\n");
  subString2 = (char *)memcpy((void *)subString2, (void *)(&memPointer[lineIndex][charIndex + oldWordLength]), newLineLength - charIndex - strlen(newWord));
  strcat(newLine, subString2);
  free(memPointer[lineIndex]);
  memPointer[lineIndex] = (char *)malloc(newLineLength*sizeof(char));
  if(memPointer[lineIndex] == NULL) printf("ERROR: Failed to allocate memPointer[%i]\n", lineIndex);
  strcpy(memPointer[lineIndex], newLine);
}
