#include <Eigen/Dense>
#include <cstdio>
#include <iomanip>
#include <cmath>
#include "asset.hpp"
using namespace Eigen;

vector<string> asset_info(string info){
    vector<string> asset;
    string delim = ",";
    auto start = 0U;
    auto end = info.find(delim);
    while (end != string::npos){
        asset.push_back(info.substr(start,end-start));
        start = end+delim.length();
        end = info.find(delim,start);
    }
    asset.push_back(info.substr(start,end));
    if (asset.size() != 3){
        fprintf(stderr,"Error: Line formats are wrong.\n");
        exit(EXIT_FAILURE);
    }
    return asset;
}
vector<Asset *> record_asset(istream&univ){
    std::string line;
    vector<string> lines;
    while (getline(univ,line)){
        lines.push_back(line);
    }
    if ((univ.eof()!=1)&&(univ.good()!=1)){
        fprintf(stderr,"Error in reading files.\n");
        exit(EXIT_FAILURE);
    }
    
    size_t nasset = lines.size();
    vector<Asset *> portfolio;
    vector<string> asset;
    double asset_sd;
    double asset_mean;
    for (size_t i = 0; i<nasset;i++){
        asset = asset_info(lines[i]);
        try{
            asset_mean = stod(asset[1]);
        }catch(...){
            cerr << "Invalid argument"<< endl;
            exit(EXIT_FAILURE);
        }
        try{
            asset_sd = stod(asset[2]);
            if (asset_sd < 0){
                cerr << "Invalid argument"<< endl;
                exit(EXIT_FAILURE);
            };
        }
        catch(...){
            cerr << "Invalid argument"<< endl;
            exit(EXIT_FAILURE);
        }
        Asset *port = new Asset(asset[0],asset_mean,asset_sd);
        portfolio.push_back(port);
    }
    return portfolio;
}

vector<double> matrix_line(string line,size_t mat_len){
        
    vector<double> mat_line;
    string delim = ",";
    auto start = 0U;
    auto end = line.find(delim);
    while (end != string::npos){
        string s = line.substr(start,end-start);
        try{
        double num = stod(s);
        if (num>1 || num<-1){
            cerr << "Invalid argument"<< endl;
            exit(EXIT_FAILURE);
        };
        mat_line.push_back(num);
        }catch(...){
            cerr << "Invalid argument"<< endl;
            exit(EXIT_FAILURE);
        }
        start = end+delim.length();
        end = line.find(delim,start);
    }
    string s = line.substr(start,end-start);
    try{
        double num = stod(s);
        mat_line.push_back(num);
        if (num>1 || num<-1){
            cerr << "Invalid argument"<< endl;
            exit(EXIT_FAILURE);
        };
    }catch(...){
        cerr << "Invalid argument"<< endl;
        exit(EXIT_FAILURE);
    }
    if (mat_line.size() != mat_len){
        fprintf(stderr,"Error: Line formats are wrong.\n");
        exit(EXIT_FAILURE);
    }
    return mat_line;
}

MatrixXd cov_matrix(size_t mat_len,istream&corr_file,vector<Asset *> portfolio){
    std::string line;
    vector<string> lines;
    
    while(getline(corr_file,line)){
        lines.push_back(line);
    }
    if ((corr_file.eof()!=1)&&(corr_file.good()!=1)){
        fprintf(stderr,"Error in reading files.\n");
        exit(EXIT_FAILURE);
    }

    if (lines.size()!=mat_len){
        fprintf(stderr,"Files' informations do not match.\n");
        exit(EXIT_FAILURE);
    }

    MatrixXd corr_mat(mat_len,mat_len);
    for (size_t i = 0;i < mat_len;i++){
        vector<double> mat_line = matrix_line(lines[i],mat_len);
        for (size_t j = 0; j < mat_len;j++){
            if (i==j){
                if (mat_line[j]!=1){
                    fprintf(stderr,"Wrong correlation matrix.\n");
                    exit(EXIT_FAILURE);
                }
            }
            corr_mat(i,j) = mat_line[j];
        }
    }
    if (corr_mat!= corr_mat.transpose()){
            fprintf(stderr,"Wrong correlation matrix.\n");
            exit(EXIT_FAILURE);
    }
    MatrixXd cov_mat(mat_len,mat_len);
    for (size_t i = 0;i < mat_len;i++){
        for (size_t j = 0; j < mat_len;j++){
            cov_mat(i,j) = corr_mat(i,j)*portfolio[i]->get_sd()*portfolio[j]->get_sd();
        }
    }

    return cov_mat;
}


