#include "algorithms.h"
#include <queue>

bool BFS::connected(Node* begin, Node* end) {
    std::queue<Node*> nodes; nodes.push(begin);
    std::set<Node*> visited;
    while (!nodes.empty()) {
        Node* next = nodes.front(); nodes.pop();
        if (end == next) return true;
        visited.insert(next);
        for (node_iterator it = next->nb_begin();
            it != next->nb_end(); it++)
            if (visited.find(*it) == visited.end())
                nodes.push(*it);
    }
    return false;
}

bool DFS::connected(Node* begin, Node* end) {
    visited.clear(); return connected(begin, end, 0);
}

bool DFS::connected(Node* begin, Node* end, int depth) {
    if (begin == end) return true;
    visited.insert(begin);
    for (node_iterator it = begin->nb_begin();
        it != begin->nb_end(); it++) {
        if (visited.find(*it) == visited.end()) {
            if (connected(*it, end, depth + 1)) return true;
        }
    }
    return false;
}