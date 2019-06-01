#include<stdlib.h>
#include<stdio.h>

struct _retire_info {
  int months;
  double contribution;
  double rate_of_return;
};
typedef struct _retire_info retire_info;

double balanceUpdate (retire_info period,double balance, int age){
  int n = period.months;
  for (int i=1; i<= n; i++){
    printf("Age %3d month %2d you have $%.2f\n",age/12,age%12,balance);
    balance = balance*(1+period.rate_of_return)+period.contribution;
    age++;
  }
  return balance;
}
void retirement (int startAge,
		 double initial,
		 retire_info working,
		 retire_info retired){
  double balanceAfterWorking = balanceUpdate(working,initial,startAge);
  balanceUpdate(retired,balanceAfterWorking,startAge+working.months);
}
int main(){
  retire_info Working;
  Working.months = 489;
  Working.contribution = 1000;
  Working.rate_of_return = 0.045/12;

  retire_info retired;
  retired.months = 384;
  retired.contribution = -4000;
  retired.rate_of_return = 0.01/12;
  // start conditions
  int Age = 327;
  double savings = 21345;
  retirement(Age,savings,Working,retired);
  return 0;
}
  
