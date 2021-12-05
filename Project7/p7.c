//Libraries used in this program
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>
#include <sys/mman.h>

//These need to be global because the base and bomber control need access to
//the pid values for them to be able to be read across forks.
static int *t1PID, *t2PID, *t3PID;

int openTerminal(FILE **curTermPtr, int *curTermNum);
int baseControl(FILE *openTerminal);
int bomberControl(FILE *openTerminal);
int writeBomberPID(int whichBomber, int bomberPID);

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

  //Make vaiables that can be used across the fork
  t1PID = mmap(NULL, sizeof(*t1PID), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
  t2PID = mmap(NULL, sizeof(*t2PID), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
  t3PID = mmap(NULL, sizeof(*t3PID), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);

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
    writeBomberPID(currentBomber, getpid());
  } else if(forkTracker == 0){
    //Primary process
    //Therefore spawn base process
    fprintf(tBase, "Base with id %i\n", getpid());
    //printf("pids %i %i %i\n", *t1PID, *t2PID, *t3PID);
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
  *curTermPtr = fopen(terminalName, "r+");
  while(*curTermPtr == NULL && *curTermNum < 1000){
    sprintf(terminalName, "/dev/pts/%i", *curTermNum);
    (*curTermNum)++;
    //printf("%s\n", terminalName);
    *curTermPtr = fopen(terminalName, "r+");
  }
  return 0;
}

int writeBomberPID(int whichBomber, int bomberPID){
  switch(whichBomber){
    case 0:
      *t1PID = bomberPID;
      break;

    case 1:
      *t2PID = bomberPID;
      break;

    case 2:
      *t3PID = bomberPID;
      break;
  }
  return 0;
}


int baseControl(FILE *openTerminal){
  return 0;
}

int bomberControl(FILE *openTerminal){
  return 0;
}
