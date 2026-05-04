#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "point.h"
#include "figure.h"
#include "geometry_utils.h"
#include <iostream>

template <typename T>
class Rectangle : public Figure {
    double a, b;

    bool is_valid() const {
        return a > 0 && b > 0;
    }

public:
    Rectangle(T a, T b) : a(a), b(b) {
        if (!is_valid())
            throw FigureException();
    }

    Rectangle(Point<T> p1, Point<T> p2, Point<T> p3) {
        Point<T> v1{p1.x - p2.x, p1.y - p2.y};
        Point<T> v2{p3.x - p2.x, p3.y - p2.y};

        if (dot(v1, v2) != 0) {
            throw FigureException();
        }

        a = get_dist(p1, p2);
        b = get_dist(p2, p3);
    }

    double calc_area() override {
        return a * b;
    }

    double calc_perimetr() override {
        return 2 * (a + b);
    }

    void name() override { 
        std::cout << "Rectangle" << std::endl;
    }
};

#endif