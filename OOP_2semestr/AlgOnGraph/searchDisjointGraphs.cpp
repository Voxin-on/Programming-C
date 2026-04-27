#include "searchDisjointGraphs.h"
#include "algorithms.h"
#include <iostream>
#include <fstream>

using namespace std;

// vector<Graph*> graphs; 1 функция можно получить в динам массив
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

void saveDisjointGraph(const Graph& g, const string& filename) {
    ofstream file(filename + ".txt");
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