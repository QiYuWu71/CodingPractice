#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include "parse.cpp"

int main(int argc, char **argv){
    if (argc < 2){
        fprintf(stderr,"Usage: correl_matrix inputFileName\n");
        exit(EXIT_FAILURE);
    }
    if (argc >2){
        fprintf(stderr,"Usage: correl_matrix inputFileName\n");
        exit(EXIT_FAILURE);
    }
    std::ifstream ifs(argv[1]);
    
    if (!ifs.is_open()){
        fprintf(stderr,"Can not open the file!\n");
        exit(EXIT_FAILURE);
    }
    parse(ifs);
    ifs.close();
    return EXIT_SUCCESS;
}
