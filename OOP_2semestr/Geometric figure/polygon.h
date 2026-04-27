#ifndef POLYGON_H
#define POLYGON_H

#include "point.h"
#include "figure.h"
#include "geometry_utils.h"
#include <iostream>
#include <fstream>
#include <string>

template <typename T>
class Polygon : public IFigure {
    Point<T>* vertices;
    int n;
public:
    Polygon(Point<T>* points, int count) : n(count) {
        vertices = new Point<T>[n];
        for (int i = 0; i < n; i++) {
            vertices[i] = points[i];
        }
    }

    Polygon(const  char* filename) {
        std::ifstream file(filename);

        if (!file.is_open())
            throw FigureException();

        if (!(file >> n) || n < 3) 
            throw FigureException();

        vertices = new Point<T>[n];
        for (int i = 0; i < n; i++) {
            T x, y;
            if (!(file >> x >> y)) {
                delete[] vertices;
                throw FigureException();
            }
            vertices[i] = {x,y};
        }

        file.close();
    }

    ~Polygon() override {
        delete[] vertices;
    }

    double calc_perimetr() override {
        double p = 0;
        for (int i = 0; i < n; i++) {
            p += get_dist(vertices[i], vertices[(i + 1) % n]);
        }
        return p;
    }

    double calc_area() override {
        double area = 0;
        for (int i = 0; i < n; i++) {
            area += (vertices[i].x * vertices[(i + 1) % n].y);
            area -= (vertices[(i + 1) % n].x * vertices[i].y);
        }
        return abs(area) / 2.0;
    }

    void name() override { 
        std::cout << "Polygon with " << n << " vertices" << std::endl; 
    }
};

#endif