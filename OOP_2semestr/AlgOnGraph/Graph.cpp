#include "graph.h"
#include <fstream>
#include <map>

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

Graph::Graph(const Graph& other) {
    std::map<Node*, Node*> nodeMap;

    // копируем вершины
    for (Node* node : other.nodes) {
        Node* newNode = new Node(node->getName());
        nodes.insert(newNode);
        nodeMap[node] = newNode;
    }

    // копируем рёбра
    for (Node* node : other.nodes) {
        for (auto it = node->nb_begin(); it != node->nb_end(); ++it) {
            if (nodeMap.count(*it)) {
                nodeMap[node]->addNeighbour(nodeMap[*it]);
            }
        }
    }
}

Graph& Graph::operator=(const Graph& other) {
    if (this == &other) return *this;

    // очистка
    for (Node* node : nodes)
        delete node;
    nodes.clear();

    std::map<Node*, Node*> nodeMap;

    for (Node* node : other.nodes) {
        Node* newNode = new Node(node->getName());
        nodes.insert(newNode);
        nodeMap[node] = newNode;
    }

    for (Node* node : other.nodes) {
        for (auto it = node->nb_begin(); it != node->nb_end(); ++it) {
            if (nodeMap.count(*it)) {
                nodeMap[node]->addNeighbour(nodeMap[*it]);
            }
        }
    }

    return *this;
}

Graph::~Graph() {
    for (Node* node : nodes)
        delete node;
}

void Graph::addNode(Node* node) {
    nodes.insert(node);
}

void Graph::removeNode(Node* node) {
    for (Node* n : nodes) {
        n->removeNeighbour(node);
    }
    nodes.erase(node);
    delete node;
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

std::ostream& operator<<(std::ostream& os, const Graph& g) {
    os << "Source\tTarget\n";

    for (node_iterator it = g.begin(); it != g.end(); ++it) {
        Node* node = *it;
        for (node_iterator nb = node->nb_begin(); nb != node->nb_end(); ++nb) {
            if (node->getName() < (*nb)->getName()) {
                os << node->getName() << "\t" << (*nb)->getName() << "\n";
            }
        }
    }

    return os;
}