#include <stdio.h>
#include <stdlib.h>

struct _retire_info{
  int months;
  double contribution;
  double rate_of_return;
};

typedef struct _retire_info retire_info;

int getYears(int age){
  return age / 12;
}

int getMonths(int age){
  return age % 12;
}

void retirement(int startAge, //in months
		double initial, //initial savings in dollars
		retire_info working, //info about working
		retire_info retired){
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

int main(void){
  retire_info w, r;
  w = (retire_info){489, 1000, 0.045/12};
  r = (retire_info){384, -4000, 0.01/12};
  retirement(327, 21345, w, r);
  return 0;
}
