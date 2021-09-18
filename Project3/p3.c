

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
char generateParity(char inputData[8]);

/*
Enter hex: 0x41424344
Number[0] = D
B[0] << 0: 0
B[0] << 1: 0
B[0] << 2: 1
B[0] << 3: 0
B[0] << 4: 0
B[0] << 5: 0
B[0] << 6: 1
B[0] << 7: 0
Number[1] = C
B[1] << 0: 1
B[1] << 1: 1
B[1] << 2: 0
B[1] << 3: 0
B[1] << 4: 0
B[1] << 5: 0
B[1] << 6: 1
B[1] << 7: 0
Number[2] = B
B[2] << 0: 0
B[2] << 1: 1
B[2] << 2: 0
B[2] << 3: 0
B[2] << 4: 0
B[2] << 5: 0
B[2] << 6: 1
B[2] << 7: 0
Number[3] = A
B[3] << 0: 1
B[3] << 1: 0
B[3] << 2: 0
B[3] << 3: 0
B[3] << 4: 0
B[3] << 5: 0
B[3] << 6: 1
B[3] << 7: 0
*/

int main(int arg, char **argv){
  /*
  union dataBytes inputNum;
  int i = 0, j = 0;
  printf("Enter hex: 0x");
  scanf("%X", &inputNum.number);

  for(i = 0; i < 4; i++){
    printf("Number[%i] = %c\n", i, (char)inputNum.bytes[i]);
    for(j = 0; j < 8; j++){
      printf("B[%i] << %i: %i\n", i, j, readBit(inputNum.bytes[i], j));
    }
  }
  */
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

char generateParity(char inputData[4]){
  char parityBits = 0;
  //int currentBit = 0;

  return parityBits;
}
