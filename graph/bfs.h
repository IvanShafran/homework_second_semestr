#pragma once

#include <queue>
#include <vector>

#include "graph.h"

std::vector<int> BFS(const Graph& graph, size_t vertex)
{
    std::vector<bool> used(graph.GetNumberOfVertices(), false);
    used[vertex] = true;

    std::queue<size_t> queue;
    queue.push(vertex);

    std::vector<int> distance(graph.GetNumberOfVertices(), -1);
    distance[vertex] = 0;

    while (!queue.empty()) {
        size_t current_vertex = queue.back();
        queue.pop();
        used[current_vertex] = true;

        std::vector<size_t> incidence_list = graph.GetIncidenceList(current_vertex);

        for (size_t incidence_vertex_index = 0; incidence_vertex_index < incidence_list.size();
            ++incidence_vertex_index) {
            
            size_t incidence_vertex = incidence_list[incidence_vertex_index];
            if (!used[incidence_vertex]) {
                distance[incidence_vertex] = distance[current_vertex] + 1;
                queue.push(incidence_vertex);
            }
        }        
    }

    return distance;
}
