#include <stdio.h>
#include <stdlib.h>

size_t maxSeq(int * array, size_t n){
    if (array==NULL||n == 0){return 0;}
    size_t max_length = 1;
    size_t current_length = 1;

    for (int i =1;i<n;i++){
        if (array[i]>array[i-1]){
            current_length++;
        }
        else{
            if (current_length>max_length){
                max_length = current_length;
            }
            current_length = 1;
        }
    }
    if (current_length > max_length){
        max_length = current_length;
    }
    return max_length;
}
