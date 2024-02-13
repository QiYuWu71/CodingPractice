#include <iostream>
#include <ctype.h>
#include <cstdlib>
#include <string.h>
#include <vector>

using namespace std;

class Asset{
    private:
        string name;
        double mean;
        double sd;

    public:
        Asset(string init_name, double init_mean, double init_sd);
        double get_sd()const;
        double get_mean()const;
        ~Asset(){}
};
