#ifndef ELLIPSE_H
#define ELLIPSE_H

#include "point.h"
#include "figure.h"
#include <iostream>
#include <cmath>

template<typename CoordType, typename RadiusType>
class Ellipse : public Figure {
    Point<CoordType> center;
    RadiusType a, b;

    bool is_valid() const {
        return a > 0 && b > 0;
    }

public:
    Ellipse(const Point<CoordType>& c, RadiusType a, RadiusType b)
        : center(c), a(a), b(b) {
        if (!is_valid())
            throw FigureException();
    }

    Ellipse(CoordType x, CoordType y, RadiusType a, RadiusType b)
        : Ellipse(Point<CoordType>{x, y}, a, b) {}

    double calc_area() override {
        return PI * a * b;
    }

    double calc_perimetr() override {
        return PI * (3*(a + b) - std::sqrt((3*a + b)*(a + 3*b)));
    }

    void name() override {
        std::cout << "Ellipse" << std::endl; 
    }

    std::string getType() override { return "Ellipse"; }
};

#endif