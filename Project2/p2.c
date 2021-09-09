

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct idiot {
  char[3] prefix;
  char[32] firstName;
  char middleInitial;
  char[32] lastName;
  char[3] suffix;
  int age;
  char sex;
  char[32] officeHeld;
  int yearsServed;
  char[3] politicalParty;
  char[2] homeState;
  char[15] twitter;
  char[13] phoneNumber;
  double donationsReceived;
  long double totalWealth;
};

idiot setToDefaultPolitician();

int main(int arg, char **argv){
  return 1;
}

idiot setToDefaultPolitician(){
  idiot default_politician;
  default_politician.prefix = '-';
  default_politician.firstName = '-';
  default_politician.middleInitial = '-';
  default_politician.lastName = '-';
  default_politician.suffix = '-';
  default_politician.age = -1;
  default_politician.sex = '-';
  default_politician.officeHeld = '-';
  default_politician.yearsServed = -1;
  default_politician.politicalParty = '-';
  default_politician.homeState = '-';
  default_politician.twitter = '-';
  default_politician.phoneNumber = '-';
  default_politician.donationsReceived = -0.1;
  default_politician.totalWealth = -0.1;
  return default_politician;
}
