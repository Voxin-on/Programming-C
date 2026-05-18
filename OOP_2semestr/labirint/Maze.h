#ifndef MAZE_H
#define MAZE_H

#include "Cell.h"

#include <vector>

class Maze {
private:
    int width;
    int height;
    std::vector<std::vector<int>> grid;
    Cell startCell;
    Cell endCell;
public:
    enum CellType {
        EMPTY =0,
        WALL = 1,
        START = 2,
        END = 3,
    };

    Maze(int w, int h) : width(w), height(h), grid(h, std::vector<int>(w, EMPTY)) {}

    int getWidth() const;
    int getHeight() const;
    Cell getStartCell() const;
    Cell getEndCell() const;

    int getCell(int x, int y) const;
    int getCell(const Cell& cell) const;

    bool isWalkable(int x, int y) const;
    bool isWalkable(const Cell& cell) const;

    void setCell(int x, int y, int type);
};


#endif