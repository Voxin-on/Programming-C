#include "graph.h"
#include "algorithms.h"
#include "searchDisjointGraphs.h"
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

bool testBFS(const Graph& g, const string node1, const string node2){
    BFS test(g);

    Node* nodeA = nullptr; // делаем 2 пустых указателя
    Node* nodeB = nullptr;

    for (node_iterator it = g.begin(); it != g.end(); ++it) {
        if ((*it)->getName() == node1)  nodeA = *it;
        if ((*it)->getName() == node2) nodeB = *it;
    } // присваиваем указатели на вершины в одном и том же графе

    return test.connected(nodeA,nodeB);
}

bool testDFS (const Graph& g, const string node1, const string node2){
    DFS test(g);

    Node* nodeA = nullptr;
    Node* nodeB = nullptr;

    for (node_iterator it = g.begin(); it != g.end(); ++it) {
        if ((*it)->getName() == node1)  nodeA = *it;
        if ((*it)->getName() == node2) nodeB = *it;
    }

    return test.connected(nodeA,nodeB);
}

void testSearchDisjointGraphs(){
    Graph g3("testgraph.txt");
    vector<Graph*> graphs3 = findDisjointGraphs(g3);
    for (int i=0; i<graphs3.size() ;i++)
        saveDisjointGraph(*graphs3[i],"4.task_" + to_string(i));

    for (Graph* ptr : graphs3)
        delete ptr; 
    graphs3.clear();

    Graph g4("1000.csv");
    vector<Graph*> graphs4 = findDisjointGraphs(g4);
    for (int i=0; i<graphs4.size() ;i++)
        saveDisjointGraph(*graphs4[i],"5.task_" + to_string(i));

    for (Graph* ptr : graphs4) 
        delete ptr;
    graphs4.clear();
}
 
int main() {
    // test create graph
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

    cout<<"testDFS"<<endl;

    if(testDFS(g, "A", "E")) //must be Yes
        cout<<"Yes"<<endl;
    else
        cout<<"No"<<endl;

    Node* isolated = new Node("Z");
    g.addNode(isolated);

    if(testDFS(g, "A", "Z")) //must be Yes
        cout<<"Yes"<<endl;
    else
        cout<<"No"<<endl;

    cout<<"testBFS"<<endl;

    Graph g2("testgraph.txt");

    if(testBFS(g2, "0", "38")) //must be Yes
        cout<<"Yes"<<endl;
    else
        cout<<"No"<<endl;

    if(testBFS(g2, "0", "29")) //must be No
        cout<<"Yes"<<endl;
    else
        cout<<"No"<<endl;

    // 4 и 5 выделение непересекающих граф и распределние по файлам

    testSearchDisjointGraphs();


 
    return 0;
}