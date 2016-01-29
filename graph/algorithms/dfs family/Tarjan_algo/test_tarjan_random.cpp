#include <memory>
#include <vector>
#include <string>

#include "graph.h"
#include "Tarjan's_strongly_connected_components_algorithm.h"
#include "graph_generate.h"
#include "check_strong_connected_component.h"

void TestTarjanRandom(const Graph& graph)
{
    std::vector<std::vector<size_t> > component = 
        GetStronglyConnectedComponents(graph);
    CheckStronglyConnectedComponents(graph, component, "random Tarjan test");
}

void TestTarjanRandom()
{
    size_t number_of_test = 1000;
    size_t number_of_vertices = 50;
    srand(777);
    for (size_t test = 0; test < number_of_test; ++test)
    {
        size_t unnecessary_number_of_edges;
        std::unique_ptr<Graph> graph = GetRandomGraph(number_of_vertices,
            &unnecessary_number_of_edges);
        TestTarjanRandom(*graph);
    }
}
