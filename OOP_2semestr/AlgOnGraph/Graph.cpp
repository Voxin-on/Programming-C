#include "graph.h"
#include <fstream>

Graph::Graph(const char* file_name){
    std::ifstream file(file_name);
    file.ignore(1000, '\n');
    int source,target;

    while(file>>source>>target){
        Node* srcNode = nullptr;
        Node* tgtNode = nullptr;

        for (node_iterator it = nodes.begin(); it != nodes.end(); ++it) {
            if ((*it)->getName() == std::to_string(source)) 
                srcNode = *it;
            if ((*it)->getName() == std::to_string(target)) 
                tgtNode = *it;
        }

        if (!srcNode) { 
            srcNode = new Node(std::to_string(source)); 
            addNode(srcNode); 
        }
        if (!tgtNode) { 
            tgtNode = new Node(std::to_string(target)); 
            addNode(tgtNode); 
        }

        addEdge(srcNode, tgtNode);
    }

    file.close();
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