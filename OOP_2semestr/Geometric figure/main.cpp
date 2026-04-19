#include "point.h"
#include "figure.h"
#include "triangle.h"
#include "polygon.h"
#include "rectangle.h"
#include "circle.h"
#include "ellipse.h"
#include <iostream>

using namespace std;

int main () {
    Triangle<int> t(3, 4, 5);
    t.name();
    cout<<t.calc_area() << endl; // 6
    cout<<t.calc_perimetr() << endl;

    Rectangle<int> r(3, 4);
    r.name();
    cout<<r.calc_area() << endl;
    cout<<r.calc_perimetr() << endl;

    Circle<int> c({0,0}, 1);
    c.name();
    cout<<c.calc_area() << endl;
    cout<<c.calc_perimetr() << endl;

    Ellipse<int> e({0,0}, 1, 1);
    e.name();
    cout<<e.calc_area() << endl;
    cout<<e.calc_perimetr() << endl;

    Point<int> pts[] = {{0,0}, {10,0}, {0,10}};
    Polygon<int> p(pts, 3);
    p.name();
    cout<<p.calc_area() << endl;
    cout<<p.calc_perimetr() << endl;




    return 0;
}