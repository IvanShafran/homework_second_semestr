#include <vector>
#include <set>

#include "graph.h"
#include "topological_sort.h"
#include "random_functions.h"
#include "graph_has_cyclic.h"
#include "graph_generate.h"

void CheckTopologicalSort(const std::unique_ptr<Graph>& graph)
{
    bool graph_has_cyclic;
    std::vector<size_t> topological_vertex_order = TopologicalSort(graph, &graph_has_cyclic);

    if (graph_has_cyclic != DoesGraphHaveCyclic(graph))
        throw std::runtime_error("Error on TopologicalSortRandomTest");

    if (graph_has_cyclic)
        return;

    std::vector<size_t> topological_vertex_index(graph->GetNumberOfVertices());
    for (size_t vertex_index = 0; vertex_index < graph->GetNumberOfVertices(); ++vertex_index)
        topological_vertex_index[topological_vertex_order[vertex_index]] = vertex_index;


    for (size_t vertex = 0; vertex < graph->GetNumberOfVertices(); ++vertex) {
        std::vector<size_t> incidence_list = graph->GetIncidenceList(vertex);
        
        for (size_t edge_index = 0; edge_index < incidence_list.size(); ++edge_index)
        if (topological_vertex_index[vertex] > 
            topological_vertex_index[incidence_list[edge_index]])
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

        CheckTopologicalSort(graph);
    }
}

void TopologicalSortUnitTest()
{
    bool graph_has_cyclic;

    std::unique_ptr<Graph> graph1 = MakeCompactGraph(1, {}, {});
    if (TopologicalSort(graph1, &graph_has_cyclic) != std::vector<size_t>({ { 0 } }))
        throw std::runtime_error("Error on TopologicalSortUnitTest");

    std::unique_ptr<Graph> graph2 = MakeCompactGraph(2, { 0, 1 }, { 1, 0 });
    TopologicalSort(graph2, &graph_has_cyclic);
    if (!graph_has_cyclic)
        throw std::runtime_error("Error on TopologicalSortUnitTest");

    std::unique_ptr<Graph> graph3 = MakeCompactGraph(5, { 0, 1, 2, 3 }, { 1, 2, 3, 4 });
    if (TopologicalSort(graph3, &graph_has_cyclic) != std::vector<size_t>({ 0, 1, 2, 3, 4 }))
        throw std::runtime_error("Error on TopologicalSortUnitTest");
}

void TopologicalSortTest()
{
    TopologicalSortUnitTest();
    TopologicalSortRandomTest();
}
