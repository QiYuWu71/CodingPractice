#include<stdlib.h>
#include<stdio.h>
#include<string.h>

void rotateMatrix(FILE *f){
    char matrix[10][10] = {{0}};
    char buffer[12];

    int line_num = 0;

    while (fgets(buffer,12,f)!=NULL){
        if (strchr(buffer,'\n')==NULL){
            fprintf(stderr,"The line is longer than 10 length.\n");
            exit(EXIT_FAILURE);
        }
        if (strlen(buffer)<10){
            fprintf(stderr,"The line is smaller than 10 length.\n");
            exit(EXIT_FAILURE);
        }

        if (line_num>=10){
            fprintf(stderr,"The number of line is larger than 10.\n");
            exit(EXIT_FAILURE);
        }
        for (int col=0;col<10;col++){
            matrix[line_num][col] = buffer[col];
        }
        line_num++;
    }
    if (line_num<10){
        fprintf(stderr,"The number of line is smaller than 10.\n");
        exit(EXIT_FAILURE);
    }

    for (int row=0;row<10;row++){
        for (int col=0;col<10;col++){
            printf("%c",matrix[10-1-col][row]);
    }
    printf("\n");
    }}

int main(int argc, char ** argv){
    if (argc != 2){
        fprintf(stderr,"Usage: rotateMatrix FileName\n");
        return EXIT_FAILURE;        
    }

    FILE *f = fopen(argv[1],"r");
    if (f==NULL){
        perror("Could not open file");
        return EXIT_FAILURE;
    }
    rotateMatrix(f);
    if (fclose(f)!=0){
        perror("Failed to close the input file!");
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}
