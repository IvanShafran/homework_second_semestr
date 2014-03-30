#pragma once

#include "graph.h"

struct Edge
{
    Edge(size_t edge_begin, size_t edge_end);
};

bool operator < (const Edge& first_edge, const Edge& second_edge);

void TopologicalSortTest();

Graph GetRandomGraph(size_t max_number_of_vertices, size_t max_number_of_edges,
    size_t* number_of_vertices, size_t* number_of_edges);
