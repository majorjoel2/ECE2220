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
int gameCheckDraw(int draw);
int gameCheckWin();
int gameBoardUnique = 0;
int r, c, i, sumR, sumC, drawCounter, gameCounter, gameDraw;
time_t t;
char charInput; //10 = Enter, 113 = q, 81 = Q
char covidStr[] = {'C', 'O', 'V', 'I', 'D'};

int main(int arg, char **argv){
  gameCounter = 0;
  srand((unsigned) time(&t));
  drawCounter = 0;
  gameFillBoard();
  dispPrintBoard();
  printf("Press \'Enter\' to generate a Square (or \'q\' to [Quit]) ");
  scanf("%c",&charInput);
  while(!gameCheckWin() && charInput == 10){
    gameDraw = (rand() % 98) + 1;
    gameCheckDraw(gameDraw);
    drawCounter++;
    printf("%i: %c-%i\n", drawCounter, covidStr[(int) (gameDraw/20)], gameDraw);
    dispPrintBoard();
    printf("Press \'Enter\' to generate next Square (or \'q\' to [Quit])");
    scanf("%c",&charInput);
  }
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

int gameCheckDraw(int draw){
  for(r = 0; r < 5; r++){
    for(c = 0; c < 5; c++){
      if(gameBoard[r][c] == draw){
        gameBoard[r][c] = -1;
      }
    }
  }
  return 1;
}

int gameCheckWin(){
  for(r = 0; r < 5; r++){
    sumR = 0;
    sumC = 0;
    for(c = 0; c < 5; c++){
      sumR = sumR + ((int) gameBoard[r][c]);
      sumC = sumC + ((int) gameBoard[c][r]);
      if(sumR <= -5 || sumC <= -5){
        return 1;
      }
    }
  }
  sumR = gameBoard[0][0] + gameBoard[1][1] + gameBoard[3][3] + gameBoard[4][4];
  sumC = gameBoard[0][4] + gameBoard[1][3] + gameBoard[3][1] + gameBoard[4][0];
  if(sumR == -4 || sumC == -4){
    return 1;
  }
  return 0;
}
