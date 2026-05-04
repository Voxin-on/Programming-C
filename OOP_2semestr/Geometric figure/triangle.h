#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "point.h"
#include "figure.h"
#include "geometry_utils.h"
#include <iostream>
#include <cmath>

template <typename T>
class Triangle : public Figure {
    double a, b, c;
    bool is_valid() const {
        return (a + b > c) && (a + c > b) && (b + c > a);
    }
public:
    Triangle(T a, T b, T c) : a(a), b(b), c(c) {
        if (!is_valid())
            throw FigureException();
    }

    Triangle(Point<T> p1, Point<T> p2, Point<T> p3) {
        a = get_dist(p1, p2);
        b = get_dist(p2, p3);
        c = get_dist(p3, p1);
        if (!is_valid())
            throw FigureException();
    }

    double calc_area() override {
        double p = (a + b + c) / 2.0;
        return std::sqrt(p * (p - a) * (p - b) * (p - c));
    }

    double calc_perimetr() override {
        return a + b + c;
    }

    void name() override { 
        std::cout << "Triangle" << std::endl;
    }
};

#endif