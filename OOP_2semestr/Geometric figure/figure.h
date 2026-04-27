#ifndef FIGURE_H
#define FIGURE_H

class FigureException {};

class IFigure {
public:
    virtual double calc_area() = 0;
    virtual double calc_perimetr() = 0;
    virtual void name() = 0;

    virtual ~IFigure() {};
};

#endif