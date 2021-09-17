

//Libraries used in this program
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>


byte readBit(char byte, char bitPosition);
void setBit(char *byte, char bitPosition);
void clearBit(char *byte, char bitPosition);


int main(int arg, char **argv){
  return 1;
}


byte readBit(char byte, char bitPosition){
  bitPosition == 1 << bitPosition;
  return (byte & bitPosition);
}
void setBit(char *byte, char bitPosition){
  bitPosition == 1 << bitPosition;
  *byte = (*byte | bitPosition);
}
void clearBit(char *byte, char bitPosition){
  bitPosition == 1 << bitPosition;
  bitPosition ^= 0xff;
  *byte = (*byte & bitPosition);
}
