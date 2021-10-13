
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
  int validInput = 0, operation = 0;
  int keyOrder[10] = {0,1,2,3,4,5,6,7,8,9};
  char messageInput[31];
  if(argc != 5){
    printf("Wrong number of inputs!\n");
    return 0;
  }
  sscanf(argv[2], "%i,%i,%i,%i,%i,%i,%i,%i,%i,%i",
         &keyOrder[0], &keyOrder[1], &keyOrder[2], &keyOrder[3], &keyOrder[4],
         &keyOrder[5], &keyOrder[6], &keyOrder[7], &keyOrder[8], &keyOrder[9]);
  for(i = 0; i < 10; i++){
    for(j = i+1; j < 10; j++){
      if(keyOrder[i] == keyOrder[j] && i != j){
        validInput++;
      }
    }
  }
  sscanf(argv[3], "%i", &offsetVal);
  if(offsetVal < 0){
    validInput += 100;
  }
  offsetVal = offsetVal % 26;
  strcpy(messageInput, argv[4]);
  for(i = 0; i < strlen(argv[1]); i++){
    argv[1][i] = toupper(argv[1][i]);
  }
  if(strcmp(argv[1], "ENCODE") == 0 && validInput == 0){
    //encode
    operation = 1;
    for(i = 0, j = 0; i < strlen(messageInput); i++){
      if(isalpha(messageInput[i]) != 0){
        //letter
        encodeLetter(messageInput, keyOrder[j%10], offsetVal, i);
        j++;
      }
    }
    printf("Encoded Message: %s\n", messageInput);
  }
  if(strcmp(argv[1], "DECODE") == 0 && validInput == 0){
    //decode
    operation = 1;
    for(i = 0, j = 0; i < strlen(messageInput); i++){
      if(isalpha(messageInput[i]) != 0){
        //letter
        decodeLetter(messageInput, keyOrder[j%10], offsetVal, i);
        j++;
      }
    }
    printf("Decoded Message: %s\n", messageInput);
  }
  if(validInput != 0 || operation == 0){
    printf("Invalid Input! Error Code: %i\n", validInput);
    return 0;
  }
  return 1;
}

void encodeLetter(char *message, int keyNum, int offset, int currentIndex){
  keyNum--;
  int letterLocation = 26, i = 0;
  for(i = 0; i < 26; i++){
    if(encode[keyNum][i] == toupper(message[currentIndex])){
      letterLocation += i;
    }
  }
  message[currentIndex] = encode[keyNum][(letterLocation+offset)%26];
}

void decodeLetter(char *message, int keyNum, int offset, int currentIndex){
  keyNum--;
  int letterLocation = 26, i = 0;
  for(i = 0; i < 26; i++){
    if(encode[keyNum][i] == toupper(message[currentIndex])){
      letterLocation += i;
    }
  }
  message[currentIndex] = encode[keyNum][(letterLocation-offset)%26];
}
