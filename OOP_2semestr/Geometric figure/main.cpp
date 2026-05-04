#include "point.h"
#include "figure.h"
#include "triangle.h"
#include "polygon.h"
#include "rectangle.h"
#include "circle.h"
#include "ellipse.h"
#include <iostream>

#include <vector>

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

    vector<Point<int>> pts = {{0,0}, {10,0}, {0,10}};
    Polygon<int> p(pts);
    p.name();
    cout<<p.calc_area() << endl;
    cout<<p.calc_perimetr() << endl;


    cout<<"Test with base class"<<endl;
    vector<Figure *> figures;

    figures.push_back(new Triangle<int>(3, 4, 5));
    figures.push_back(new Rectangle<int>(3, 4));
    figures.push_back(new Circle<int>({0,0}, 1));
    figures.push_back(new Ellipse<int>({0,0}, 1, 1));
    figures.push_back(new Polygon<int>(pts));

    for (Figure* fig : figures){ 
        fig->name();
        cout << "Area: " << fig->calc_area() << endl;
        cout << "Perimeter: " << fig->calc_perimetr() << endl << endl;
    }

    // Посчитайте площадь участка определенного в granitsy-uchastka2.txt.

    Polygon<int> pol("granitsy-uchastka2.txt");
    cout << "Polygon area in file: " << pol.calc_area() << endl;

    return 0;
}