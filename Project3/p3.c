/**
 * Joel Tanner
 * 09-22-2021
 *
 * The goal of this project is to encode two printable characters to a
 * (21, 16)Hamming Code and to show the error free decoding of a
 * (21, 16)Hamming Code.
 */


//Libraries used in this program
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

/*
 * Union to allow cess to individual bytes of the int.
 * Makes it easier to get and set bits because you can use bytes
 */
union dataBytes {
  int number;
  char bytes[4];
};

/**
 * This function will read the bit ate bitPosition or the input byte and return
 * a zero or one depending if the bit is one or zero
 *
 * @param byte A char to read from
 * @param bitPosition The position of the bit in the char
 *
 * @return char bit at bitPosition of byte. Value: Zero or One
 */
char readBit(char byte, char bitPosition);
/**
 * This function will set a single bit in the byte using pass by refrence
 *
 * @param *byte Pass by refrence of a byte
 * @param bitPosition position of bit to be set
 */
void setBit(char *byte, char bitPosition);
/**
 * This function will clear a single bit in the byte using pass by refrence
 *
 * @param *byte Pass by refrence of a byte
 * @param bitPosition position of bit to be cleared
 */
void clearBit(char *byte, char bitPosition);
/**
 * This function will generate the parity of the input data using the formula:
 * Pk is parity bit k; Dk is data bit k; Zero is right most bit
 * P0 = D0 + D1 + D3 + D4 + D6 + D8 + D10 + D11 + D13 + D15
 * P1 = D0 + D2 + D3 + D5 + D6 + D9 + D10 + D12 + D13
 * P2 = D1 + D2 + D3 + D7 + D8 + D9 + D10 + D14 + D15
 * P3 = D4 + D5 + D6 + D7 + D8 + D9 + D10
 * P4 = D11 + D12 + D13 + D14 + D15
 *
 * @param inputData the user data to be used to generate parity bits
 *
 * @return char parity bits stored in one byte with zeros in the three remaining bits
 */
char generateParity(union dataBytes inputData);
/**
 * This function will reorder the data bits and add in the parity bits. The
 * data is passed in with pass by refrence as the union to simplufy the input
 *
 * @param *inputData The user data to be encoded
 * @param parity the 5 parity bits
 */
void encodeBits(union dataBytes *inputData, char parity);
/**
 * This function will pull the parity bits out and move the data bits back to
 * their origional positions. The data is passed in with pass by refrence
 * to simplify the input.
 *
 * @param *inputData the Hamming Code to be decoded
 *
 * @return char the five parity bits
 */
char decodeBits(union dataBytes *inputData);

int main(int arg, char **argv){
  //loop values
  char exitLoop = 0, activeRead = 0, dummyRead = 0, pBits = 0;
  //Strings to store data and hex values
  char inputValue[16];
  char inputCopy[16];
  char hexValue[7];
  char newHexValue[5];
  int i = 0;
  //user data
  union dataBytes userInput;

  //Keep looping until the user inputs the exit command
  while(!exitLoop){
    //print max
    printf("To Encode two characters [cc] type \"Encode cc\"\n");
    printf("To Decode hex number [0xNNNNNN] type \"Decode 0xNNNNNN\"\n");
    printf("To Quit type \"Quit\"\n");
    //read command 15 char max
    i = 0;
    scanf("%c", &activeRead);
    //read input
    while(activeRead != 10 && i < 16){
      inputValue[i] = activeRead;
      scanf("%c", &activeRead);
      i++;
    }
    //clear excess input
    if(i == 16){
      dummyRead = 0;
      while(dummyRead != 10){
        scanf("%c", &dummyRead);
      }
    }
    inputValue[i] = 0;
    //copy to manipulat3
    strcpy(inputCopy, inputValue);
    //Add a null to shorten to compare
    inputCopy[6] = 0;
    if(strcmp(inputCopy, "Encode") == 0){
      //Encoding
      //Print input
      printf("Code Letters Entered: %c%c\n", inputValue[7], inputValue[8]);
      userInput.bytes[0] = inputValue[7];
      userInput.bytes[1] = inputValue[8];
      userInput.bytes[2] = 0;
      userInput.bytes[3] = 0;
      printf("Code Value (Hex): 0x%X\n", userInput.number);
      printf("Code Value (Binary): ");
      for(i = 15; i >=0; i--){
        printf("%i", readBit(userInput.bytes[i/8], i%8));
      }
      printf("\n");
      //Generate parity and print
      pBits = generateParity(userInput);
      printf("Parity Bits: ");
      for(i = 4; i >=0; i--){
        printf("%i", readBit(pBits, i));
      }
      printf("\n");
      //Encode and print
      encodeBits(&userInput, pBits);
      printf("Encoded Value (Hex): 0x%X\n", userInput.number);
      printf("Encoded Value (Binary): ");
      for(i = 20; i >=0; i--){
        printf("%i", readBit(userInput.bytes[i/8], i%8));
      }
      printf("\n");
    } else if(strcmp(inputCopy, "Decode") == 0){
      //Decoding
      //Pull hex value from input
      for(i = 0; i < 8; i++){
        hexValue[i] = inputValue[i+9];
      }
      //convert to integer and print
      sscanf(hexValue, "%X", &userInput.number);
      for(i = 0; i < 6; i++){
        printf("   %c ", hexValue[i]);
      }
      printf("\n");
      //print bits
      printf("---%i ", readBit(userInput.bytes[2], 4));
      for(i = 19; i >= 0; i--){
        printf("%i", readBit(userInput.bytes[i/8], i%8));
        if(i%4 == 0) {
          printf(" ");
        }
      }
      printf("\n");
      printf("   ^ ^^^^  ^^^ ^^^^  ^^^  ^\n");
      //Decode and print nibbles
      pBits = decodeBits(&userInput);
      printf("     ");
      for(i = 15; i >= 0; i--){
        printf("%i", readBit(userInput.bytes[i/8], i%8));
        if(i%4 == 0) {
          printf(" ");
        }
      }
      printf("\n");
      //convert decoded hex to string
      sprintf(newHexValue, "%X",userInput.number);
      //print as hex and char
      printf("     ");
      for(i = 0; i < 4; i++){
        printf("  %c  ", newHexValue[i]);
      }
      printf("\n");
      printf("=        \'%c\'       \'%c\'\n", userInput.bytes[1], userInput.bytes[0]);
    } else if(strcmp(inputCopy, "Quit") == 0){
      //Exit
      exitLoop = 1;
    } else {
      printf("Invalid Input\n");
    }
  }
  return 1;
}


