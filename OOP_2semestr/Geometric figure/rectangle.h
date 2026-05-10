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
        return a > EPS && b > EPS;
    }

public:
    Rectangle(T a, T b) : a(a), b(b) {
        if (!is_valid())
            throw FigureException();
    }

    Rectangle(const Point<T> p1, const Point<T> p2,
              const Point<T> p3, const Point<T> p4) {

        Point<T> v1{p2.x - p1.x, p2.y - p1.y};
        Point<T> v2{p3.x - p2.x, p3.y - p2.y};
        Point<T> v3{p4.x - p3.x, p4.y - p3.y};
        Point<T> v4{p1.x - p4.x, p1.y - p4.y};
        

        if (std::abs(dot(v1, v2)) > EPS ||
            std::abs(dot(v2, v3)) > EPS ||
            std::abs(dot(v3, v4)) > EPS) {
            throw FigureException();
        }

        a = get_dist(p1, p2);
        b = get_dist(p2, p3);

        if (!is_valid())
            throw FigureException();
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

    std::string getType() override { return "Rectangle"; }
};

#endif