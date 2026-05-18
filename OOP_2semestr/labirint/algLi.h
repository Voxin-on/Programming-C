#ifndef ALGLI_H
#define ALGLI_H

#include "Maze.h"
#include "Cell.h"
#include <vector>

struct Path {
    std::vector<Cell> cells;
    int length;
    Path() : length(-1) {}
};

class algLi {
private:
    const Maze& maze;
    void reversePath(std::vector<Cell>& cells);
public:
    algLi(const Maze&   aMaze) : maze(aMaze) {}
    Path unroll(const std::vector<std::vector<int>>& dist, Cell start, Cell end);
    Path shortestPath();
};


#endif