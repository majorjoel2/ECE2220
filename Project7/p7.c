//Libraries used in this program
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>

int openTerminal(FILE **curTermPtr, int *curTermNum);
int baseControl(FILE *openTerminal);
int bomberControl(FILE *openTerminal);

int main(int argc, char *argv[]){
  FILE *tBase, *tBomber[3];
  int currentTerminal = 1, forkTracker = -1, currentBomber = 0;
  openTerminal(&tBase, &currentTerminal);
  openTerminal(&tBomber[0], &currentTerminal);
  openTerminal(&tBomber[1], &currentTerminal);
  openTerminal(&tBomber[2], &currentTerminal);
  //printf("term num %i\n", currentTerminal);
  if(currentTerminal >= 1000){
    printf("ERROR 104: No open Terminals. Open four terminals.\n");
    return 104;
  }

  //Dtsplay Program Start time
  time_t t = time(NULL);
  struct tm tm = *localtime(&t);
  printf("%d-%02d-%02d %02d:%02d:%02d\n", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);

  //Make bomber forks
  forkTracker = fork();
  while(forkTracker == 0 && currentBomber < 3){
    //printf("fk: %i; cb: %i\n", forkTracker, currentBomber);
    currentBomber++;
    if(currentBomber < 3){
      forkTracker = fork();
    }
  }

  //Use bomber forks
  printf("fk: %i; cb: %i\n", forkTracker, currentBomber);
  if(forkTracker > 0){
    //Not zero and not fork error
    //Therefore spawn bomber process
    fprintf(tBomber[currentBomber], "Bomber with id %i\n", getpid());
  } else if(forkTracker == 0){
    //Primary process
    //Therefore spawn base process
    fprintf(tBase, "Base with id %i\n", getpid());
  } else {
    printf("ERROR 106: Failed to make Fork\n");
    return 106;
  }

  fclose(tBase);
  fclose(tBomber[0]);
  fclose(tBomber[1]);
  fclose(tBomber[2]);
  return 0;
}

int openTerminal(FILE **curTermPtr, int *curTermNum){
  char terminalName[16];// "/dev/pts/#"
  sprintf(terminalName, "/dev/pts/%i", *curTermNum);
  (*curTermNum)++;
  //printf("%s\n", terminalName);
  *curTermPtr = fopen(terminalName, "r");
  while(*curTermPtr == NULL && *curTermNum < 1000){
    sprintf(terminalName, "/dev/pts/%i", *curTermNum);
    (*curTermNum)++;
    //printf("%s\n", terminalName);
    *curTermPtr = fopen(terminalName, "r");
  }
  return 0;
}
