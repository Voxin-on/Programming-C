#include "Dijkstra.h"
#include "PriorityQueue.h"
#include <map>

// переворачиваем путь от end к begin
static Way unroll(std::map<Node*, MarkedNode> visited,
Node* begin, Node* curr) {
    Way way;
    way.length = visited[curr].mark;
    while (curr != begin) {
        way.nodes.push_back(curr);
        curr = visited[curr].prev;
    }
    way.nodes.push_back(begin);
    return way;
}

Way Dijkstra::shortestWay(Node* begin, Node* end) {
    PriorityQueue nodes; // вектор вершин
    nodes.push(begin, 0, 0); // начальная точка
    std::map<Node*, MarkedNode> visited;
    while (!nodes.empty()) {
        MarkedNode next = nodes.pop(); // берём мин путь и удаляем

        // если уже есть лучший путь пропуск
        if (visited.count(next.node))
            continue;

        visited[next.node] = next; // мин путь для вершины

        if (end == next.node) // конечный узел найден
            return unroll(visited, begin, end);

        // перебираем соседей текущей вершины
        for (node_iterator it = next.node->nb_begin();
            it != next.node->nb_end(); ++it) {
            
            // считаем новый путь
            int weight = next.mark + next.node->getWeight(*it);
            
            // если новый путь хуже то не обновляем
            if (visited.count(*it) && visited[*it].mark <= weight)
                continue;

            //обновляем
            nodes.push(*it, weight, next.node);
        }
    }
    return Way();
}