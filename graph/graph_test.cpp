#include <exception>
#include <string>
#include <vector>
#include <functional>
#include <fstream>
#include <Windows.h>

#include "graph.h"
#include "dfs.h"

Graph GetFullGraph(size_t number_of_vertices, size_t* number_of_edges)
{
    *number_of_edges = 0;
    std::vector<size_t> edge_begin, edge_end;

    for (size_t vertex = 0; vertex < number_of_vertices; ++vertex)
    for (size_t incidence_vertex = 0; incidence_vertex < number_of_vertices; 
        ++incidence_vertex)
    if (vertex != incidence_vertex) {
        edge_begin.push_back(vertex);
        edge_end.push_back(incidence_vertex);
        ++(*number_of_edges);
    }

    Graph graph(number_of_vertices, edge_begin, edge_end);
    return graph;
}

Graph GetEmptyGraph(size_t number_of_vertices, size_t* number_of_edges)
{
    *number_of_edges = 0;
    return Graph(number_of_vertices, {}, {});
}


#ifdef _DEBUG
void GraphMemoryTest(size_t number_of_tests, size_t number_of_vertices_step,  
    const std::function<Graph(size_t, size_t*)>& GetGraph, 
    std::string graph_type)
{
    std::ofstream graph_memory_test_log(".\\memory_logs\\" + graph_type + " memory test.log");
    
    for (size_t test = 0; test < number_of_tests; ++test)
    {
        _CrtMemState memory_state_before_test;
        _CrtMemCheckpoint(&memory_state_before_test);

        {
            size_t number_of_vertices = test * number_of_vertices_step;
            size_t number_of_edges;
            
            _CrtMemState memory_state_before_creation;
            _CrtMemCheckpoint(&memory_state_before_creation);

            Graph graph = GetGraph(number_of_vertices, &number_of_edges);

            _CrtMemState memory_state_after_creation;
            _CrtMemCheckpoint(&memory_state_after_creation);

            _CrtMemState graph_memory;
            _CrtMemDifference(&graph_memory, &memory_state_before_creation, 
                &memory_state_after_creation);

            graph_memory_test_log << "Size of used memory by " + graph_type 
                + " is " + std::to_string(graph_memory.lTotalCount) + " bytes " 
                + "on " + std::to_string(number_of_vertices) + " vertices and " 
                + std::to_string(number_of_edges) + " edges" << std::endl;

        }
        _CrtMemState memory_state_after_test;
        _CrtMemCheckpoint(&memory_state_after_test);
        _CrtMemState memore_difference;

        if (_CrtMemDifference(&memore_difference, &memory_state_before_test,
            &memory_state_after_test)) {
            throw std::runtime_error("Memory leaks on " + graph_type);
            }
    }
}
#endif

void GraphTimeTest(size_t number_of_tests, size_t number_of_vertices_step,
    const std::function<Graph(size_t, size_t*)>& GetGraph,
    std::string graph_type)
{
    std::ofstream graph_time_test_log(".\\time_logs\\" + graph_type + " time test.log");

    for (size_t test = 0; test < number_of_tests; ++test)
    {
        size_t number_of_vertices = test * number_of_vertices_step;
        size_t number_of_edges;

        Graph graph = GetGraph(number_of_vertices, &number_of_edges);

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

void GraphTest()
{
#ifdef _DEBUG
    GraphMemoryTest(100, 1, GetFullGraph, "full graph");
    GraphMemoryTest(10, 1000, GetEmptyGraph, "empty graph");
#endif
    
#ifndef _DEBUG
    GraphTimeTest(10, 1000, GetFullGraph, "full graph");
    GraphTimeTest(10, 1000, GetEmptyGraph, "empty graph");
#endif
}
