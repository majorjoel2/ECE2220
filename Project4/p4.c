
//Libraries used in this program
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>


char encode[10][26] = {
  "ZWAXJGDLUBVIQHKYPNTCRMOSFE",
  "KPBELNACZDTRXMJQOYHGVSFUWI",
  "BDMAIZVRNSJUWFHTEQGYXPLOCK",
  "RPLNDVHGFCUKTEBSXQYIZMJWAO",
  "IHFRLABEUOTSGJVDKCPMNZQWXY",
  "AMKGHIWPNYCJBFZDRUSLOQXVET",
  "GWTHSPYBXIZULVKMRAFDCEONJQ",
  "NOZUTWDCVRJLXKISEFAPMYGHBQ",
  "XPLTDSRFHENYVUBMCQWAOIKZGJ",
  "UDNAJFBOWTGVRSCZQKELMXYIHP"
};

void encodeLetter(char *message, int keyNum, int offset, int currentIndex);
void decodeLetter(char *message, int keyNum, int offset, int currentIndex);

int main(int arg, char **argv){
  int keyOrder[10] = {0,1,2,3,4,5,6,7,8,9};
  return 1;
}

void encodeLetter(char *message, int keyNum, int offset, int currentIndex){
  int letterLocation = 26, i = 0;
  for(i = 0; i < 26; i++){
    if(encode[keyNum][i] == toupper(message[currentIndex])){
      letterLocation += i;
    }
  }
  message[currentIndex] = encode[keyNum][(letterLocation+offset)%26];
}

void decodeLetter(char *message, int keyNum, int offset, int currentIndex){
  int letterLocation = 26, i = 0;
  for(i = 0; i < 26; i++){
    if(encode[keyNum][i] == toupper(message[currentIndex])){
      letterLocation += i;
    }
  }
  message[currentIndex] = encode[keyNum][(letterLocation-offset)%26];
}
