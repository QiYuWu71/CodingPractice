#include <stdlib.h>
#include <stdio.h>

struct _retire_info{
    int months;
    double contribution;
    double rate_of_return;
};

typedef struct _retire_info retire_info;


void retirement (int startAge, double initial, retire_info working, retire_info retired){

// while working

for (int i = 0; i<working.months; i++){
    printf("Age %3d month %2d you have $%.2lf\n",startAge/12,startAge%12,initial);
    initial = initial *(1+working.rate_of_return)+working.contribution;
    startAge ++;
}

// while retired

for (int i = 0; i<retired.months; i++){
    printf("Age %3d month %2d you have $%.2lf\n",startAge/12,startAge%12,initial);
    initial = initial *(1+retired.rate_of_return)+retired.contribution;
    startAge ++;
}

}


int main(void){

    retire_info working;
    retire_info retire;

    working.contribution = 1000;
    working.rate_of_return = 0.045/12;
    working.months = 489;

    retire.contribution = -4000;
    retire.rate_of_return = 0.01/12;
    retire.months = 384;

    retirement(327,21345,working,retire);
    return EXIT_SUCCESS;
}
