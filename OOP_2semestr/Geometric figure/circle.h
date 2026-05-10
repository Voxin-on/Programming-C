#ifndef CIRCLE_H
#define CIRCLE_H

#include "point.h"
#include "figure.h"
#include <iostream>
#include <cmath>

template<typename CoordType, typename SizeType>
class Circle : public Figure {
    Point<CoordType> center;
    double radius;

    bool is_valid() const {
        return radius > 0;
    }

public:
    Circle(const Point<CoordType>& c, SizeType r) : center(c), radius(r) {
        if (!is_valid())
            throw FigureException();
    }

    Circle(CoordType x, CoordType y, SizeType r)
        : Circle(Point<CoordType>{x, y}, r) {}

    double calc_area() override {
        return PI * radius * radius;
    }

    double calc_perimetr() override {
        return 2 * PI * radius;
    }

    void name() override { 
        std::cout << "Circle" << std::endl; 
    }

    std::string getType() override { return "Circle"; }
};

#endif