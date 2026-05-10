#include "searchDisjointGraphs.h"
#include "algorithms.h"
#include <map>

using namespace std;

vector<Graph> findDisjointGraphs(const Graph& graph) {
    set<Node*> unvisited;

    // собираем все вершины
    for (Node* node : graph)
        unvisited.insert(node);

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
            for (node_iterator it = oldNode->nb_begin(); it != oldNode->nb_end(); it++) {
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