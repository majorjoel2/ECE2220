/**
 * Joel Tanner
 * 08-25-2021
 *
 * The goal of this project is to format input and output of data of a
 * politician.
 */

//Libraries used in this program
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <float.h>

/**
 * This structure holds all the information being tracked about the politician
 */
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

/**
 * This function will create a temp idiot to fill as blank values and then
 * return the default/blank idiot. This is used to see if input has been
 * recieved.
 *
 * @return struct idiot default values for politician
 */
struct idiot setToDefaultPolitician();

//refrence list of state names
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

//refrence list of state abbreviations
char stateAbbreviations[50][3] = {
  "AL", "AK", "AZ", "AR", "CA", "CO", "CT", "DE", "FL", "GA",
  "HI", "ID", "IL", "IN", "IA", "KS", "KY", "LA", "ME", "MD",
  "MA", "MI", "MN", "MS", "MO", "MT", "NE", "NV", "NH", "NJ",
  "NM", "NY", "NC", "ND", "OH", "OK", "OR", "PA", "RI", "SC",
  "SD", "TN", "TX", "UT", "VT", "VA", "WA", "WV", "WI", "WY"
};

//refrence list of party names
char partyName[5][13] = {
  "Constitution",
  "Democratic",
  "Green",
  "Libertarian",
  "Republican"
};

//refrence list of party abbreviations
char partyAbbreviation[5][4] = {
  "CON", "DEM", "GRE", "LIB", "REP"
};

