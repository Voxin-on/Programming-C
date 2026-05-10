#include "node.h"

void Node::addNeighbour(Node* neighbour, int weight) {
    neighbours.insert(neighbour);
    weights[neighbour] = weight;
}

void Node::removeNeighbour(Node* neighbour) {
    neighbours.erase(neighbour);
    weights.erase(neighbour);
}

int Node::getWeight(Node* neighbour) const {
    std::map<Node*, int>::const_iterator it = weights.find(neighbour);

    if (it == weights.end())
        return 1;

    return it->second;
}