
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

int main(int argc, char *argv[]){
  int i = 0, j = 0, offsetVal;
  for(i = 0; i < argc; i++){
    printf("arg[%i] = %s\tLen:%li\n", i, argv[i], strlen(argv[i]));
  }
  int keyOrder[10] = {0,1,2,3,4,5,6,7,8,9};
  char messageInput[31];
  for(i = 0, j = 0; i < strlen(argv[2]); i++){
    if(argv[2][i] >= 48 && argv[2][i] <= 57){
      //number
      if(argv[2][i] == 48){
        //10
        keyOrder[j] = 9;
      } else {
        keyOrder[j] = argv[2][i] - '0' - 1;
      }
    } else {
      j++;
    }
  }
  sscanf(argv[3], "%i", &offsetVal);
  offsetVal = offsetVal % 26;
  strcpy(messageInput, argv[4]);
  if(toupper(argv[1][0]) == 'E'){
    //encode
    for(i = 0, j = 0; i < strlen(messageInput); i++){
      if(messageInput[i] > 64){
        //letter
        encodeLetter(messageInput, keyOrder[j%10], offsetVal, i);
        j++;
      }
    }
    printf("Encoded Message: %s\n", messageInput);
  }
  if(toupper(argv[1][0]) == 'D'){
    //decode
    for(i = 0, j = 0; i < strlen(messageInput); i++){
      if(messageInput[i] > 64){
        //letter
        decodeLetter(messageInput, keyOrder[j%10], offsetVal, i);
        j++;
      }
    }
    printf("Decoded Message: %s\n", messageInput);
  }
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
