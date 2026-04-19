#ifndef GRAPH_H
#define GRAPH_H

#include "node.h"
#include <set>
#include <string>

class Graph {
    std::set<Node*> nodes;
public:
    Graph () {};
    Graph(const char* file_name);
    void addNode(Node* node);
    void removeNode(Node* node);
    void addEdge(Node* begin, Node* end);
    void removeEdge(Node* begin, Node* end);
    node_iterator begin() const { return nodes.begin(); }
    node_iterator end() const { return nodes.end(); }
};

#endif