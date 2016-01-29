#include <vector>
#include <set>
#include <string>

#include "graph.h"
#include "topological_sort.h"
#include "random_functions.h"
#include "graph_has_cycle.h"
#include "graph_generate.h"

void CheckVertexInTopologicalOrder(const std::vector<size_t>& vertex_in_topological_order)
{
    for (size_t i = 0; i < vertex_in_topological_order.size(); ++i)
    if (vertex_in_topological_order[i] != 1)
        throw std::runtime_error("Error on TopologicalSortRandomTest");
}

void CheckTopologicalSort(const Graph& graph)
{
    std::vector<size_t> topological_vertex_order;
    try {
        topological_vertex_order = TopologicalSort(graph);
    }
    catch (const std::exception& ex)
    {
        std::string message = ex.what();
        if (message == "Error on TopologicalSort: Graph has cycle" &&
            !DoesGraphHaveCycle(graph))
            throw std::runtime_error("Error on TopologicalSortRandomTest");

        return;
    }

    std::vector<size_t> topological_vertex_index(graph.GetNumberOfVertices());
    std::vector<size_t> vertex_in_topological_order(graph.GetNumberOfVertices(), 0);
    for (size_t vertex_index = 0; vertex_index < graph.GetNumberOfVertices(); ++vertex_index) {
        topological_vertex_index.at(topological_vertex_order[vertex_index]) = vertex_index;
        ++vertex_in_topological_order.at(topological_vertex_order[vertex_index]);
    }

    CheckVertexInTopologicalOrder(vertex_in_topological_order);

    for (size_t vertex = 0; vertex < graph.GetNumberOfVertices(); ++vertex) {
        std::vector<size_t> incidence_list = graph.GetIncidenceList(vertex);
        
        for (size_t edge_index = 0; edge_index < incidence_list.size(); ++edge_index)
        if (topological_vertex_index[vertex] > 
            topological_vertex_index.at(incidence_list[edge_index]))
            throw std::runtime_error("Error on TopologicalSortRandomTest");
    }
}

void TopologicalSortRandomTest()
{
    srand(777);
    for (size_t test = 0; test < 150; ++test)
    {
        size_t unnecessary_number_of_edges;

        std::unique_ptr<Graph> graph;

        switch (test % 5) {
        case 0: graph = GetEmptyGraph(100, &unnecessary_number_of_edges);
            break;
        case 1: graph = GetFullGraph(50, &unnecessary_number_of_edges);
            break;
        case 2: graph = GetAcyclicGraph(200, &unnecessary_number_of_edges);
            break;
        case 3: graph = GetFunctionalGraph(200, &unnecessary_number_of_edges);
            break;
        case 4: graph = GetRandomGraph(200, &unnecessary_number_of_edges);
            break;
        }

        CheckTopologicalSort(*graph);
    }
}

void TopologicalSortTest()
{
    TopologicalSortRandomTest();
}
