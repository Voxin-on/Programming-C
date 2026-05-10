#ifndef GEOMETRY_UTILS_H
#define GEOMETRY_UTILS_H

#include "point.h"
#include <cmath>
#include <vector>
using namespace std;

const double PI = std::acos(-1.0);
const double EPS = 1e-9;

template <typename T>
double dot(Point<T> a, Point<T> b) {
    return a.x * b.x + a.y * b.y;
}

template <typename T>
double cross_product(Point<T> a, Point<T> b, Point<T> c) {
    return (double)(b.x - a.x) * (c.y - a.y) - (double)(b.y - a.y) * (c.x - a.x);
}

template <typename T1, typename T2>
double get_dist(const Point<T1>& p1, const Point<T2>& p2) {
    return std::sqrt(
        ((double)p1.x - p2.x) * ((double)p1.x - p2.x) +
        ((double)p1.y - p2.y) * ((double)p1.y - p2.y)
    );
}

#endif