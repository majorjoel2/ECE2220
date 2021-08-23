/*
 * File Header Comment
 * gcc -Wall -g main.c -o p1.out
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

double gameBoard[5][5];
int dispPrintCovid();
int gameFillBoard();
int r, c;
time_t t;

int main(int arg, char **argv){
  srand((unsigned) time(&t));
  dispPrintCovid();
  gameFillBoard();
  return 1;
}

int gameFillBoard(){
  for(r = 0; r < 5; r++){
    for(c = 0; c < 5; c++){
      gameBoard[r][c] = (double) ((rand() % 19) + (c * 20) + 1);
      printf("%i ", (int) gameBoard[r][c]);
    }
    printf("\n");
  }
  gameBoard[2][2] = -1.1;
  return 1;
}

int dispPrintCovid(){
  printf("   C      O      V      I      D\n");
  return 1;
}
