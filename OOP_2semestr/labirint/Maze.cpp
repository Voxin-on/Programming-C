#include "Maze.h"

int Maze::getWidth() const {
    return width;
}

int Maze::getHeight() const {
    return height;
}

Cell Maze::getStartCell() const{
    return startCell;
}

Cell Maze::getEndCell() const{
    return endCell;
}



int Maze::getCell(int x, int y) const{
    if (x >= 0 && x < width && y >= 0 && y < height) {
        return grid[y][x];
    }
    return WALL;
}
int Maze::getCell(const Cell& cell) const{
    return getCell(cell.x, cell.y);
}



bool Maze::isWalkable(int x, int y) const {
    int type = getCell(x, y);
    return type != WALL;
}
bool Maze::isWalkable(const Cell& cell) const {
    return isWalkable(cell.x, cell.y);
}



void Maze::setCell(int x, int y, int type) {
    if (x >= 0 && x < width && y >= 0 && y < height) {
        grid[y][x] = type;

        if (type == START) startCell = Cell(x, y);
        if (type == END) endCell = Cell(x, y);
    }
}