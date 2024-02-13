#include "IntMatrix.h"

IntMatrix::IntMatrix(){
    numColumns = 0;
    numRows = 0;
    rows = NULL;
}
IntMatrix::IntMatrix(int r, int c) {
    numColumns = c;
    numRows = r;
    rows = new IntArray*[numRows];
    for (int i=0;i<numRows;i++){
        rows[i] = new IntArray(numColumns);
    }
}
IntMatrix::IntMatrix(const IntMatrix & rhs)  {
    numColumns = rhs.numColumns;
    numRows = rhs.numRows;
    rows = new IntArray*[numRows];
    for (int i=0;i<numRows;i++){
        rows[i] = new IntArray(numColumns);
    }
    for (int i=0;i<numRows;i++){
        for (int j=0;j<numColumns;j++){
            (*rows[i])[j] = (*rhs.rows[i])[j];
        }
    }
}
IntMatrix::~IntMatrix() {
    // delete each row arrays first'
    // delete the rows second;
    // then we need to delete the whole matrix

    for (int i=0;i<numRows;i++){
        delete rows[i];
    }
    delete[] rows;
}
IntMatrix &IntMatrix::operator=(const IntMatrix & rhs) {
    if (this!=&rhs){
        for (int i=0;i<this->numRows;i++){
            delete this->rows[i];
        }
        delete[] this->rows;
        this->numColumns = rhs.numColumns;
        this->numRows = rhs.numRows;
        IntArray ** newrows = new IntArray*[numRows];
        for (int i=0;i<numRows;i++){
            newrows[i] = new IntArray(numColumns);
        }
        for (int i=0;i<numRows;i++){
            for (int j=0;j<numColumns;j++){
                (*newrows[i])[j]=(*rhs.rows[i])[j];
            }
        }
        this->rows = newrows;
}
return *this;
}

int IntMatrix::getRows() const {
    
    return numRows;

}
int IntMatrix::getColumns() const {
    return numColumns;

}
const IntArray & IntMatrix::operator[](int index) const {
    assert((index>=0)&&(index<numRows));
    return *rows[index];
}
IntArray & IntMatrix::operator[](int index){
    assert((index>=0)&&(index<numRows));
    return *rows[index];
}

bool IntMatrix::operator==(const IntMatrix & rhs) const {

if ((this->numRows != rhs.numRows)||(this->numColumns!=rhs.numColumns)){
    return false;
}
else{
    for (int i=0;i<numRows;i++){
        for (int j=0;j<numColumns;j++){
            if ((*this->rows[i])[j]!=(*rhs.rows[i])[j]){
                return false;
            }
        }
}
return true;
}}


IntMatrix IntMatrix::operator+(const IntMatrix & rhs) const {
    assert((this->numColumns==rhs.numColumns)&&(this->numRows==rhs.numRows));
    IntMatrix newthis(numRows,numColumns);
    for (int i=0;i<numRows;i++){
        for (int j=0;j<numColumns;j++){
            (*newthis.rows[i])[j] = (*this->rows[i])[j] + (*rhs.rows[i])[j];
        }
}
  return newthis;
}

std::ostream & operator<<(std::ostream & s, const IntMatrix & rhs) {

    s<< "[ ";
    for (int i = 0; i<rhs.getRows();i++){
        s<< rhs[i];
        if (i!=rhs.getRows()-1){
            s<<",\n";
        }}
    s<<" ]";


return s;
}