int main(int arg, char **argv){
  //character reads
  char loopInput = 10, dummyClear, currentLetter;
  //booleans for checking valid input
  char validInput, validInput2;
  //active data being manipulated
  struct idiot currentPolitician = setToDefaultPolitician();
  //interator and input
  int i, currentNumber;
  //more input
  double currentDouble;
  long double currentLongDouble;

  while(loopInput != 113){
    //main menu
    printf("Enter the [c]haracter input for the corresponding choice.\n");
    printf("[N]ame\n[Y]ears, Party, Office, and State\n[A]ge and Sex\n");
    printf("[T]witter and Phone\nContributions and [W]ealth\n[D]isplay all Data\n");
    printf("[C]lear all Data\n[Q]uit\n");
    validInput = 0;
    //checking to see if input is a valid selection
    while(!validInput){
      scanf("%c", &loopInput);
      if(loopInput != 10){
        loopInput = tolower(loopInput);
        //possible valid selections
        if(loopInput == 110 || loopInput == 121 || loopInput == 97 ||
           loopInput == 116 || loopInput == 119 || loopInput == 100 ||
           loopInput == 99 || loopInput == 113){
          //
          validInput = 1;
        } else {
          printf("Invalid Selection\n");
        }
        //clear buffer
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
          //top scanning if new line, space, or max length
          if(currentLetter == 10 || currentLetter == 32 || i == 3){
            validInput = 1;
            //terminate string with ". "
            currentPolitician.prefix[i] = '.';
            currentPolitician.prefix[i+1] = ' ';
            currentPolitician.prefix[i+2] = 0;
            if((currentLetter == 32 || i == 3) && currentLetter != 10){
              dummyClear = 0;
              while(dummyClear != 10){
                scanf("%c", &dummyClear);
              }
            }
          } else { //continue scanning
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
          //stop scanning if new line, space, or max length
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
        //if a letter exists scan letter and terminate string
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
          //stop scanning if new line, space, or max length
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
          //stop scanning if new line, space, or max length
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
        //Inform user of invalid entry
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
          //Inform user of invalid entry
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
            currentPolitician.officeHeld[i] = 0;
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
          //Inform user of invalid entry
          printf("Invalid state\n");
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
        dummyClear = 0;
        while(dummyClear != 10){
          scanf("%c", &dummyClear);
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
        } else {
          //Inform user of invalid entry
          printf("Invalid Sex.\n");
        }
        dummyClear = 0;
        while(dummyClear != 10){
          scanf("%c", &dummyClear);
        }
      }
    }
    if(loopInput == 116){
      //twitter and phone number
      //twitter
      printf("Enter twitter handle: @");
      scanf("%c", &currentLetter);
      if(currentLetter != 10){
        currentPolitician.twitter[0] = currentLetter;
        i = 1;
        validInput = 0;
        while(!validInput){
          scanf("%c", &currentLetter);
          if(currentLetter == 10 || currentLetter == 32 || i == 15){
            validInput = 1;
            currentPolitician.twitter[i] = 0;
            if((currentLetter == 32 || i == 15) && currentLetter != 10){
              dummyClear = 0;
              while(dummyClear != 10){
                scanf("%c", &dummyClear);
              }
            }
          } else {
            currentPolitician.twitter[i] = currentLetter;
          }
          i++;
        }
      } else {
        //set twitter handle to - to indicate none given
        currentPolitician.twitter[0] = '-';
      }
      //phone number
      validInput2 = 0;
      while(!validInput2){
        printf("Enter politician phone number (Format: (111)222-3333): ");
        scanf("%c", &currentLetter);
        if(currentLetter != 10){
          currentPolitician.phoneNumber[0] = currentLetter;
          i = 1;
          validInput = 0;
          while(!validInput){
            scanf("%c", &currentLetter);
            if(currentLetter == 10 || currentLetter == 32 || i == 13){
              validInput = 1;
              currentPolitician.phoneNumber[i] = 0;
              if((currentLetter == 32 || i == 13) && currentLetter != 10){
                dummyClear = 0;
                while(dummyClear != 10){
                  scanf("%c", &dummyClear);
                }
              }
            } else {
              currentPolitician.phoneNumber[i] = currentLetter;
            }
            i++;
          }
        } else {
          //null terminate at first index if no homeState entered
          currentPolitician.phoneNumber[0] = 0;
        }
        if(currentPolitician.phoneNumber[0] == '(' &&
           currentPolitician.phoneNumber[4] == ')' &&
           currentPolitician.phoneNumber[8] == '-'){
          validInput2 = 1;
        }
        if(!validInput2){
          //Inform user of invalid entry
          printf("Invalid phone number\n");
        }
      }
    }
    if(loopInput == 119){
      //contributions and wealth
      //contributions
      currentDouble = -1;
      while(currentDouble < 0 || currentDouble > DBL_MAX){
        printf("Enter donations recieved (0-10e50 as float): ");
        scanf("%lf", &currentDouble);
        if(currentDouble < 0 || currentDouble > DBL_MAX){
          //Inform user of invalid entry
          printf("Contributions out of range!\n");
        }
        dummyClear = 0;
        while(dummyClear != 10){
          scanf("%c", &dummyClear);
        }
      }
      currentPolitician.donationsReceived = currentDouble;
      //wealth
      currentLongDouble = -1;
      while(currentLongDouble < 0 || currentLongDouble > LDBL_MAX){
        printf("Enter total Wealth (0-10e1000 as float): ");
        scanf("%Lf", &currentLongDouble);
        if(currentLongDouble < 0 || currentLongDouble > LDBL_MAX){
          //Inform user of invalid entry
          printf("Wealth out of range!\n");
        }
        dummyClear = 0;
        while(dummyClear != 10){
          scanf("%c", &dummyClear);
        }
      }
      currentPolitician.totalWealth = currentLongDouble;
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
      if(currentPolitician.officeHeld[0] == '-'){
        //only need to check one because all others have error checking
        printf("Years, party, office, and state not given.\n");
      } else {
        printf("Years Served: %i, Party Affiliation: %s\n", currentPolitician.yearsServed, currentPolitician.politicalParty);
        printf("Political Offics: %s, Home State: %s\n", currentPolitician.officeHeld, currentPolitician.homeState);
      }
      if(currentPolitician.twitter[0] == '-'){
        printf("Twitter handle and phone number not given.\n");
      } else {
        printf("Twitter: @%s, Phone Number: %s\n", currentPolitician.twitter, currentPolitician.phoneNumber);
      }
      if(currentPolitician.donationsReceived < 0 || currentPolitician.totalWealth < 0){
        printf("Donations and Wealth not given.\n");
      } else {
        printf("Donations: $%.2lf\n", currentPolitician.donationsReceived);
        printf("Wealth: $%.2Lf\n", currentPolitician.totalWealth);
      }
    }
    if(loopInput == 99){
      //clear all info
      currentPolitician = setToDefaultPolitician();
      printf("Data Cleared\n");
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
