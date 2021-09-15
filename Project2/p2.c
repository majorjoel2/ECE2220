

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

struct idiot {
  char prefix[6];
  char firstName[34];
  char middleInitial[4];
  char lastName[34];
  char suffix[6];
  int age;
  char sex;
  char officeHeld[33];
  int yearsServed;
  char politicalParty[4];
  char homeState[3];
  char twitter[16];
  char phoneNumber[14];
  double donationsReceived;
  long double totalWealth;
};

struct idiot setToDefaultPolitician();

char statesName[50][15] = {
  "Alabama", "Alaska", "Arizona", "Arkansas", "California",
  "Colorado", "Connecticut", "Delaware", "Florida", "Georgia",
  "Hawaii", "Idaho", "Illinois", "Indiana", "Iowa",
  "Kansas", "Kentucky", "Louisiana", "Maine", "Maryland",
  "Massachusetts", "Michigan", "Minnesota", "Mississippi", "Missouri",
  "Montana", "Nebraska", "Nevada", "New Hampshire", "New Jersey",
  "New Mexico", "New York", "North Carolina", "North Dakota", "Ohio",
  "Oklahoma", "Oregon", "Pennsylvania", "Rhode Island", "South Carolina",
  "South Dakota", "Tennessee", "Texas", "Utah", "Vermont",
  "Virginia", "Washington", "West Virginia", "Wisconsin", "Wyoming"
};

char stateAbbreviations[50][3] = {
  "AL", "AK", "AZ", "AR", "CA", "CO", "CT", "DE", "FL", "GA",
  "HI", "ID", "IL", "IN", "IA", "KS", "KY", "LA", "ME", "MD",
  "MA", "MI", "MN", "MS", "MO", "MT", "NE", "NV", "NH", "NJ",
  "NM", "NY", "NC", "ND", "OH", "OK", "OR", "PA", "RI", "SC",
  "SD", "TN", "TX", "UT", "VT", "VA", "WA", "WV", "WI", "WY"
};

