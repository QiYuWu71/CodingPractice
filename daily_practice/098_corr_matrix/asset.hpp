#include <iostream>
#include <ctype.h>
#include <cstdlib>
#include <string.h>
#include <vector>

using namespace std;

class Matrix{
    private:
        size_t numCol;
        size_t numRow;
        vector< vector<double> > amatrix;

    public:
        Matrix();
        Matrix(size_t init_numCol, size_t init_numRow);
        Matrix(const Matrix&rhs);
        Matrix & operator=(const Matrix & rhs);
        size_t getRows()const;
        size_t getColumns()const;
        const vector<double>& operator[](size_t index) const;
        vector<double> & operator[](size_t index);
        Matrix operator/(const Matrix&rhs)const;
        ~Matrix(){}
};

std::ostream & operator<<(std::ostream & s, const Matrix & rhs);

class Asset{
    private:
        string name;
        vector<double> ror;
        double mean;
        double sd;

    public:
        Asset(string init_name, vector<double> init_ror);
        double get_sd()const;
        double get_mean()const;
        void avg_ror();
        void sd_ror();
        double cov_ror(Asset &rhs);
        double corr_ror(Asset &rhs);
        void print_asset()const;
        ~Asset(){}

};
