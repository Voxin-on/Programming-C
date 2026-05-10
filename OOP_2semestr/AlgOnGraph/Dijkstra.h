#ifndef PRIORIYQUEUEE_H
#define PRIORIYQUEUEE_H

#include "Graph.h"
#include <vector>

struct Way {
    std::vector<Node*> nodes; // вектор указателей на узлы которые составляет путь 
    int length;
    Way() : length(-1) {}
};

class Dijkstra {
    const Graph& graph;
public:
    Dijkstra(const Graph& agraph) : graph(agraph) {}
    Way shortestWay(Node* begin, Node* end);
};

#endif 