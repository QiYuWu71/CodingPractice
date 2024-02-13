#include <iostream>
#include <Eigen/Dense>
#include <stdio.h>
#include <stdlib.h>
#include "matrix_cal.cpp"
#include <fstream>

int main(int argc, char **argv){
    if (argc < 3 || argc > 4){
        fprintf(stderr,"Can not open the file!\n");
        exit(EXIT_FAILURE);
    }
    if (argc == 3){
        std::ifstream univ(argv[1]);
        if (!univ.is_open()){
            fprintf(stderr,"Can not open the file!\n");
            exit(EXIT_FAILURE);
        }
        vector<Asset *> portfolio = record_asset(univ);
        univ.close();

        size_t mat_len = portfolio.size();
        std::ifstream corr_file(argv[2]);
        int flag = 0;
        if (!corr_file.is_open()){
            fprintf(stderr,"Can not open the file!\n");
            exit(EXIT_FAILURE);
        }
        MatrixXd cov_mat = cov_matrix(mat_len,corr_file,portfolio);
        corr_file.close();
        MatrixXd volat_mat = volat_matrix(portfolio,cov_mat,mat_len,flag);
        std::cout<<volat_mat<<std::endl;
        for (size_t i=0; i<mat_len;i++){
            delete portfolio[i];
        }
    }
    else if(argc == 4){
        if (strcmp(argv[1],"-r") != 0){
            fprintf(stderr,"Wrong Argument\n");
            exit(EXIT_FAILURE);
        }
        else{
        std::ifstream univ(argv[2]);
        vector<Asset *> portfolio = record_asset(univ);
        if (!univ.is_open()){
            fprintf(stderr,"Can not open the file!\n");
            exit(EXIT_FAILURE);
        }
        univ.close();
        size_t mat_len = portfolio.size();

        std::ifstream corr_file(argv[3]);
        int flag = 1;
        if (!corr_file.is_open()){
            fprintf(stderr,"Can not open the file!\n");
            exit(EXIT_FAILURE);
        }
        MatrixXd cov_mat = cov_matrix(mat_len,corr_file,portfolio);
        corr_file.close();
        MatrixXd volat_mat = volat_matrix(portfolio,cov_mat,mat_len,flag);
        std::cout<<volat_mat<<std::endl;

        for (size_t i=0; i<mat_len;i++){
            delete portfolio[i];
        }
    }
    }
    return EXIT_SUCCESS;
}
