#include "point.hpp"

class Circle{
    private:
        Point center;
        double radius;
    
    public:
        Circle();
        Circle(Point init_point, const double init_radius);
        void move (double dx, double dy);
        double intersectionArea(const Circle & otherCircle);
};
