#ifndef PRIORIYQUEUE_H
#define PRIORIYQUEUE_H

#include "node.h"
#include <vector>

struct MarkedNode {
    Node* node; int mark;
    Node* prev;
    MarkedNode(Node* anode=0, int amark=0, Node* aprev=0):
    node(anode), mark(amark), prev(aprev) {}
};

class PriorityQueue {
    std::vector<MarkedNode> nodes;
public:
    MarkedNode pop();
    void push(Node* node, int mark, Node* prev);
    bool empty() const { return nodes.empty(); }
};

#endif