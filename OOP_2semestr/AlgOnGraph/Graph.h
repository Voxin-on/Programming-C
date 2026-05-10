#ifndef GRAPH_H
#define GRAPH_H

#include "node.h"
#include <ostream>
#include <set>
#include <string>

class Graph {
    std::set<Node*> nodes;
public:
    Graph () {};
    Graph(const char* file_name);
    Graph(const Graph& other);
    Graph& operator=(const Graph& other);
    ~Graph();
    void addNode(Node* node);
    void removeNode(Node* node);
    void addDirectedEdge(Node* begin, Node* end, int weight = 1);
    void addEdge(Node* begin, Node* end, int weight = 1);
    void removeDirectedEdge(Node* begin, Node* end);
    void removeEdge(Node* begin, Node* end);
    node_iterator begin() const { return nodes.begin(); }
    node_iterator end() const { return nodes.end(); }

    Node* findNodeByName(const std::string& name);
    friend std::ostream& operator<<(std::ostream& os, const Graph& g);
};

#endif