#include "point.h"
#include "figure.h"
#include "triangle.h"
#include "polygon.h"
#include "rectangle.h"
#include "circle.h"
#include "ellipse.h"
#include "identify.h"
#include <iostream>

#include <vector>

using namespace std;

int main () {
    vector<Point<int>> pts = {{0,0}, {10,0}, {0,10}};
    cout<<endl<<"Test"<<endl;
    vector<Figure*> figures;

    figures.push_back(new Triangle<int>(3, 4, 5));
    figures.push_back(new Rectangle<int>(3, 4));
    figures.push_back(new Circle<int, int>({0,0}, 1));
    figures.push_back(new Ellipse<int, int>({0,0}, 1, 1));
    figures.push_back(new Polygon<int>(pts));

    for (Figure* fig : figures){ 
        fig->name();
        cout << "Area: " << fig->calc_area() << endl;
        cout << "Perimeter: " << fig->calc_perimetr() << endl << endl;
    }

    // поиск фигур
    ifstream file("Demo-task/input1.dat");
    if (!file.is_open()) return 1;

    int grid[200][200];
    char ch;
    for (int i = 0; i < 200; i++) {
        for (int j = 0; j < 200; j++) {
            file >> ch;
            grid[i][j] = ch - '0';
        }
    }

    int labels[200][200] = {};
    int label = 0;
    vector<vector<Point<int>>> components;

    for (int i = 0; i < 200; i++) {
        for (int j = 0; j < 200; j++) {
            if (grid[i][j] == 1 && labels[i][j] == 0) {
                findFigure(i, j, ++label, grid, labels, components);
            }
        }
    }
    int countNoise = 0;
    vector<Figure*> figuresSearched;
    for (vector<Point<int>>& comp : components) {
        if (comp.size() < 10) continue;

        Figure* fig = identifyFigure(comp);
        if (fig != nullptr)
            figuresSearched.push_back(fig);
        else
            countNoise++;
    }

    int countRect = 0, countCircle = 0, countTri = 0;
    for (Figure* fig : figuresSearched) {
        string type = fig->getType();

        if (type == "Rectangle") 
            countRect++;
        else if (type == "Circle") 
            countCircle++;
        else if (type == "Triangle")
            countTri++;
    }

    ofstream outFile("result.txt");
    outFile << "Rectangle = " << countRect << endl;
    outFile << "Circle = " << countCircle << endl;
    outFile << "Triangle = " << countTri << endl;
    outFile << "Noise = " << countNoise << endl;

    // Посчитайте общую площадь занимаемую Прямоугольниками, Треугольниками и окружностями
    double allArea = 0;
    for (Figure* fig : figuresSearched){ 
        allArea+= fig->calc_area();
    }
    cout <<"All area: "<< allArea << endl;

    // Посчитайте площадь участка определенного в granitsy-uchastka2.txt.

    Polygon<int> pol("granitsy-uchastka2.txt");
    cout << "Polygon area in file: " << pol.calc_area() << endl;

    for (Figure* fig : figuresSearched) delete fig;

    return 0;
}