#include "asset.hpp"

// Asset Class storage data

Asset::Asset(string init_name,double init_mean, double init_sd){
    name = init_name;
    mean = init_mean;
    sd = init_sd;
}
double Asset::get_sd()const{
    return sd;
}

double Asset::get_mean()const{
    return mean;
}
