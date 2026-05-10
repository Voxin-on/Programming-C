#ifndef IDENTIFY_H
#define IDENTIFY_H

#include <vector>
#include "point.h"
#include "figure.h"

void findFigure(int i, int j, int label, 
                int grid[200][200], int labels[200][200], 
                std::vector<std::vector<Point<int>>>& components);

Figure* identifyFigure(const std::vector<Point<int>>& comp);

#endif