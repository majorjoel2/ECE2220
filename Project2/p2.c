

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

struct idiot {
  char prefix[6];
  char firstName[34];
  char middleInitial[4];
  char lastName[34];
  char suffix[5];
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

char partyName[5][13] = {
  "Constitution",
  "Democratic",
  "Green",
  "Libertarian",
  "Republican"
};

char partyAbbreviation[5][4] = {
  "CON", "DEM", "GRE", "LIB", "REP"
};

int main(int arg, char **argv){
  char loopInput = 10, dummyClear, currentLetter;
  char validInput, validInput2;
  struct idiot currentPolitician = setToDefaultPolitician();
  int i, currentNumber;

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
            if((currentLetter == 32 || i == 3) && currentLetter != 10){
              dummyClear = 0;
              while(dummyClear != 10){
                scanf("%c", &dummyClear);
              }
            }
          } else {
            currentPolitician.prefix[i] = currentLetter;
          }
          i++;
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
            if((currentLetter == 32 || i == 32) && currentLetter != 10){
              dummyClear = 0;
              while(dummyClear != 10){
                scanf("%c", &dummyClear);
              }
            }
          } else {
            currentPolitician.firstName[i] = currentLetter;
          }
          i++;
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
        currentPolitician.middleInitial[1] = '.';
        currentPolitician.middleInitial[2] = ' ';
        currentPolitician.middleInitial[3] = 0;
        dummyClear = 0;
        while(dummyClear != 10){
          scanf("%c", &dummyClear);
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
            if((currentLetter == 32 || i == 32) && currentLetter != 10){
              dummyClear = 0;
              while(dummyClear != 10){
                scanf("%c", &dummyClear);
              }
            }
          } else {
            currentPolitician.lastName[i] = currentLetter;
          }
          i++;
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
            currentPolitician.suffix[i] = ' ';
            currentPolitician.suffix[i+1] = 0;
            if((currentLetter == 32 || i == 3) && currentLetter != 10){
              dummyClear = 0;
              while(dummyClear != 10){
                scanf("%c", &dummyClear);
              }
            }
          } else {
            currentPolitician.suffix[i] = currentLetter;
          }
          i++;
        }
      } else {
        //null terminate at first index if no suffix entered
        currentPolitician.suffix[0] = 0;
      }
    }
    if(loopInput == 121){
      //Years, party, office, state
      //years
      currentNumber = -1;
      while(currentNumber < 0 || currentNumber > 99){
        printf("Enter years served (0-99): ");
        scanf("%d", &currentNumber);
        if(currentNumber < 0 || currentNumber > 99){
          printf("Years served out of range!\n");
        }
        dummyClear = 0;
        while(dummyClear != 10){
          scanf("%c", &dummyClear);
        }
      }
      currentPolitician.yearsServed = currentNumber;
      //party 3 char
      validInput2 = 0;
      while(!validInput2){
        printf("Party List:\n%s%15s\n%s%15s\n%s%15s\n%s%15s\n%s%15s\n",
                partyAbbreviation[0], partyName[0],
                partyAbbreviation[1], partyName[1],
                partyAbbreviation[2], partyName[2],
                partyAbbreviation[3], partyName[3],
                partyAbbreviation[4], partyName[4]);
        printf("Enter politician party affiliation (Options listed above): ");
        scanf("%c", &currentLetter);
        if(currentLetter != 10){
          currentPolitician.politicalParty[0] = toupper(currentLetter);
          i = 1;
          validInput = 0;
          while(!validInput){
            scanf("%c", &currentLetter);
            if(currentLetter == 10 || currentLetter == 32 || i == 3){
              validInput = 1;
              currentPolitician.politicalParty[i] = 0;
              if((currentLetter == 32 || i == 3) && currentLetter != 10){
                dummyClear = 0;
                while(dummyClear != 10){
                  scanf("%c", &dummyClear);
                }
              }
            } else {
              currentPolitician.politicalParty[i] = toupper(currentLetter);
            }
            i++;
          }
        } else {
          //null terminate at first index if no party entered
          currentPolitician.politicalParty[0] = 0;
        }
        for(i = 0; i < 5; i++){
          if(strcmp(partyAbbreviation[i], currentPolitician.politicalParty) == 0){
            validInput2 = 1;
          }
        }
        if(!validInput2){
          printf("Invalid party\n");
        }
      }
      //office held
      printf("Enter office held: ");
      scanf("%c", &currentLetter);
      if(currentLetter != 10){
        currentPolitician.officeHeld[0] = currentLetter;
        i = 1;
        validInput = 0;
        while(!validInput){
          scanf("%c", &currentLetter);
          if(currentLetter == 10 || i == 32){
            validInput = 1;
            currentPolitician.officeHeld[i] = ' ';
            currentPolitician.officeHeld[i+1] = 0;
            if(i == 32 && currentLetter != 10){
              dummyClear = 0;
              while(dummyClear != 10){
                scanf("%c", &dummyClear);
              }
            }
          } else {
            currentPolitician.officeHeld[i] = currentLetter;
          }
          i++;
        }
      } else {
        //set office held to - to indicate none given
        currentPolitician.officeHeld[0] = '-';
      }
      //state
      validInput2 = 0;
      while(!validInput2){
        printf("State Abbreviation list:\n");
        for(i = 0; i < 50; i++){
          printf("%s%17s\n", stateAbbreviations[i], statesName[i]);
        }
        printf("Enter politician home state (Options listed above): ");
        scanf("%c", &currentLetter);
        if(currentLetter != 10){
          currentPolitician.homeState[0] = toupper(currentLetter);
          i = 1;
          validInput = 0;
          while(!validInput){
            scanf("%c", &currentLetter);
            if(currentLetter == 10 || currentLetter == 32 || i == 3){
              validInput = 1;
              currentPolitician.homeState[i] = 0;
              if((currentLetter == 32 || i == 3) && currentLetter != 10){
                dummyClear = 0;
                while(dummyClear != 10){
                  scanf("%c", &dummyClear);
                }
              }
            } else {
              currentPolitician.homeState[i] = toupper(currentLetter);
            }
            i++;
          }
        } else {
          //null terminate at first index if no homeState entered
          currentPolitician.homeState[0] = 0;
        }
        for(i = 0; i < 50; i++){
          if(strcmp(stateAbbreviations[i], currentPolitician.homeState) == 0){
            validInput2 = 1;
          }
        }
        if(!validInput2){
          printf("Invalid party\n");
        }
      }
    }
    if(loopInput == 97){
      //Age and Sex
      currentNumber = -1;
      while(currentNumber < 18 || currentNumber > 99){
        printf("Enter politican age (18-99): ");
        scanf("%d", &currentNumber);
        if(currentNumber < 18 || currentNumber > 99){
          printf("Age out of range!\n");
        }
      }
      currentPolitician.age = currentNumber;
      //Sex 1 char
      validInput = 0;
      while(!validInput){
        printf("Enter politician Sex ('M' or 'F'): ");
        scanf("%c", &currentLetter);
        if(toupper(currentLetter) == 70 || toupper(currentLetter) == 77){
          validInput = 1;
          currentPolitician.sex = toupper(currentLetter);
          dummyClear = 0;
          while(dummyClear != 10){
            scanf("%c", &dummyClear);
          }
        }
      }
    }
    if(loopInput == 100){
      //display all info
      if(currentPolitician.firstName[0] == '-' || currentPolitician.lastName[0] == '-'){
        printf("Name not given.\n");
      } else {
        printf("Name: %s%s%s%s%s\n", currentPolitician.prefix,
                currentPolitician.firstName, currentPolitician.middleInitial,
                currentPolitician.lastName, currentPolitician.suffix);
      }
      if(currentPolitician.age == -1){
        //Only need to check age because both or neither complete because of error checking
        printf("Age and Sex not given.\n");
      } else {
        printf("Age: %i, Sex: %c\n", currentPolitician.age, currentPolitician.sex);
      }
    }
    if(loopInput == 99){
      //clear all info
      currentPolitician = setToDefaultPolitician();
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
