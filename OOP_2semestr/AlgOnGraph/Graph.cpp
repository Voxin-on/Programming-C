#include "Graph.h"
#include <fstream>
#include <map>

Graph::Graph(const char* file_name){
    std::ifstream file(file_name);
    file.ignore(1000, '\n');
    std::string source,target;

    while(file>>source>>target){
        Node* srcNode = findNodeByName(source);
        Node* tgtNode = findNodeByName(target);

        if (!srcNode) { 
            srcNode = new Node(source); 
            addNode(srcNode); 
        }
        if (!tgtNode) { 
            tgtNode = new Node(target); 
            addNode(tgtNode); 
        }

        addEdge(srcNode, tgtNode);
    }

    file.close();
}

Graph::Graph(const Graph& other) {
    std::map<Node*, Node*> nodeMap;

    // создаём новые вершины
    for (Node* node : other.nodes) {
        Node* newNode = new Node(node->getName());
        nodes.insert(newNode);
        nodeMap[node] = newNode;
    }

    // копируем связи и веса
    for (Node* node : other.nodes) {
        for (node_iterator it = node->nb_begin(); it != node->nb_end(); it++) {
            Node* neighbor = *it;
            if (nodeMap.count(*it)) {
                int w = node->getWeight(neighbor); 
                nodeMap[node]->addNeighbour(nodeMap[neighbor], w);
            }
        }
    }
}

Graph& Graph::operator=(const Graph& other) {
    if (this == &other) return *this;

    // сначала удаляем старое
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
        for (node_iterator it = node->nb_begin(); it != node->nb_end(); it++) {
            Node* neighbor = *it;
            if (nodeMap.count(*it)) {
                int w = node->getWeight(neighbor); 
                nodeMap[node]->addNeighbour(nodeMap[neighbor], w);
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
    for (node_iterator it = nodes.begin();
    it != nodes.end(); it++) {
        (*it)->removeNeighbour(node);
    }

    nodes.erase(node);
    delete node;
}

void Graph::addDirectedEdge(Node* begin, Node* end, int weight) {
    if (nodes.find(begin) == nodes.end() || nodes.find(end) == nodes.end())
        return;

    begin->addNeighbour(end, weight);
}

void Graph::addEdge(Node* begin, Node* end, int weight) {
    addDirectedEdge(begin, end, weight);
    addDirectedEdge(end, begin, weight);
}

void Graph::removeDirectedEdge(Node* begin, Node* end) {
    if (nodes.find(begin) == nodes.end() || nodes.find(end) == nodes.end()) {
        return;
    }
    begin->removeNeighbour(end);
}

void Graph::removeEdge(Node* begin, Node* end) {
    removeDirectedEdge(begin, end);
    removeDirectedEdge(end, begin);
}

Node* Graph::findNodeByName(const std::string& name) {
    for (node_iterator it = nodes.begin(); it != nodes.end(); it++) {
        if ((*it)->getName() == name) {
            return *it;
        }
    }
    return nullptr;
}

std::ostream& operator<<(std::ostream& os, const Graph& g) {
    os << "Source\tTarget\n";

    for (node_iterator it = g.begin(); it != g.end(); it++) {
        Node* node = *it;
        
        for (node_iterator nb = node->nb_begin(); nb != node->nb_end(); nb++) {
            os << node->getName() << "\t" 
               << (*nb)->getName() << "\n";
        }
    }

    return os;
}