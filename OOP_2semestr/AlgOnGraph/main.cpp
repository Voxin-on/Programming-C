#include "graph.h"
#include "algorithms.h"
#include "searchDisjointGraphs.h"
#include "Dijkstra.h"
#include <iostream>
#include <fstream>

using namespace std;

bool testBFS(Graph& g, const string node1, const string node2){
    BFS test(g);

    return test.connected(g.findNodeByName(node1), g.findNodeByName(node2));
}

bool testDFS (Graph& g, const string node1, const string node2){
    DFS test(g);

    return test.connected(g.findNodeByName(node1), g.findNodeByName(node2));
}

void testDijkstra(Graph& g, const string& startName, const string& endName) {
    Node* start = g.findNodeByName(startName);
    Node* finish = g.findNodeByName(endName);

    if (!start || !finish) {
        cout << "Nodes not found!" << endl;
        return;
    }

    Dijkstra solver(g);
    Way path = solver.shortestWay(start, finish);

    if (path.length == -1) {
        cout << "No path exists between " << startName << " and " << endName << endl;
    } else {
        cout << "Shortest distance from " << startName << " to " << endName << " is: " << path.length << endl;
        cout << "Route: ";
        
        int pathSize = path.nodes.size();
        for (int i = pathSize - 1; i >= 0; i--) {
            cout << path.nodes[i]->getName();
            if (i > 0) {
                cout << " -> ";
            }
        }
        cout << endl;
    }
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
 
    cout<< g;

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

    Graph g3("testgraph.txt");
    vector<Graph> graphs3 = findDisjointGraphs(g3);

    for (int i = 0; i < graphs3.size(); i++) {
        ofstream file("results/4.task_" + to_string(i) + ".txt");
        file << graphs3[i];
    }

    Graph g4("1000.csv");
    vector<Graph> graphs4 = findDisjointGraphs(g4);

    for (int i = 0; i < graphs4.size(); i++) {
        ofstream file("results/5.task_" + to_string(i) + ".txt");
        file << graphs4[i];
    }

    // (Задание Дейкстры)
    
    Graph g_dijk;

    Node* n1 = new Node("1");
    Node* n2 = new Node("2");
    Node* n3 = new Node("3");
    Node* n4 = new Node("4");
    Node* n5 = new Node("5");
    Node* n6 = new Node("6");
    Node* n7 = new Node("7");
    Node* n8 = new Node("8");
    Node* n9 = new Node("9");

    g_dijk.addNode(n1); g_dijk.addNode(n2); g_dijk.addNode(n3);
    g_dijk.addNode(n4); g_dijk.addNode(n5); g_dijk.addNode(n6);
    g_dijk.addNode(n7); g_dijk.addNode(n8); g_dijk.addNode(n9);

    g_dijk.addDirectedEdge(n1, n2, 10);
    g_dijk.addDirectedEdge(n1, n4, 8);
    g_dijk.addDirectedEdge(n1, n3, 6);

    g_dijk.addDirectedEdge(n2, n7, 11);
    g_dijk.addDirectedEdge(n2, n4, 5);
    g_dijk.addDirectedEdge(n2, n5, 13);

    g_dijk.addDirectedEdge(n3, n5, 3);

    g_dijk.addDirectedEdge(n4, n3, 2);
    g_dijk.addDirectedEdge(n4, n7, 12);
    g_dijk.addDirectedEdge(n4, n5, 5);
    g_dijk.addDirectedEdge(n4, n6, 7);

    g_dijk.addDirectedEdge(n5, n6, 9);
    g_dijk.addDirectedEdge(n5, n9, 12);

    g_dijk.addDirectedEdge(n7, n6, 4);
    g_dijk.addDirectedEdge(n7, n8, 6);
    g_dijk.addDirectedEdge(n7, n9, 16);

    g_dijk.addDirectedEdge(n6, n8, 8);
    g_dijk.addDirectedEdge(n6, n9, 10);

    g_dijk.addDirectedEdge(n8, n9, 15);

    // тест дейкстры

    // testDijkstra(g_dijk, "2", "5"); //must be 10
    // testDijkstra(g_dijk, "5", "2"); // rout doesn't exist


    // Найдите оптимальный путь из 1-ой вершины в 9-ю.
    testDijkstra(g_dijk, "1", "9");

    return 0;
}