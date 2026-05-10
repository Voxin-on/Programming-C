#ifndef FIGURE_H
#define FIGURE_H
#include <string>

class FigureException {};

class Figure {
public:
    virtual double calc_area() = 0;
    virtual double calc_perimetr() = 0;
    virtual void name() = 0;
    virtual std::string getType() = 0;
};

#endif