#include "asset.hpp"
#include <cstdio>
#include <assert.h>
#include <cmath>
#include <iomanip>


// Matrix class for matrix computation;
// Matrix function construction is similar to my answers for assignment 103;
Matrix::Matrix(){
    numCol = 0;
    numRow = 0;
}
Matrix::Matrix(size_t init_numCol, size_t init_numRow){
            numCol = init_numCol;
            numRow = init_numRow;
            for (size_t i = 0; i<numRow; i++){
                amatrix.push_back(vector<double>(numCol));}

}
Matrix::Matrix(const Matrix & rhs){
    numRow = rhs.numRow;
    numCol = rhs.numCol;

    for (size_t i = 0;i<numRow;i++){
        amatrix.push_back(vector<double>(rhs[i]));
    }
  }

Matrix & Matrix::operator=(const Matrix & rhs){
numRow = rhs.numRow;
numCol= rhs.numCol;

for (size_t i = 0;i<numRow;i++){
    amatrix.push_back(vector<double>(rhs[i]));   
}
return *this;
}
size_t Matrix::getColumns()const{
    return numCol;
}
size_t Matrix::getRows()const{
    return numRow;
}

const vector<double> & Matrix::operator[](size_t index) const{
    assert((index>=0)&&(index<numRow));
    return amatrix[index];
}

vector<double> & Matrix::operator[](size_t index){
    assert((index>=0)&&(index<numRow));
    return amatrix[index];
}

Matrix Matrix::operator/(const Matrix &rhs) const{
    assert((numCol==rhs.numCol)&&(numRow==rhs.numRow));
    Matrix summatrix(numRow,numCol);
    for (size_t i=0;i<numRow;i++){
        for (size_t j=0;j<numCol;j++){
            summatrix.amatrix[i][j] = amatrix[i][j]/rhs.amatrix[i][j];
        }
}
    return summatrix;
  }


std::ostream & operator<<(std::ostream & s, const Matrix & rhs){
    s<< "[";
    for (size_t i = 0; i<rhs.getRows();i++){
        for (size_t j = 0; j < rhs.getColumns();j++){
            s<<setprecision(4)<<fixed;
            s.width(7);
            s<<rhs[i][j];
            if (j!=rhs.getColumns()-1){
                s<<",";
            }
        }
        if (i!=rhs.getRows()-1){
            s<<"\n";
            s<<" ";
        }}
    s<<"]";

return s;
}

// Asset Class storage data
Asset::Asset(string init_name,vector<double> init_ror){
    name = init_name;
    mean = 0;
    sd = 0;
    ror = init_ror;
}
double Asset::get_sd()const{
    return sd;
}

double Asset::get_mean()const{
    return mean;
}

void Asset::avg_ror(){
    double ror_sum = 0;
    for (vector<double>::iterator i = ror.begin();i<ror.end();i++){
        ror_sum += *i;
    }
    mean = ror_sum/(ror.size()-1);
}

void Asset::sd_ror(){
    double ror_diff = 0;
    for (size_t i = 1;i<ror.size();i++){

        ror_diff += (ror[i] - mean)*(ror[i] - mean);
    }
    sd = sqrt(ror_diff/(ror.size()-2));
}

double Asset::cov_ror(Asset &rhs){
    assert(ror.size()==rhs.ror.size());
    double cov;
    double diff = 0;
    for (size_t i = 1;i<ror.size();i++){
        diff += (ror[i]-mean)*(rhs.ror[i]-rhs.mean);
    }
    cov = diff/(ror.size()-1);
    return cov;
}

double Asset::corr_ror(Asset &rhs){
    double corr;
    corr = Asset::cov_ror(rhs)/(sd*rhs.sd);
    return corr;
}

void Asset::print_asset() const{
    cout<<name<<endl;
}

