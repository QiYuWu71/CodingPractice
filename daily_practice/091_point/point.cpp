#include "point.hpp"

#include <cmath>
#include <cstdio>
using namespace std;

Point::Point(){x=0;y=0;}

void Point::move(double dx, double dy){
    x += dx;
    y += dy;
}

double Point::distanceFrom(const Point &p){
    double dx =x-p.x ;
    double dy =y-p.y ;

    double distance = (std::sqrt)(dx*dx+dy*dy);
    return distance;
}