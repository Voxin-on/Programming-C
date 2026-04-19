#ifndef ELLIPSE_H
#define ELLIPSE_H

#include "point.h"
#include "figure.h"
#include <iostream>

template <typename T>
class Ellipse : public IFigure {
    Point<T> center;
    double a, b;

    bool is_valid() const {
        return a > 0 && b > 0;
    }

public:
    Ellipse(const Point<T>& c, double a, double b)
        : center(c), a(a), b(b) {
        if (!is_valid())
            throw FigureException();
    }

    Ellipse(T x, T y, double a, double b)
        : center{ x, y }, a(a), b(b) {
        if (!is_valid())
            throw FigureException();
    }

    double calc_area() override {
        return M_PI * a * b;
    }

    double calc_perimetr() override {
        return M_PI * (3*(a + b) - sqrt((3*a + b)*(a + 3*b)));
    }

    void name() override {
        std::cout << "Ellipse" << std::endl; 
    }
};

#endif