#include "point.h"
#include "figure.h"
#include "triangle.h"
#include "polygon.h"
#include "rectangle.h"
#include "circle.h"
#include "ellipse.h"
#include <iostream>

using namespace std;

int findFigures(){
    int countRect = 0, countCircle = 0, countTri = 0, countNoise = 0;

    

    // Посчитайте площадь участка определенного в granitsy-uchastka2.txt.

    Polygon<int> p("granitsy-uchastka2.txt");
    cout << "Polygon area in file: " << p.calc_area() << endl;

    return 0;
}