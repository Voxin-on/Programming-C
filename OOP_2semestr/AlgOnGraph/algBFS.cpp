#include "graph.h"
#include "algorithms.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

void printGraph(const Graph& g) {
    for (node_iterator it = g.begin(); it != g.end(); it++) {
        Node* node = *it;
        cout << node->getName() << " -> ";
        for (node_iterator nb = node->nb_begin(); nb != node->nb_end(); nb++)
            cout << (*nb)->getName() << " ";
        cout << endl;
    }
}

void findSubgraphs(const Graph& graph) {
    set<Node*> unvisited;
    for (node_iterator it = graph.begin(); it != graph.end(); ++it)
        unvisited.insert(*it);

    int componentIndex = 0;

    while (!unvisited.empty()) {
        Node* start = *unvisited.begin();

        BFS bfs(graph);
        set<Node*> component;
        component.insert(start);
        
        for (Node* node : unvisited)
            if (bfs.connected(start, node))
                component.insert(node);

        for (Node* node : component)
            unvisited.erase(node);

        ofstream file("Subgraph_" + to_string(componentIndex++) + ".txt");
        file << "Source\tTarget" << endl;

        for (Node* node : component) {
            for (node_iterator it = node->nb_begin(); it != node->nb_end(); ++it) {
                if (node->getName() < (*it)->getName())
                    file << node->getName() << "\t" << (*it)->getName() << endl;
            }
        }
        file.close();
    }

    cout << "Founded subgraphs: " << componentIndex << endl;
}

int main(){
    Graph g("testgraph.txt");

    printGraph(g);

    cout<<"3.Test BFS: "<<endl;
    BFS test(g);

    Node* nodeA = nullptr;
    Node* nodeB = nullptr;

    for (node_iterator it = g.begin(); it != g.end(); ++it) {
        if ((*it)->getName() == "0")  nodeA = *it;
        if ((*it)->getName() == "38") nodeB = *it;
    }

    if(test.connected(nodeA,nodeB)) //must be Yes
        cout<<"Yes"<<endl;
    else
        cout<<"No"<<endl;

    for (node_iterator it = g.begin(); it != g.end(); ++it)
        if ((*it)->getName() == "29") nodeB = *it;

    if(test.connected(nodeA,nodeB)) //must be No
        cout<<"Yes"<<endl;
    else
        cout<<"No"<<endl;

    findSubgraphs(g);

    Graph g2("1000.csv");

    findSubgraphs(g2);

    return 0;
}