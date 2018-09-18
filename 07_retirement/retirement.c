#include <stdio.h>
#include <stdlib.h>

struct retire_info{
  int months;
  double contribution;
  double rate_of_return;
};

typedef struct retire_info balance;

int getYears(int age){
  return age / 12;
}

int getMonths(int age){
  return age % 12;
}

void retirement(int startAge, //in months
		double initial, //initial savings in dollars
		balance working, //info about working
		balance retired){
  double bal = initial;
  printf("Age %3d month %2d you have $%.2f\n", getYears(startAge), getMonths(startAge), bal);

  for (int i = 1; i <= working.months; i++) {
    startAge++;
    bal = bal + bal * working.rate_of_return + working.contribution;
    printf("Age %3d month %2d you have $%.2f\n", getYears(startAge), getMonths(startAge), bal);
  }
  for (int i = 1; i < retired.months; i++) {
    startAge++;
    bal = bal + bal * retired.rate_of_return + retired.contribution;
    printf("Age %3d month %2d you have $%.2f\n", getYears(startAge), getMonths(startAge), bal);
  }
}

int main(){
  balance w, r;
  w = (balance){489, 1000, 0.045/12};
  r = (balance){384, -4000, 0.01/12};
  retirement(327, 21345, w, r);
  return 0;
}
