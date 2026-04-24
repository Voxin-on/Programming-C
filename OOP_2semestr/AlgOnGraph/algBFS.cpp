#include "graph.h"
#include "algorithms.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

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

// vector<Graph> graphs; 1 функция можно получить в динам массив
// for (перебор){
//     file << graph; 2 функция вывод в файл
// }

vector<Graph*> findDisjointGraphs(const Graph& graph) {
    set<Node*> unvisited;
    for (node_iterator it = graph.begin(); it != graph.end(); ++it)
        unvisited.insert(*it);
    
    vector<Graph*> components;

    while (!unvisited.empty()) {
        Node* start = *unvisited.begin();
        BFS bfs(graph);
        Graph* component = new Graph; // текущий граф
        
        // находим все вершины соед с start и добавляем в граф
        for (Node* node : unvisited)
            if (bfs.connected(start, node))
                component->addNode(node);

        // соед вершины в ребра
        for (node_iterator it = component->begin(); it != component->end(); ++it)
            for (node_iterator nb = (*it)->nb_begin(); nb != (*it)->nb_end(); ++nb)
                component->addEdge(*it, *nb);

        for (node_iterator it = component->begin(); it != component->end(); ++it)
            unvisited.erase(*it); // очистка вершин если они уже в текущем графе

        components.push_back(component); // ложим граф в массив графов

    }
    return components;
}

void saveDisjointGraph(const Graph& g, int index, const string& filename) {
    ofstream file(filename + to_string(index) + ".txt");
    file << "Source\tTarget" << endl;

    for (node_iterator it = g.begin(); it != g.end(); ++it) {
        Node* node = *it;
        for (node_iterator nb = node->nb_begin(); nb != node->nb_end(); ++nb) {
            if (node->getName() < (*nb)->getName())
                file << node->getName() << "\t" << (*nb)->getName() << endl;
        }
    }

    file.close();
}

int testSearchDisjointGraphs(){
    Graph g("testgraph.txt");

    printGraph(g); // проверка вывод для графа

    cout<<"3.Test BFS: "<<endl; // проверка БСФ
    BFS test(g);

    Node* nodeA = nullptr; // делаем 2 пустых указателя
    Node* nodeB = nullptr;

    for (node_iterator it = g.begin(); it != g.end(); ++it) {
        if ((*it)->getName() == "0")  nodeA = *it;
        if ((*it)->getName() == "38") nodeB = *it;
    } // присваиваем указатели на вершины в одном и том же графе

    if(test.connected(nodeA,nodeB)) //must be Yes
        cout<<"Yes"<<endl;
    else
        cout<<"No"<<endl;

    for (node_iterator it = g.begin(); it != g.end(); ++it)
        if ((*it)->getName() == "29") nodeB = *it; // присваиваем вершину в другом графе

    if(test.connected(nodeA,nodeB)) //must be No
        cout<<"Yes"<<endl;
    else
        cout<<"No"<<endl;

    // 4 и 5 выделение непересекающих граф и распределние по файлам

    vector<Graph*> graphs = findDisjointGraphs(g);
    for (int i=0; graphs.size()!=i ;i++)
        saveDisjointGraph(*graphs[i], i, "4.task_");

    Graph g2("1000.csv");
    vector<Graph*> graphs2 = findDisjointGraphs(g2);
    for (int i=0; graphs2.size()!=i ;i++)
        saveDisjointGraph(*graphs2[i], i, "5.task_");

    return 0;
}