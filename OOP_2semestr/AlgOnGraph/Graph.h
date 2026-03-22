#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <set>
#include <string>

class Node;

typedef std::set<Node*>::const_iterator
    node_iterator;


class Node {
    std::string name;
    std::set<Node*> neighbours;
    void addNeighbour(Node* neighbour);
    void removeNeighbour(Node* neighbour);
    public:
        Node(const std::string& aname) : name(aname) {}
        const std::string& getName() const { return name; }
        node_iterator nb_begin() const { return neighbours.begin(); }
        node_iterator nb_end() const { return neighbours.end(); }
        friend class Graph;
};


class Graph {
    std::set<Node*> nodes;
    public:
        ~Graph();
        void addNode(Node* node);
        void removeNode(Node* node);
        void addEdge(Node* begin, Node* end);
        void removeEdge(Node* begin, Node* end);
        node_iterator begin() const { return nodes.begin(); }
        node_iterator end() const { return nodes.end(); }
};

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