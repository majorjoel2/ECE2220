//Libraries used in this program
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>
#include <sys/mman.h>
#include <signal.h>

#define CRASHED  0b00000001
#define BOMBLESS 0b00000010
#define LANDED   0b00000100
#define QUIT     0b10000000
#define BOMBER1  0x000000FF
#define BOMBER2  0x0000FF00
#define BOMBER3  0x00FF0000

//These need to be global because the base and bomber control need access to
//the pid values for them to be able to be read across forks.
static int *t1PID, *t2PID, *t3PID, *activePlanes;

//These need to be global variables so that the signal handlers can manipulate them
int fuel = 100, bombs = 8, crashedPlane = 0;

int openTerminal(FILE **curTermPtr, int *curTermNum);
int baseControl(FILE *openTerminal);
int bomberControl(FILE *openTerminal, int id);
int writeBomberPID(int whichBomber, int bomberPID);
int getPID(int id);
void bombsAway(int sig);
void refuelBomber(int sig);
void planeCrash(int sig);
int getBomber(int id);

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
  printf("pp %i\n", getpid());

  //Make vaiables that can be used across the fork
  t1PID = mmap(NULL, sizeof(*t1PID), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
  t2PID = mmap(NULL, sizeof(*t2PID), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
  t3PID = mmap(NULL, sizeof(*t3PID), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
  activePlanes = mmap(NULL, sizeof(*activePlanes), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);

  *activePlanes = 0x00040404;

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
    bomberControl(tBomber[currentBomber], currentBomber);
  } else if(forkTracker == 0){
    //Primary process
    //Therefore spawn base process
    fprintf(tBase, "Base with id %i\n", getpid());
    //printf("pids %i %i %i\n", *t1PID, *t2PID, *t3PID);
    baseControl(tBase);
    kill(*t1PID, SIGKILL);
    kill(*t2PID, SIGKILL);
    kill(*t3PID, SIGKILL);
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

int getPID(int id){
  switch(id){
    case 0:
      return *t1PID;

    case 1:
      return *t2PID;

    case 2:
      return *t3PID;
  }
  return 0;
}

int getBomber(int id){
  switch(id){
    case 0:
      return BOMBER1;

    case 1:
      return BOMBER2;

    case 2:
      return BOMBER3;
  }
  return 0;
}

int baseControl(FILE *openTerminal){
  int loop = 0;
  char input[16];
  char command[8];
  int inputID = -1;
  signal(SIGUSR2, planeCrash);
  while(loop == 0){
    fprintf(openTerminal, "Command list: launch, bomb [id], refuel [id], status, quit\n");
    printf("Enter Command: ");
    fgets(input,16,stdin);
    sscanf(input, "%s%i", command, &inputID);
    //printf("cmp %i\n", strcmp(command, "launch"));
    //printf("cmd %s, id %i\n", input, inputID);
    if(strcmp(command, "launch") == 0){
      //launch
      if((getBomber(0) & *activePlanes) != 0){
        //launch bomber 1
        *activePlanes &= (0xFFFFFFFF ^ getBomber(0));
      } else if((getBomber(1) & *activePlanes) != 0){
        //launch bomber 2
        *activePlanes &= (0xFFFFFFFF ^ getBomber(1));
      } else if((getBomber(2) & *activePlanes) != 0){
        //launch bomber 3
        *activePlanes &= (0xFFFFFFFF ^ getBomber(2));
      } else {
        printf("No more planes remaining\n");
      }
    }
    if(strcmp(command, "bomb") == 0){
      kill(inputID, SIGUSR1);
    }
    if(strcmp(command, "refuel") == 0){
      kill(inputID, SIGUSR2);
    }
    if(strcmp(command, "status") == 0){
      fprintf(openTerminal, "Bomber %i %s\n", getPID(0), ((getBomber(0) & *activePlanes) == 0) ? "Flying" : "Landed");
      fprintf(openTerminal, "Bomber %i %s\n", getPID(1), ((getBomber(1) & *activePlanes) == 0) ? "Flying" : "Landed");
      fprintf(openTerminal, "Bomber %i %s\n", getPID(2), ((getBomber(2) & *activePlanes) == 0) ? "Flying" : "Landed");
    }
    if(strcmp(command, "quit") == 0){
      //quit
      loop = -1;
    }
  }
  return 0;
}

int bomberControl(FILE *openTerminal, int id){
  int runBomber = 0;
  signal(SIGUSR1, bombsAway);
  signal(SIGUSR2, refuelBomber);
  while(runBomber == 0){
    if((getBomber(id) & *activePlanes) == 0){
      //launch plane
      fuel = 100;
      bombs = 8;
      int upTime = 0, lastBomb = bombs;
      while(upTime >= 0){
        if(upTime % 3 == 0){
          //print fuel and bombs
          fprintf(openTerminal, "Bombardier %i to base, %i gallons left and %i bombs left\n", getPID(id), fuel, bombs);
        }
        if(fuel <= 5){
          fprintf(openTerminal, "Plane %i almost out of Fuel!\n", getPID(id));
        }
        if(fuel <= 0){
          *activePlanes |= (CRASHED << (id * 8));
          //kill((getppid()+1), SIGUSR2);
          fprintf(openTerminal, "Mayday, mayday! Plane %i ditching.\n", getPID(id));
          upTime = -404;
        }
        while(lastBomb != bombs){
          lastBomb--;
          fprintf(openTerminal, "Bombardier %i to base, bomb dropped, %i bombs left\n", getPID(id), lastBomb);
        }
        if(bombs <= 0){
          *activePlanes |= (BOMBLESS << (id * 8));
          fprintf(openTerminal, "Bombay Empty, Returning Home\n");
          upTime = -100;
        }
        upTime++;
        fuel -= 5;
        sleep(1);
      }
    }
  }
  return 0;
}

void bombsAway(int sig){
  //Dropping bomb
  bombs--;
}

void refuelBomber(int sig){
  //Fill Fuel
  fuel = 100;
}

void planeCrash(int sig){
  if((*activePlanes & (CRASHED)) == (CRASHED)){
    //Bomber 1 crashed
    printf("Vaya con Dios, flight %i\n", *t1PID);
    *activePlanes ^= (CRASHED << (0 * 8));
    *activePlanes |= (LANDED);
  }
  if((*activePlanes & (CRASHED << 8)) == (CRASHED << 8)){
    //Bomber 2 crashed
    printf("Vaya con Dios, flight %i\n", *t2PID);
    *activePlanes ^= (CRASHED << (1 * 8));
    *activePlanes |= (LANDED << 8);
  }
  if((*activePlanes & (CRASHED << 16)) == (CRASHED << 16)){
    //Bomber 3 crashed
    printf("Vaya con Dios, flight %i\n", *t3PID);
    *activePlanes ^= (CRASHED << (2 * 8));
    *activePlanes |= (LANDED << 16);
  }
}
