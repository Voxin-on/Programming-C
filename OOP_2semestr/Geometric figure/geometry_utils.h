#ifndef GEOMETRY_UTILS_H
#define GEOMETRY_UTILS_H

#include "point.h"
#include <cmath>
using namespace std;

template <typename T>
double dot(Point<T> a, Point<T> b) {
    return a.x * b.x + a.y * b.y;
}

template <typename T>
double get_dist(const Point<T>& p1, const Point<T>& p2) {
    return sqrt(((double)p1.x - p2.x) * ((double)p1.x - p2.x) + 
                 ((double)p1.y - p2.y) * ((double)p1.y - p2.y));
};

#endif