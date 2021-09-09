

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct idiot {
  char prefix[3];
  char firstName[32];
  char middleInitial;
  char lastName[32];
  char suffix[3];
  int age;
  char sex;
  char officeHeld[32];
  int yearsServed;
  char politicalParty[3];
  char homeState[2];
  char twitter[15];
  char phoneNumber[13];
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
  return 1;
}

struct idiot setToDefaultPolitician(){
  struct idiot default_politician;
  default_politician.prefix[0] = '-';
  default_politician.firstName[0] = '-';
  default_politician.middleInitial = '-';
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
