#include <stdio.h>
#include <stdlib.h>

void series18(int x){
    int value = 0;
    for (int i= 0;i<3*x;i++){
        if (i == 0){
            value = -(x*x);
        }
        else{
            value += (i-1)*2+1;
        }
        printf("%d ",value);
    }
    printf("\n");
}


int main(int argc, char *argv[]){
    if (argc < 2){
        printf("N not specified\n");
        printf("usage: series18 N\n");
        return 1;
    }
    int n = atoi(argv[1]);
    series18(n);
    return 0;
}