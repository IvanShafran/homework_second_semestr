#include <exception>
#include <string>
#include <vector>
#include <functional>
#include <fstream>
#include <Windows.h>
#include <algorithm>
#include <memory>

#include "graph.h"
#include "dfs.h"
#include "graph_generate.h"

void GraphTimeTest(size_t max_number_of_vertices, size_t number_step,
    const std::function<std::unique_ptr<Graph>(size_t, size_t*)>& GetGraph,
    std::string graph_type)
{
    std::ofstream graph_time_test_log(".\\time_logs\\" + graph_type + "_time_test.log");

    for (size_t number_of_vertices = 0; number_of_vertices < max_number_of_vertices; 
        number_of_vertices += number_step)
    {
        size_t number_of_edges;

        std::unique_ptr<Graph> graph = GetGraph(number_of_vertices, &number_of_edges);

        int time_before_DFS = GetTickCount();
        DFS(graph);
        int time_after_DFS = GetTickCount();

        graph_time_test_log << "Time used by DFS on " + graph_type
            + " with " + std::to_string(number_of_vertices) 
            + " vertices and "
            + std::to_string(number_of_edges) + " edges is " 
            + std::to_string(time_after_DFS - time_before_DFS) + "ms"
            << std::endl;
    }
}

void GraphTimeTest()
{
    srand(777);
    GraphTimeTest(5001, 500, GetFullGraph, "full_graph");
    GraphTimeTest(5001, 500, GetEmptyGraph, "empty_graph");
    GraphTimeTest(5001, 500, GetRandomGraph, "random_graph");
    GraphTimeTest(5001, 500, GetFunctionalGraph, "functional_graph");
    GraphTimeTest(5001, 500, GetAcyclicGraph, "acyclic_graph");
}
