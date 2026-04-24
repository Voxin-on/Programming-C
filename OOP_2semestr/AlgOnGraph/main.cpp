#include "graph.h"
#include "algorithms.h"
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

    DFS test(g);

    Node* nodeA = nullptr;
    Node* nodeB = nullptr;

    for (node_iterator it = g.begin(); it != g.end(); ++it) {
        if ((*it)->getName() == "A")  nodeA = *it;
        if ((*it)->getName() == "E") nodeB = *it;
    }

    if(test.connected(nodeA,nodeB)) //must be Yes
        cout<<"Yes"<<endl;
    else
        cout<<"No"<<endl;

    Node* isolated = new Node("Z");
    g.addNode(isolated);

    for (node_iterator it = g.begin(); it != g.end(); ++it)
        if ((*it)->getName() == "Z") nodeB = *it;

    if (test.connected(nodeA, isolated)) // must be No
        cout << "Yes" << endl;
    else
        cout << "No" << endl;

    
 
    return 0;
}