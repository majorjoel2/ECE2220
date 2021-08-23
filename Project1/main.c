/*
 * File Header Comment
 * gcc -Wall -g main.c -o p1.out
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

double gameBoard[5][5];
int dispPrintNum(int inputR, int inputC);
int dispPrintBoard();
int gameFillBoard();
int gameBoardUnique = 0;
int r, c, i;
time_t t;

int main(int arg, char **argv){
  srand((unsigned) time(&t));
  gameFillBoard();
  dispPrintBoard();
  return 1;
}

int gameFillBoard(){
  for(r = 0; r < 5; r++){
    for(c = 0; c < 5; c++){
      gameBoard[r][c] = (double) ((rand() % 19) + (c * 20) + 1);
      gameBoardUnique = r == 0;
      while(!gameBoardUnique){
        for(i = (r - 1); i >= 0; i--){
          if(gameBoard[r][c] == gameBoard[i][c]){
            i = r;
            gameBoard[r][c] = (double) ((rand() % 19) + (c * 20) + 1);
          }
        }
        gameBoardUnique = 1;
      }
      //printf("%i ", (int) gameBoard[r][c]);
    }
    //printf("\n");
  }
  gameBoard[2][2] = -1.1;
  return 1;
}

int dispPrintNum(int inputR, int inputC){
  if(gameBoard[inputR][inputC] < 0){
    if(gameBoard[inputR][inputC] == -1.1){
      printf(" Free ");
    } else {
      printf("  x   ");
    }
  } else {
    printf("  %i  ", (int) gameBoard[inputR][inputC]);
    if(gameBoard[inputR][inputC] < 10){
      printf(" ");
    }
  }
  return 1;
}

int dispPrintBoard(){
  printf("   C      O      V      I      D\n");
  printf("------------------------------------\n");
  printf("|");
  for(r = 0; r < 5; r++){
    for(c = 0; c < 5; c++){
      dispPrintNum(r,c);
      printf("|");
    }
    if(r != 4){
      printf("\n|------|------|------|------|------|\n|");
    }
  }
  printf("\n------------------------------------\n");
  return 1;
}
