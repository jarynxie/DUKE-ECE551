#include <stdio.h>
#include <stdlib.h>

struct _retire_info {
  int months;
  double contribution;
  double rate_of_return;
};
typedef struct _retire_info retire_info;

double updateInfo(int startAge, double initialSavings, retire_info retireInfo) {
  double curSavings = initialSavings;
  int curAge = startAge;
  for (int i = 0; i < retireInfo.months; i++) {
    printf("Age %3d month %2d you have $%.2lf\n", curAge / 12, curAge % 12, curSavings);
    curSavings += curSavings * retireInfo.rate_of_return + retireInfo.contribution;
    curAge++;
  }
  return curSavings;
}

void retirement(int startAge, double initial, retire_info working, retire_info retired) {
  double savings = initial;
  savings = updateInfo(startAge, initial, working);
  savings = updateInfo(startAge + working.months, savings, retired);
}

int main() {
  retire_info Working;
  Working.months = 489;
  Working.contribution = 1000;
  Working.rate_of_return = 0.045 / 12;
  retire_info Retired;
  Retired.months = 384;
  Retired.contribution = -4000;
  Retired.rate_of_return = 0.01 / 12;
  retirement(327, 21345, Working, Retired);
  return EXIT_SUCCESS;
}
