/**
 * Joel Tanner
 * 08-25-2021
 *
 * The goal of this project is to be a playable BINGO game styalized as COVID.
 * The program will display the board at every number draw and loop to play
 * multiple games. The program will keep track of games played and numbers
 * drawn for each game.
 */

//Libraries used in this program
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/**
 * This function will print the number in the game board arrray for the selected
 * row and coloumn. The function will print an x for already drawn numbers. The
 * function will also print free in the center of the board.
 *
 * @param inputR the row of the number to print
 * @param inputC the column of the number to print
 */
int dispPrintNum(int inputR, int inputC);
/**
 * This function will print the whole board. It calles dispPrintNum for each
 * number printed.
 */
int dispPrintBoard();
/**
 * This function will fill the array gameBoard with unique random numbers per
 * the set range for each column.
 */
int gameFillBoard();
/**
 * This function will check if the number drawn is a number on the board. If the
 * number drawn is on the board it will clearn the number from the array so that
 * when the board is printed the next time an x is printed
 *
 * @param draw the number to check
 */
int gameCheckDraw(int draw);
/**
 * This function will check all win conditions on the board. If there is a win
 * condition the function will return 1 (True) else the function will
 * return 0 (False)
 *
 * @return int (Bool) 1 if win else 0
 */
int gameCheckWin();
//Array to hold the current game board
double gameBoard[5][5];
//boolean to check if the generating game board is still unique
int gameBoardUnique = 0;
//incrementing and counting variables
int r, c, i, sumR, sumC, drawCounter, gameCounter, gameDraw;
//Time variable to seed random
time_t t;
//character input. targeted return values listed
char charInput; //10 = Enter, 113 = q, 81 = Q
//array used for printing appropriate prefix for drawn number
char covidStr[] = {'C', 'O', 'V', 'I', 'D'};

int main(int arg, char **argv){
  gameCounter = 0;
  charInput = 10;
  //while the input from the user is 'enter' This will be 10 if the user selects
  //to play again
  while(charInput == 10){
    //seed random for each game
    srand((unsigned) time(&t));
    drawCounter = 0;
    //randomize board anf print
    gameFillBoard();
    dispPrintBoard();
    charInput = 0;
    //Input filtering so input is only 'Enter', 'q', or 'Q'
    while(charInput != 10 && charInput != 81 && charInput != 113){
      printf("Press \'Enter\' to generate a Square (or \'q\' to [Quit]) ");
      scanf("%c",&charInput);
    }
    //check win to continue and user must have pressed enter to continue
    while(!gameCheckWin() && charInput == 10){
      //Draw a random number from 1-99 and check the draw
      gameDraw = (rand() % 98) + 1;
      gameCheckDraw(gameDraw);
      drawCounter++;
      //the letter prefix is calculated with 'covidStr[(int) (gameDraw/20)]'
      //so thet no conditional loops are needed. Casting as int will trunc
      //the remainder to always get the correct letter prefix
      printf("%i: %c-%i\n", drawCounter, covidStr[(int) (gameDraw/20)], gameDraw);
      dispPrintBoard();
      //Ask to continue if the game hasn't been won yet
      if(!gameCheckWin()){
        charInput = 0;
        while(charInput != 10 && charInput != 81 && charInput != 113){
          printf("Press \'Enter\' to generate a Square (or \'q\' to [Quit]) ");
          scanf("%c",&charInput);
        }
      }
    }
    //If the game wasn't quit then display the win message and inrement the
    //game played counter
    if(charInput == 10){
      printf("You Win! Number of Draws: %i\n", drawCounter);
      gameCounter++;
      charInput = 0;
      while(charInput != 10 && charInput != 81 && charInput != 113){
        printf("Press \'Enter\' to play again (or \'q\' to [Quit]) ");
        scanf("%c",&charInput);
      }
    }
  }
  printf("Games played: %i\n", gameCounter);
  return 1;
}

int gameFillBoard(){
  for(r = 0; r < 5; r++){
    for(c = 0; c < 5; c++){
      //Loops through the game board and generates the appripiate number form
      //the number range
      gameBoard[r][c] = (double) ((rand() % 19) + (c * 20) + 1);
      gameBoardUnique = r == 0;
      //Checks to make sure the board is unique.
      while(!gameBoardUnique){
        for(i = (r - 1); i >= 0; i--){
          //If the board isn't unique it will regenerate and check until it is
          if(gameBoard[r][c] == gameBoard[i][c]){
            i = r;
            gameBoard[r][c] = (double) ((rand() % 19) + (c * 20) + 1);
          }
        }
        gameBoardUnique = 1;
      }
    }
  }
  //set to a unique number so the dispPrintNum will print 'Free'
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