VectorXd unres_eff(vector<Asset *> portfolio, MatrixXd cov_mat, size_t mat_len,double E_ror){
    MatrixXd ror_mean = MatrixXd::Constant(2,mat_len,1);
    for (size_t i = 0; i<mat_len;i++){
        ror_mean(1,i) = portfolio[i]->get_mean();
    }

    MatrixXd A = MatrixXd::Constant(mat_len+2,mat_len+2,0);
    A.block(0,0,mat_len,mat_len)= cov_mat;
    A.block(mat_len,0,2,mat_len) = ror_mean;
    A.block(0,mat_len,mat_len,2) = ror_mean.transpose();
    VectorXd b  = VectorXd::Constant(mat_len+2,0);
    b(mat_len) = 1;
    b(mat_len+1) = E_ror;
    VectorXd weight = A.colPivHouseholderQr().solve(b);
    return weight;
}


VectorXd res_eff(vector<Asset *> portfolio, MatrixXd cov_mat,size_t mat_len,double E_ror){
    MatrixXd ror_mean = MatrixXd::Constant(2,mat_len,1);
    for (size_t i = 0; i<mat_len;i++){
        ror_mean(1,i) = portfolio[i]->get_mean();
    }
    MatrixXd A = MatrixXd::Constant(mat_len+2,mat_len+2,0);
    A.block(0,0,mat_len,mat_len)= cov_mat;
    A.block(mat_len,0,2,mat_len) = ror_mean;
    A.block(0,mat_len,mat_len,2) = ror_mean.transpose();
    VectorXd b  = VectorXd::Constant(mat_len+2,0);
    b(mat_len) = 1;
    b(mat_len+1) = E_ror;
    VectorXd ans = A.colPivHouseholderQr().solve(b);
    VectorXd weight = ans(seq(0,mat_len-1));

    vector<size_t> res_x;
    int nega_iden = 0;
    for (size_t i = 0; i < mat_len;i++){
        if (weight(i)<0){
            res_x.push_back(i);
            nega_iden++;
        }
    }
    while (nega_iden!=0){
        VectorXd nb = VectorXd::Constant(mat_len+2+res_x.size(),0);
        nb(mat_len) = 1;
        nb(mat_len+1) = E_ror;

        MatrixXd nA = MatrixXd::Constant(mat_len+2+res_x.size(),mat_len+2+res_x.size(),0);
        nA.block(0,0,mat_len+2,mat_len+2) = A;
        for (size_t j = 0; j < res_x.size();j++){
            nA(mat_len+2+j,res_x[j]) = 1;
            nA(res_x[j],mat_len+2+j) = 1;
        }
        VectorXd ans = nA.colPivHouseholderQr().solve(nb);
        VectorXd weight = ans(seq(0,mat_len-1));

        int nega_iden = 0;
        for (size_t i = 0; i < mat_len;i++){
            if (weight(i)<0){
                res_x.push_back(i);
                nega_iden++;
            }
        }
        if (nega_iden == 0){
            return weight;
        }
    }
    return weight;
}

double volat(VectorXd weight, MatrixXd cov_mat){
    double risk2;
    risk2 = weight.transpose()*cov_mat*weight;
    double risk = sqrt(risk2);
    return risk;
}

MatrixXd volat_matrix(vector<Asset *> portfolio, MatrixXd cov_mat, size_t mat_len,int flag){
    MatrixXd volat_mat(26,2);
    double e = 1;
    for (size_t i=0;i<26;i++){
        volat_mat(i,0) = e;
        if (flag == 0){
            VectorXd ans= unres_eff(portfolio,cov_mat,mat_len,e/100);
            VectorXd weight = ans(seq(0,mat_len-1));
            double volatility = volat(weight,cov_mat);
            volat_mat(i,1) = volatility*100;
        }else{
            VectorXd weight= res_eff(portfolio,cov_mat,mat_len,e/100);
            double volatility = volat(weight,cov_mat);
            volat_mat(i,1) = volatility*100;
        }
        e++;
    }
    return volat_mat;
}

std::ostream & operator<<(std::ostream & s,MatrixXd volat_mat){
    s<<"ROR,volatility"<<"\n";
    for (size_t i = 0; i<26;i++){
        s<<setprecision(1)<<fixed;
        s<<volat_mat(i,0)<<"%"<<",";
        s<<setprecision(2)<<fixed;
        if (i!=25){
            s<<volat_mat(i,1)<<"%"<<"\n";
        }else{
            s<<volat_mat(i,1)<<"%";
        }
    }
return s;
}
