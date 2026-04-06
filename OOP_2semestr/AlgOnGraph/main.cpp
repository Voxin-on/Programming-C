#include "graph.h"
#include <iostream>
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
 
int main() {
    Node* a = new Node("A");
    Node* b = new Node("B");
    Node* c = new Node("C");
    Node* d = new Node("D");
    Node* e = new Node("E");
 
    Graph g;

    g.addNode(a);
    g.addNode(b);
    g.addNode(c);
    g.addNode(d);
    g.addNode(e);
 
    g.addEdge(a, b);
    g.addEdge(b, c);
    g.addEdge(c, d);
    g.addEdge(d, e);
 
    printGraph(g);
 
    return 0;
}