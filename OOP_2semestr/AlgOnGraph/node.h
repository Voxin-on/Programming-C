#ifndef NODE_H
#define NODE_H

#include <set>
#include <string>
#include <map>

class Node;

typedef std::set<Node*>::const_iterator
    node_iterator;

class Node {
    std::string name;
    std::set<Node*> neighbours;

    std::map<Node*, int> weights;

    void addNeighbour(Node* neighbour, int weight = 1);
    void removeNeighbour(Node* neighbour);
public:
    Node(const std::string& aname) : name(aname) {}
    const std::string& getName() const { return name; }
    node_iterator nb_begin() const { return neighbours.begin(); }
    node_iterator nb_end() const { return neighbours.end(); }

    int getWeight(Node* neighbour) const;

    friend class Graph;
};

#endif