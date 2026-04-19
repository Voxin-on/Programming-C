#ifndef GEOMETRY_UTILS_H
#define GEOMETRY_UTILS_H

#include "point.h"
#include <cmath>

template <typename T>
double get_dist(const Point<T>& p1, const Point<T>& p2) {
    return std::sqrt(((double)p1.x - p2.x) * ((double)p1.x - p2.x) + 
                 ((double)p1.y - p2.y) * ((double)p1.y - p2.y));
};

#endif