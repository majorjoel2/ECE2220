

//Libraries used in this program
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

union dataBytes {
  int number;
  char bytes[4];
};

char readBit(char byte, char bitPosition);
void setBit(char *byte, char bitPosition);
void clearBit(char *byte, char bitPosition);
char generateParity(union dataBytes inputData);
void encodeBits(union dataBytes *inputData, char parity);
char decodeBits(union dataBytes *inputData);

int main(int arg, char **argv){
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

/*
P0 = D0 + D1 + D3 + D4 + D6 + D8 + D10 + D11 + D13 + D15
P1 = D0 + D2 + D3 + D5 + D6 + D9 + D10 + D12 + D13
P2 = D1 + D2 + D3 + D7 + D8 + D9 + D10 + D14 + D15
P3 = D4 + D5 + D6 + D7 + D8 + D9 + D10
P4 = D11 + D12 + D13 + D14 + D15
*/

char generateParity(union dataBytes inputData){
  int parity[5][10] = {
    {0, 1, 3, 4, 6, 8, 10, 11, 13, 15},
    {0, 2, 3, 5, 6, 9, 10, 12, 13, 0},
    {1, 2, 3, 7, 8, 9, 10, 14, 15, 0},
    {4, 5, 6, 7, 8, 9, 10, 0, 0, 0},
    {11, 12, 13, 14, 15, 0, 0, 0, 0, 0}
  };
  int paritySize[5] = {10, 9, 9, 7, 5};
  char parityBits = 0;
  int currentBit = 0, i = 0, j = 0;
  for(j = 0; j < 5; j++){
    currentBit = 0;
    for(i = 0; i < paritySize[j]; i++){
      currentBit += readBit(inputData.bytes[parity[j][i]/8], (parity[j][i])%8);
    }
    (currentBit%2 == 1) ? setBit(&parityBits, j) : clearBit(&parityBits, j);
  }
  return parityBits;
}

void encodeBits(union dataBytes *inputData, char parity){
  int newDataPosition[16] = {2, 4, 5, 6, 8, 9, 10, 11, 12, 13, 14, 16, 17, 18, 19, 20};
  int newParityPosition[5] = {0, 1, 3, 7, 15};
  int i;
  for(i = 15; i >= 0; i--){
    if(readBit(inputData->bytes[i/8], i%8) == 1){
      setBit(&inputData->bytes[newDataPosition[i]/8], newDataPosition[i]%8);
    } else {
      clearBit(&inputData->bytes[newDataPosition[i]/8], newDataPosition[i]%8);
    }
  }
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
  int oldDataPosition[16] = {2, 4, 5, 6, 8, 9, 10, 11, 12, 13, 14, 16, 17, 18, 19, 20};
  int parityPosition[5] = {0, 1, 3, 7, 15};
  int i;
  for(i = 4; i >= 0; i--){
    if(readBit(inputData->bytes[parityPosition[i]/8], parityPosition[i]%8) == 1){
      setBit(&parity, i);
    } else {
      clearBit(&parity, i);
    }
  }
  for(i = 0; i < 16; i++){
    if(readBit(inputData->bytes[oldDataPosition[i]/8], oldDataPosition[i]%8) == 1){
      setBit(&inputData->bytes[i/8], i%8);
    } else {
      clearBit(&inputData->bytes[i/8], i%8);
    }
  }
  for(i = 16; i < 32; i++){
    clearBit(&inputData->bytes[i/8], i%8);
  }
  return parity;
}