char readBit(char byte, char bitPosition){
  bitPosition = 1 << bitPosition;
  return (byte & bitPosition) == 0 ? 0 : 1;
}

void setBit(char *byte, char bitPosition){
  bitPosition = 1 << bitPosition;
  *byte = (*byte | bitPosition);
}

void clearBit(char *byte, char bitPosition){
  bitPosition = 1 << bitPosition;
  bitPosition ^= 0xff;
  *byte = (*byte & bitPosition);
}

char generateParity(union dataBytes inputData){
  //Position of bits to calc parity
  int parity[5][10] = {
    {0, 1, 3, 4, 6, 8, 10, 11, 13, 15},
    {0, 2, 3, 5, 6, 9, 10, 12, 13, 0},
    {1, 2, 3, 7, 8, 9, 10, 14, 15, 0},
    {4, 5, 6, 7, 8, 9, 10, 0, 0, 0},
    {11, 12, 13, 14, 15, 0, 0, 0, 0, 0}
  };
  //number of data bits to consider
  int paritySize[5] = {10, 9, 9, 7, 5};
  char parityBits = 0;
  int currentBit = 0, i = 0, j = 0;
  //loop the parity array limiting to paritySize
  for(j = 0; j < 5; j++){
    currentBit = 0;
    for(i = 0; i < paritySize[j]; i++){
      //add the value of the bit
      currentBit += readBit(inputData.bytes[parity[j][i]/8], (parity[j][i])%8);
    }
    //mod sum and and set or clear depending on output of mod
    (currentBit%2 == 1) ? setBit(&parityBits, j) : clearBit(&parityBits, j);
  }
  return parityBits;
}

void encodeBits(union dataBytes *inputData, char parity){
  //data and parity positions
  int newDataPosition[16] = {2, 4, 5, 6, 8, 9, 10, 11, 12, 13, 14, 16, 17, 18, 19, 20};
  int newParityPosition[5] = {0, 1, 3, 7, 15};
  int i;
  //move data to new position
  for(i = 15; i >= 0; i--){
    if(readBit(inputData->bytes[i/8], i%8) == 1){
      setBit(&inputData->bytes[newDataPosition[i]/8], newDataPosition[i]%8);
    } else {
      clearBit(&inputData->bytes[newDataPosition[i]/8], newDataPosition[i]%8);
    }
  }
  //add in parity bits to data
  for(i = 4; i >= 0; i--){
    if(readBit(parity, i) == 1){
      setBit(&inputData->bytes[newParityPosition[i]/8], newParityPosition[i]%8);
    } else {
      clearBit(&inputData->bytes[newParityPosition[i]/8], newParityPosition[i]%8);
    }
  }
}

char decodeBits(union dataBytes *inputData){
  char parity = 0;
  //refrence positions
  int oldDataPosition[16] = {2, 4, 5, 6, 8, 9, 10, 11, 12, 13, 14, 16, 17, 18, 19, 20};
  int parityPosition[5] = {0, 1, 3, 7, 15};
  int i;
  //strip out parity
  for(i = 4; i >= 0; i--){
    if(readBit(inputData->bytes[parityPosition[i]/8], parityPosition[i]%8) == 1){
      setBit(&parity, i);
    } else {
      clearBit(&parity, i);
    }
  }
  //move data to old positions
  for(i = 0; i < 16; i++){
    if(readBit(inputData->bytes[oldDataPosition[i]/8], oldDataPosition[i]%8) == 1){
      setBit(&inputData->bytes[i/8], i%8);
    } else {
      clearBit(&inputData->bytes[i/8], i%8);
    }
  }
  //clear upper bits
  for(i = 16; i < 32; i++){
    clearBit(&inputData->bytes[i/8], i%8);
  }
  return parity;
}
