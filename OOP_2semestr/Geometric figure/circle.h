#ifndef CIRCLE_H
#define CIRCLE_H

#include "point.h"
#include "figure.h"
#include <iostream>
#include <cmath>

template <typename T>
class Circle : public Figure {
    Point<T> center;
    double radius;

    bool is_valid() const {
        return radius > 0;
    }

public:
    Circle(const Point<T>& c, double r) : center(c), radius(r) {
        if (!is_valid())
            throw FigureException();
    }

    Circle(T x, T y, double r)
        : Circle(Point<T>{x, y}, r) {}

    double calc_area() override {
        return M_PI * radius * radius;
    }

    double calc_perimetr() override {
        return 2 * M_PI * radius;
    }

    void name() override { 
        std::cout << "Circle" << std::endl; 
    }
};

#endif