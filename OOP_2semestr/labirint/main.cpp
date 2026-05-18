#define STB_IMAGE_IMPLEMENTATION    
#include "stb_image.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

#include "Maze.h"
#include "Cell.h"
#include "algLi.h"
#include <iostream>
using namespace std;

int main() {
    int w, h, channels;
    unsigned char* pixels = stbi_load("Maze.bmp", &w, &h, &channels, 3);

    if (pixels == nullptr){
        cout << "problem with file";
        return 1;
    }

    Maze maze (w, h);

    for (int y=0; y<h; y++){
        for (int x=0; x<w; x++){
            int index = (y * w +x) * 3; // 1 пиксель занимает 3 байта RGB

            unsigned char r = pixels[index];
            unsigned char g = pixels[index + 1];
            unsigned char b = pixels[index + 2];

            if (g > 170 && r < 50 && b < 80) { // Зелёный
                maze.setCell(x, y, Maze::START);
            } 
            else if (r > 200 && g < 50 && b < 50) { // Красный
                maze.setCell(x, y, Maze::END);
            } 
            else if (r < 50 && g < 50 && b < 50) { // Чёрный
                maze.setCell(x, y, Maze::WALL);
            } 
            else {
                maze.setCell(x, y, Maze::EMPTY);
            }
        }
    }

    algLi solve(maze);
    
    Path path = solve.shortestPath();

    if (path.length != -1) { // рисуем линию пути
        for (int i = 1; i < path.length; i++) {
            Cell c = path.cells[i];
            int index = (c.y * w + c.x) * 3;

            pixels[index] = 0;
            pixels[index + 1] = 0;
            pixels[index + 2] = 255;

            stbi_write_bmp("resolved_maze.bmp", w, h, 3, pixels); // записали в файл
        }
    }
    else{
        cout << "Path doesnt't exist" << endl;
    }

    stbi_image_free(pixels);

    return 0;
}