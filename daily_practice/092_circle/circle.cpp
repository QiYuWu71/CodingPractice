#include "circle.hpp"

#include <cmath>
#include <cstdio>


Circle::Circle(Point init_point, const double init_radius){center = init_point; radius = init_radius;}

void Circle::move(double dx, double dy){
    center.move(dx,dy);
}

double r_min(double x,double y){
    if (x>y) {
        return y;
    }
    else{
        return x;
    }
}
double part_area(double r,double d){

    double A = r*r*(std::acos)(d/r)-d*(std::sqrt)(r*r-d*d);

    return A;
}

double Circle::intersectionArea(const Circle & otherCircle){
    double distance = center.distanceFrom(otherCircle.center);
    if (distance > radius+otherCircle.radius){
        return 0;
    }
    if (distance <= (std::abs)(radius-otherCircle.radius)){
        double r = r_min(radius,otherCircle.radius);
        double r_area = r*r*M_PI;
        return r_area;
    }
    double r1 = radius;
    double r2 = otherCircle.radius;
    double d1 = (r1*r1-r2*r2+distance*distance)/(2*distance);
    double d2 = distance-d1;
    double A1 = part_area(r1,d1);
    double A2 = part_area(r2,d2);
    double total = A1+A2;
    return total;
}