int main(int arg, char **argv){
  char loopInput = 10, dummyClear, currentLetter;
  char validInput;
  struct idiot currentPolitician = setToDefaultPolitician();
  int i;

  while(loopInput != 113){
    printf("Enter the [c]haracter input for the corresponding choice.\n");
    printf("[N]ame\n[Y]ears, Party, Office, and State\n[A]ge and Sex\n");
    printf("C[o]tacts\nContributions and [W]ealth\n[D]isplay all Data\n");
    printf("[C]lear all Data\n[Q]uit\n");
    validInput = 0;
    while(!validInput){
      scanf("%c", &loopInput);
      if(loopInput != 10){
        loopInput = tolower(loopInput);
        if(loopInput == 110 || loopInput == 121 || loopInput == 97 ||
           loopInput == 111 || loopInput == 119 || loopInput == 100 ||
           loopInput == 99 || loopInput == 113){
          //
          validInput = 1;
        } else {
          printf("Invalid Selection\n");
        }
        dummyClear = 0;
        while(dummyClear != 10){
          scanf("%c", &dummyClear);
        }
      }
    }
    if(loopInput == 110){
      //Name Input
      //Prefix 3 char
      printf("Enter politician prefix ([Enter] to skip): ");
      scanf("%c", &currentLetter);
      if(currentLetter != 10){
        currentPolitician.prefix[0] = currentLetter;
        i = 1;
        validInput = 0;
        while(!validInput){
          scanf("%c", &currentLetter);
          if(currentLetter == 10 || currentLetter == 32 || i == 3){
            validInput = 1;
            currentPolitician.prefix[i] = '.';
            currentPolitician.prefix[i+1] = ' ';
            currentPolitician.prefix[i+2] = 0;
            if(currentLetter == 32 || i == 3){
              dummyClear = 0;
              while(dummyClear != 10){
                scanf("%c", &dummyClear);
              }
            }
          } else {
            currentPolitician.prefix[i] = currentLetter;
          }
        }
      } else {
        //null terminate at first index if no prefix entered
        currentPolitician.prefix[0] = 0;
      }
      //first name 32 char
      printf("Enter politician first name: ");
      scanf("%c", &currentLetter);
      if(currentLetter != 10){
        currentPolitician.firstName[0] = currentLetter;
        i = 1;
        validInput = 0;
        while(!validInput){
          scanf("%c", &currentLetter);
          if(currentLetter == 10 || currentLetter == 32 || i == 32){
            validInput = 1;
            currentPolitician.firstName[i] = ' ';
            currentPolitician.firstName[i+1] = 0;
            if(currentLetter == 32 || i == 32){
              dummyClear = 0;
              while(dummyClear != 10){
                scanf("%c", &dummyClear);
              }
            }
          } else {
            currentPolitician.firstName[i] = currentLetter;
          }
        }
      } else {
        //set first name to - to indicate none given
        currentPolitician.firstName[0] = '-';
      }
      //Middle Initial 1 char
      printf("Enter politician middle initial ([Enter] to skip): ");
      scanf("%c", &currentLetter);
      if(currentLetter != 10){
        currentPolitician.middleInitial[0] = currentLetter;
        i = 1;
        validInput = 0;
        while(!validInput){
          scanf("%c", &currentLetter);
          if(currentLetter == 10 || currentLetter == 32 || i == 1){
            validInput = 1;
            currentPolitician.middleInitial[i] = '.';
            currentPolitician.middleInitial[i+1] = ' ';
            currentPolitician.middleInitial[i+2] = 0;
            if(currentLetter == 32 || i == 1){
              dummyClear = 0;
              while(dummyClear != 10){
                scanf("%c", &dummyClear);
              }
            }
          } else {
            currentPolitician.middleInitial[i] = currentLetter;
          }
        }
      } else {
        //null terminate at first index if no prefix entered
        currentPolitician.middleInitial[0] = 0;
      }
      //ladt name 32 char
      printf("Enter politician last name: ");
      scanf("%c", &currentLetter);
      if(currentLetter != 10){
        currentPolitician.lastName[0] = currentLetter;
        i = 1;
        validInput = 0;
        while(!validInput){
          scanf("%c", &currentLetter);
          if(currentLetter == 10 || currentLetter == 32 || i == 32){
            validInput = 1;
            currentPolitician.lastName[i] = ' ';
            currentPolitician.lastName[i+1] = 0;
            if(currentLetter == 32 || i == 32){
              dummyClear = 0;
              while(dummyClear != 10){
                scanf("%c", &dummyClear);
              }
            }
          } else {
            currentPolitician.lastName[i] = currentLetter;
          }
        }
      } else {
        //set last name to - to indicate none given
        currentPolitician.lastName[0] = '-';
      }
      //Suffix 3 char
      printf("Enter politician suffix ([Enter] to skip): ");
      scanf("%c", &currentLetter);
      if(currentLetter != 10){
        currentPolitician.suffix[0] = currentLetter;
        i = 1;
        validInput = 0;
        while(!validInput){
          scanf("%c", &currentLetter);
          if(currentLetter == 10 || currentLetter == 32 || i == 3){
            validInput = 1;
            currentPolitician.suffix[i] = '.';
            currentPolitician.suffix[i+1] = ' ';
            currentPolitician.suffix[i+2] = 0;
            if(currentLetter == 32 || i == 3){
              dummyClear = 0;
              while(dummyClear != 10){
                scanf("%c", &dummyClear);
              }
            }
          } else {
            currentPolitician.suffix[i] = currentLetter;
          }
        }
      } else {
        //null terminate at first index if no suffix entered
        currentPolitician.suffix[0] = 0;
      }
    }
    if(loopInput = 100){
      //display all info
      if(currentPolitician.firstName[0] == '-' || currentPolitician.lastName == '-'){
        printf("Name not given.\n");
      } else {
        printf("Name: %s%s%s%s%s\n", currentPolitician.prefix,
                currentPolitician.firstName, currentPolitician.middleInitial,
                currentPolitician.lastName, currentPolitician.suffix);
      }
    }
  }
  return 1;
}

struct idiot setToDefaultPolitician(){
  struct idiot default_politician;
  default_politician.prefix[0] = '-';
  default_politician.firstName[0] = '-';
  default_politician.middleInitial[0] = '-';
  default_politician.lastName[0] = '-';
  default_politician.suffix[0] = '-';
  default_politician.age = -1;
  default_politician.sex = '-';
  default_politician.officeHeld[0] = '-';
  default_politician.yearsServed = -1;
  default_politician.politicalParty[0] = '-';
  default_politician.homeState[0] = '-';
  default_politician.twitter[0] = '-';
  default_politician.phoneNumber[0] = '-';
  default_politician.donationsReceived = -0.1;
  default_politician.totalWealth = -0.1;
  return default_politician;
}
