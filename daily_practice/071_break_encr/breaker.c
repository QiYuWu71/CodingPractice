#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int array_max(int *array){
    int max_loc = 0;
    int * max_array = array;

    for (int i=0;i<26;i++){
        if (array[i]>*max_array){
            *max_array = array[i];
            max_loc = i;
        }  
        }
    return max_loc;
}


void breaker(FILE *f){
    int c;
    int alphalist[26]={0};

    while (((c=fgetc(f))!= EOF)){
        if (isalpha(c)){
            c = tolower(c);
            alphalist[c-'a'] ++ ;
        }
    }
    int max_alpha = array_max(alphalist);
    int key = (max_alpha+26-4)%26;
    printf("%d\n",key);

}


int main(int argc, char ** argv){

if (argc != 2){
    fprintf(stderr,"Usage: breaker inputFileName\n");
    return EXIT_FAILURE;
}

FILE *f = fopen(argv[1],"r");
if (f==NULL){
    perror("Could not open file");
    return EXIT_FAILURE;
}
breaker(f);
if (fclose(f)!=0){
    perror("Failed to close the input file!");
    return EXIT_FAILURE;
}
return EXIT_SUCCESS;
}
