#include "identify.h"
#include "triangle.h"
#include "polygon.h"
#include "rectangle.h"
#include "circle.h"
#include "geometry_utils.h"
#include <queue>
#include <cmath>
#include <iostream>

using namespace std;

void findFigure( int i, int j, int label, 
    int grid[200][200], int labels[200][200], 
    vector<vector<Point<int>>>& components){
    int dr[] = {-1, -1, -1, 0, 0, 1, 1, 1};
    int dc[] = {-1, 0, 1, -1, 1, -1, 0, 1};

    vector<Point<int>> comp;
    queue<Point<int>> q;    
    q.push({i, j}); // заносим в очередь текущую точку    
    labels[i][j] = label; // помечаем 
    while (!q.empty()) { // пока очередь не опустела
        Point<int> curr = q.front();         
        q.pop(); // удаляем точку
        comp.push_back({curr.x, curr.y}); // собираем фигуры из точек         
        for (int d = 0; d < 8; d++) { // ходим по всем направлениям
            int nr = curr.x + dr[d];        
            int nc = curr.y + dc[d];
                        
            if (nr >= 0 && nr < 200 && nc >= 0 && nc < 200 &&
                grid[nr][nc] == 1 && labels[nr][nc] == 0) {  // если нашли 1 и она не помечена
                    labels[nr][nc] = label; // помекчаем
                    q.push({nr, nc}); // заносим в очередь 
            }
        }
    }
    components.push_back(comp);
}

Figure* identifyFigure(const vector<Point<int>>& comp) {
    int minX = 1e9, maxX = -1e9, minY = 1e9, maxY = -1e9;
    double sumX = 0, sumY = 0;
    for (Point<int> p : comp) {
        if (p.x < minX) minX = p.x; if (p.x > maxX) maxX = p.x;
        if (p.y < minY) minY = p.y; if (p.y > maxY) maxY = p.y;
        sumX += p.x; sumY += p.y;
    }

    // Rectangle
    Point<double> p1{(double)minX, (double)minY}, p2{(double)maxX, (double)minY}, 
                  p3{(double)maxX, (double)maxY}, p4{(double)minX, (double)maxY};
    double realArea = comp.size();

    try {
        Rectangle<double> r(p1, p2, p3, p4);
        if (realArea / r.calc_area() > 0.90) 
            return new Rectangle<double>(p1, p2, p3, p4);
    } catch (FigureException& e) { }

    // Circle
    Point<double> center = {sumX / comp.size(), sumY / comp.size()};
    double radius = (maxX - minX + 1) / 2.0;
    try {
        Circle<double, double> c(center, radius);
        double fill = realArea / c.calc_area();
        if (fill > 0.8 && fill < 1.05) 
            return new Circle<double, double>(center, radius);
    } catch (FigureException& e) { }

    // Triangle
    // поиск 2 самых отдалённых точек
    double maxDist = 0;
    Point<int> p5 = comp[0], p6 = comp[0];
    for (const Point<int>& a : comp) {
        for (const Point<int>& b : comp) {
            double d = get_dist(a, b);
            if (d > maxDist) { 
                maxDist = d; 
                p5 = a; 
                p6 = b; 
            }
        }
    }

    double bestArea = 0;
    Point<int> p7 = comp[0];
    // Sтреуг=1/2 * h * основание(между p5 и p6)
    for (const Point<int>& p : comp) {
        double area = std::abs(cross_product(p5, p6, p)); // основание*h получается Sтреуг/2
        if (area > bestArea) { bestArea = area; p7 = p; }
    }

    try {
        Triangle<int> t(p5, p6, p7);
        double fill = realArea / t.calc_area();
        if (fill > 0.85 && fill < 1.5) 
            return new Triangle<int>(p5, p6, p7);
    } catch (FigureException& e) { }

    return nullptr;
}