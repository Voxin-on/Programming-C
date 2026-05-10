#include "PriorityQueue.h"

MarkedNode PriorityQueue::pop() {
    MarkedNode mn = nodes.back(); // берём последнюю т.к. самая маленькая
    nodes.pop_back();
    return mn;
}
void PriorityQueue::push(Node* node, int mark, Node* prev) {
    std::vector<MarkedNode>::iterator it = nodes.begin(); // начало вектора
    MarkedNode mn(node, mark, prev);
    // From higher to lower
    while (it != nodes.end() && mark < it->mark) it++; 
    if (it == nodes.end()) nodes.push_back(mn);  // кладём в конец
    else nodes.insert(it, mn); // вставляем до куда дошёл цикл
}