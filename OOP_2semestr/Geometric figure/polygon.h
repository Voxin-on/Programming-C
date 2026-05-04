#ifndef POLYGON_H
#define POLYGON_H

#include "point.h"
#include "figure.h"
#include "geometry_utils.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>

template <typename T>
class Polygon : public Figure {
    std::vector<Point<T>> vertices;

public:
    Polygon(const std::vector<Point<T>>& points) : vertices(points) {
        if (vertices.size() < 3)
            throw FigureException();
    }

    Polygon(const char* filename) {
        std::ifstream file(filename);

        if (!file.is_open())
            throw FigureException();

        int n;
        if (!(file >> n) || n < 3)
            throw FigureException();

        vertices.resize(n);

        for (int i = 0; i < n; i++) {
            T x, y;
            if (!(file >> x >> y))
                throw FigureException();

            vertices[i] = {x, y};
        }
    }

    double calc_perimetr() override {
        double p = 0;
        int n = vertices.size();

        for (int i = 0; i < n; i++) {
            p += get_dist(vertices[i], vertices[(i + 1) % n]);
        }
        return p;
    }

    double calc_area() override {
        double area = 0;
        int n = vertices.size();

        for (int i = 0; i < n; i++) {
            area += vertices[i].x * vertices[(i + 1) % n].y;
            area -= vertices[(i + 1) % n].x * vertices[i].y;
        }

        return std::abs(area) / 2.0;
    }

    void name() override {
        std::cout << "Polygon with " << vertices.size() << " vertices\n";
    }
};

#endif