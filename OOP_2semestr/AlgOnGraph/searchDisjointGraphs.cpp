#include "searchDisjointGraphs.h"
#include "algorithms.h"
#include <iostream>
#include <fstream>
#include <map>

using namespace std;

// vector<Graph*> graphs; 1 функция можно получить в динам массив
// for (перебор){
//     file<<graph; 2 функция вывод в файл
// }

vector<Graph> findDisjointGraphs(const Graph& graph) {
    set<Node*> unvisited;

    // собираем все вершины
    for (auto it = graph.begin(); it != graph.end(); ++it)
        unvisited.insert(*it);

    vector<Graph> components;

    while (!unvisited.empty()) {
        Node* start = *unvisited.begin();
        BFS bfs(graph);

        set<Node*> componentNodes;

        // находим все вершины компоненты если они соединены
        for (Node* node : unvisited) {
            if (bfs.connected(start, node)) {
                componentNodes.insert(node);
            }
        }

        // текущий граф
        Graph component;
        map<Node*, Node*> nodeMap;

        // создаём новые вершины
        for (Node* oldNode : componentNodes) {
            Node* newNode = new Node(oldNode->getName());
            component.addNode(newNode);
            nodeMap[oldNode] = newNode;
        }

        // восстанавливаем для них рёбра
        for (Node* oldNode : componentNodes) {
            for (auto it = oldNode->nb_begin(); it != oldNode->nb_end(); ++it) {
                if (componentNodes.count(*it)) {
                    component.addEdge(nodeMap[oldNode], nodeMap[*it]);
                }
            }
        }

        // удаляем уже посещённые
        for (Node* node : componentNodes)
            unvisited.erase(node);

        //  добавляем в массив графов
        components.push_back(component);
    }

    return components;
}