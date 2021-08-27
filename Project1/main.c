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
int dispPrintNum(double gameBoardPoint);
/**
 * This function will print the whole board. It calles dispPrintNum for each
 * number printed.
 */
int dispPrintBoard(double (*gameBoardAdr)[5]);
/**
 * This function will fill the array gameBoard with unique random numbers per
 * the set range for each column.
 */
int gameFillBoard(double (*gameBoardAdr)[5]);
/**
 * This function will check if the number drawn is a number on the board. If the
 * number drawn is on the board it will clearn the number from the array so that
 * when the board is printed the next time an x is printed
 *
 * @param draw the number to check
 */
int gameCheckDraw(double (*gameBoardAdr)[5], int draw);
/**
 * This function will check all win conditions on the board. If there is a win
 * condition the function will return 1 (True) else the function will
 * return 0 (False)
 *
 * @return int (Bool) 1 if win else 0
 */
int gameCheckWin(double (*gameBoardAdr)[5]);

int main(int arg, char **argv){
  //Array to hold the current game board
  double gameBoard[5][5];
  //counting variables
  int drawCounter, gameCounter, gameDraw;
  //Time variable to seed random
  time_t t;
  //character input. targeted return values listed
  char charInput, dummyRead; //10 = Enter, 113 = q, 81 = Q
  //array used for printing appropriate prefix for drawn number
  char covidStr[] = {'C', 'O', 'V', 'I', 'D'};

  gameCounter = 0;
  charInput = 10;
  //while the input from the user is 'enter' This will be 10 if the user selects
  //to play again
  while(charInput == 10){
    //seed random for each game
    srand((unsigned) time(&t));
    drawCounter = 0;
    //randomize board anf print
    gameFillBoard(gameBoard);
    dispPrintBoard(gameBoard);
    charInput = 0;
    //Input filtering so input is only 'Enter', 'q', or 'Q'
    while(charInput != 10 && charInput != 81 && charInput != 113){
      printf("Press \'Enter\' to generate a Square (or \'q\' to [Quit]) ");
      scanf("%c",&charInput);
      if(charInput != 10){
        scanf("%c",&dummyRead);
      }
    }
    //check win to continue and user must have pressed enter to continue
    while(!gameCheckWin(gameBoard) && charInput == 10){
      //Draw a random number from 1-99 and check the draw
      gameDraw = (rand() % 98) + 1;
      gameCheckDraw(gameBoard, gameDraw);
      drawCounter++;
      //the letter prefix is calculated with 'covidStr[(int) (gameDraw/20)]'
      //so thet no conditional loops are needed. Casting as int will trunc
      //the remainder to always get the correct letter prefix
      printf("%i: %c-%i\n", drawCounter, covidStr[(int) (gameDraw/20)], gameDraw);
      dispPrintBoard(gameBoard);
      //Ask to continue if the game hasn't been won yet
      if(!gameCheckWin(gameBoard)){
        charInput = 0;
        while(charInput != 10 && charInput != 81 && charInput != 113){
          printf("Press \'Enter\' to generate a Square (or \'q\' to [Quit]) ");
          scanf("%c",&charInput);
          if(charInput != 10){
            scanf("%c",&dummyRead);
          }
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
        if(charInput != 10){
          scanf("%c",&dummyRead);
        }
      }
    }
  }
  printf("Games played: %i\n", gameCounter);
  return 1;
}

int gameFillBoard(double (*gameBoardAdr)[5]){
  //boolean to check if the generating game board is still unique
  int gameBoardUnique = 0;
  //incrementing variables
  int r, c, i;
  for(r = 0; r < 5; r++){
    for(c = 0; c < 5; c++){
      //Loops through the game board and generates the appripiate number form
      //the number range
      gameBoardAdr[r][c] = (double) ((rand() % 19) + (c * 20) + 1);
      gameBoardUnique = r == 0;
      //Checks to make sure the board is unique.
      while(!gameBoardUnique){
        for(i = (r - 1); i >= 0; i--){
          //If the board isn't unique it will regenerate and check until it is
          if(gameBoardAdr[r][c] == gameBoardAdr[i][c]){
            i = r;
            gameBoardAdr[r][c] = (double) ((rand() % 19) + (c * 20) + 1);
          }
        }
        gameBoardUnique = 1;
      }
    }
  }
  //set to a unique number so the dispPrintNum will print 'Free'
  gameBoardAdr[2][2] = -1.1;
  return 1;
}

int dispPrintNum(double gameBoardPoint){
  //Check if the number has been drawn or is the free space
  if(gameBoardPoint < 0){
    if(gameBoardPoint == -1.1){
      printf(" Free ");
    } else {
      printf("  x   ");
    }
  } else {
    //Print the number and add an extra space if 1-9
    printf("  %i  ", (int) gameBoardPoint);
    if(gameBoardPoint < 10){
      printf(" ");
    }
  }
  return 1;
}

int dispPrintBoard(double (*gameBoardAdr)[5]){
  int r, c;
  printf("   C      O      V      I      D\n");
  printf("------------------------------------\n");
  printf("|");
  for(r = 0; r < 5; r++){
    //Print number line
    for(c = 0; c < 5; c++){
      dispPrintNum(gameBoardAdr[r][c]);
      printf("|");
    }
    //Print spacer line
    if(r != 4){
      printf("\n|------|------|------|------|------|\n|");
    }
  }
  printf("\n------------------------------------\n");
  return 1;
}

int gameCheckDraw(double (*gameBoardAdr)[5], int draw){
  int r, c;
  //check entire array for drawn number and replace with -1 if in array
  for(r = 0; r < 5; r++){
    for(c = 0; c < 5; c++){
      if(gameBoardAdr[r][c] == draw){
        gameBoardAdr[r][c] = -1;
      }
    }
  }
  return 1;
}

int gameCheckWin(double (*gameBoardAdr)[5]){
  //incrementing and counting variables
  int r, c, sumR, sumC, output = 0;
  //Check row and columns for all -1 or -1.1 for free space
  for(r = 0; r < 5; r++){
    sumR = 0;
    sumC = 0;
    for(c = 0; c < 5; c++){
      sumR = sumR + ((int) gameBoardAdr[r][c]);
      sumC = sumC + ((int) gameBoardAdr[c][r]);
      if(sumR <= -5 || sumC <= -5){
        output = 1;
      }
    }
  }
  //diagonals include free space so summing rest gives -4 if win
  sumR = gameBoardAdr[0][0] + gameBoardAdr[1][1] + gameBoardAdr[3][3] +
  gameBoardAdr[4][4];
  sumC = gameBoardAdr[0][4] + gameBoardAdr[1][3] + gameBoardAdr[3][1] +
  gameBoardAdr[4][0];
  if(sumR == -4 || sumC == -4){
    output = 1;
  }
  return output;
}
