#ifndef ALGORITHMS_H
#define ALGORITHMS_H

#include "graph.h"
#include <set>

class BFS {
    const Graph& graph;
public:
    BFS(const Graph& agraph) : graph(agraph) {}
    bool connected(Node* begin, Node* end);
};

class DFS {
    const Graph& graph;
    std::set<Node*> visited;
    bool connected(Node* begin, Node* end, int depth);
    public:
        DFS(const Graph& agraph) : graph(agraph) {}
        bool connected(Node* begin, Node* end);
};

#endif