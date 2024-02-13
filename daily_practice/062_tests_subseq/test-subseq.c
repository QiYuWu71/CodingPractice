#include <stdio.h>
#include <stdlib.h>

void run_check(int testnum,int *array, size_t n,size_t ans){
    size_t temp = maxSeq(array,n);
    if (temp != ans){
        printf("The result is wrong.");
        exit(EXIT_FAILURE);
}}

int main(void){

    run_check(1,NULL,0,0);
    int myArray[0] = {};
    run_check(2,myArray,0,0);
    int myArray1[1] = {1};
    run_check(3,myArray1,1,1);
    int myArray2[5] = {-2,-1,0,1,2};
    run_check(4,myArray2,5,5);
    int myArray3[4] = {1,2,3,4};
    run_check(5,myArray3,4,4);
    int myArray4[6] = {1,1,2,2,3,3};
    run_check(6,myArray4,6,2);
    int myArray5[7] = {1,2,3,1,2,3,4};
    run_check(7,myArray5,7,4);
    int myArray6[4] = {1,1,1,1};
    run_check(8,myArray6,4,1);
    int myArray7[4] = {-1,2,2,1};
    run_check(4,myArray7,4,2);
    printf("Yes");

    return EXIT_SUCCESS;
}