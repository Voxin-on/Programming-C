#include "graph.h"
#include <iostream>
#include <queue>

void Node::addNeighbour(Node* neighbour) {
    neighbours.insert(neighbour);
}

void Node::removeNeighbour(Node* neighbour) {
    neighbours.erase(neighbour);
}

void Graph::addNode(Node* node) {
    nodes.insert(node);
}

void Graph::removeNode(Node* node) {
    nodes.erase(node);
    // Remove also from all neighbours list
    for (std::set<Node*>::iterator it = nodes.begin();
    it != nodes.end(); it++) {
        (*it)->removeNeighbour(node);
    }
}

void Graph::addEdge(Node* begin, Node* end) {
    if (nodes.find(begin) == nodes.end())
        return;
    if (nodes.find(end) == nodes.end())
        return;
    begin->addNeighbour(end);
    end->addNeighbour(begin);
}

void Graph::removeEdge(Node* begin, Node* end) {
    if (nodes.find(begin) == nodes.end()) 
        return;
    if (nodes.find(end) == nodes.end()) 
        return;
    begin->removeNeighbour(end);
    end->removeNeighbour(begin);
}


bool BFS::connected(Node* begin, Node* end) {
    std::queue<Node*> nodes; nodes.push(begin);
    std::set<Node*> visited;
    while (!nodes.empty()) {
        Node* next = nodes.front(); nodes.pop();
        if (end == next) return true;
        visited.insert(next);
        for (node_iterator it = next->nb_begin();
            it != next->nb_end(); it++)
            if (visited.find(*it) == visited.end())
                nodes.push(*it);
    }
    return false;
}

bool DFS::connected(Node* begin, Node* end) {
    visited.clear(); return connected(begin, end, 0);
}
    bool DFS::connected(Node* begin, Node* end, int depth) {
    if (begin == end) return true;
    visited.insert(begin);
    for (node_iterator it = begin->nb_begin();
        it != begin->nb_end(); it++) {
        if (visited.find(*it) == visited.end()) {
            if (connected(*it, end, depth + 1)) return true;
        }
    }
    return false;
}