#include "IntArray.h"
#include <assert.h>
#include <ostream>
#include <iostream>

IntArray::IntArray() {
    data = NULL;
    numElements = 0;
}

IntArray::IntArray(int n) {
    data = new int[n];
    numElements = n;
}

IntArray::IntArray(const IntArray & rhs)  {
    data = new int[rhs.numElements];
    numElements = rhs.numElements;
    for (int i =0;i<rhs.numElements;i++){
       data[i] = rhs.data[i];
    }
}

IntArray::~IntArray(){
    delete[] data;
}

IntArray & IntArray::operator=(const IntArray & rhs) {
// we need to delete the current array to allocate the new length for the rhs
    if (this != &rhs){
        delete[] this->data;
        int* newdata = new int[rhs.numElements];
        for (int i = 0;i<rhs.numElements;i++){
            newdata[i] = rhs.data[i];
        }
        this->data = newdata;
        this->numElements = rhs.numElements;
    }
    return *this;
    
}
const int & IntArray::operator[](int index) const {
    assert((0<=index)&&(index<numElements));
    return data[index];

}
int & IntArray::operator[](int index) {
 // check whether the index within the bounds
 // greater or equal to zero
    assert((0<=index)&&(index<numElements));
    return data[index];

}

int IntArray::size() const {
    return numElements;
}

bool IntArray::operator==(const IntArray & rhs) const {
    if (this->numElements!=rhs.numElements){return false;}

    for (int i =0; i<this->numElements;i++){
        if (this->data[i]!=rhs.data[i]){
            return false;
        }
    }
    return true;
}

bool IntArray::operator!=(const IntArray & rhs) const {
    return !(*this == rhs);
}

std::ostream & operator<<(std::ostream & s, const IntArray & rhs) {
// to check when the size is zero or not.

if (rhs.size()>0){
    s<< "{";
    for (int i = 0; i<rhs.size();i++){
        s<< rhs[i];
        if (i!=rhs.size()-1){
            s<<", ";
        }
        else{
            s<<"}";
        }
}
}
else{
    s<<"{}";
}
return s;
}
