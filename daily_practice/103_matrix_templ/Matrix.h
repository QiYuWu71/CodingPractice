#ifndef __T_MATRIX_H___
#define __T_MATRIX_H___

#include <assert.h>
#include <iostream>
#include <vector>
#include <cstdlib>
using namespace std;

template <typename T>

class Matrix {
 private:
  int numRows;
  int numColumns;
  vector< vector<T> > rows;
 public:
  Matrix<T>(){numRows = 0;
                numColumns=0;}

  Matrix<T>(int r, int c){
    numRows = r;
    numColumns = c;
    for (int i =0;i<numRows;i++){
        rows.push_back(vector<T>(numColumns));
    }
  }

  Matrix<T>(const Matrix & rhs){
    numRows = rhs.numRows;
    numColumns = rhs.numColumns;

    for (int i = 0;i<numRows;i++){
        rows.push_back(vector<T>(rhs[i]));
    }
  }

  ~Matrix(){}

  Matrix<T> & operator=(const Matrix<T> & rhs){
    numRows = rhs.numRows;
    numColumns = rhs.numColumns;

    for (int i = 0;i<numRows;i++){
        rows.push_back(vector<T>(rhs[i]));   
    }
    return *this;
  }

  int getRows() const{
    return numRows;
  }
  int getColumns() const{
    return numColumns;
  }

  const vector<T>& operator[](int index) const{
    assert((index>=0)&&(index<numRows));
    return rows[index];
  }

  vector<T> & operator[](int index){
    assert((index>=0)&&(index<numRows));
    return rows[index];
  }

  bool operator==(const Matrix<T> & rhs) const{
    if ((numColumns!=rhs.numColumns)||(numRows!=rhs.numRows)||(rows!=rhs.rows)){
        return false;
    }
    return true;
  }

  Matrix<T> operator+(const Matrix<T> & rhs) const{
    assert((numColumns==rhs.numColumns)&&(numRows==rhs.numRows));
    Matrix<T> summatrix(numRows,numColumns);
    for (int i=0;i<numRows;i++){
        for (int j=0;j<numColumns;j++){
            summatrix.rows[i][j] = rows[i][j]+rhs.rows[i][j];
        }
}
    return summatrix;
  }

};

template <typename T>
std::ostream & operator<<(std::ostream & s, const Matrix<T> & rhs){

    s<< "[ ";
    for (int i = 0; i<rhs.getRows();i++){
        s<< "{";

        for (int j = 0; j < rhs.getColumns();j++){
            s<<rhs[i][j];
            if (j!=rhs.getColumns()-1){
                s<<", ";
            }
        }
        s<<"}";
        if (i!=rhs.getRows()-1){
            s<<",\n";
        }}
    s<<" ]";

return s;
}


#endif