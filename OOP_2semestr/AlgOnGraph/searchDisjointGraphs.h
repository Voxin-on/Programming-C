#ifndef MY_TASKS_H
#define MY_TASKS_H

#include "graph.h"
#include <vector>
#include <string>

std::vector<Graph*> findDisjointGraphs(const Graph& graph);
void saveDisjointGraph(const Graph& g, const std::string& filename);

#endif