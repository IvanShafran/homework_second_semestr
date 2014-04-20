#include <exception>
#include <string>
#include <vector>
#include <functional>
#include <fstream>
#include <algorithm>
#include <memory>

#include "graph.h"
#include "graph_generate.h"
#include "memory_monitor.h"

void GraphMemoryTest(size_t max_number_of_vertices, size_t number_step,
    const std::function<std::unique_ptr<Graph>(size_t, size_t*)>& GetGraph, 
    std::string graph_type)
{
    std::ofstream graph_memory_test_log(".\\memory_logs\\" + graph_type + "_memory_test.log");
    
    for (size_t number_of_vertices = 0; number_of_vertices < max_number_of_vertices;
        number_of_vertices += number_step)
    {
        MemoryMonitor memory_monitor;
        {
            size_t number_of_edges;

            MemoryMonitor graph_memory_monitor;
            std::unique_ptr<Graph> graph = GetGraph(number_of_vertices, &number_of_edges);
            size_t graph_memory = graph_memory_monitor.GetDifference();

            graph_memory_test_log << "Size of used memory by " + graph_type 
                + " is " + std::to_string(graph_memory) + " bytes " 
                + "on " + std::to_string(number_of_vertices) + " vertices and " 
                + std::to_string(number_of_edges) + " edges" << std::endl;
        }

        if (memory_monitor.CheckMemoryLeaks()) 
            throw std::runtime_error("Memory leaks on " + graph_type);
    }
}

void GraphMemoryTest()
{
    srand(777);
    GraphMemoryTest(200, 20, GetFullGraph, "full_graph");
    GraphMemoryTest(1000, 100, GetEmptyGraph, "empty_graph");
    GraphMemoryTest(1000, 100, GetRandomGraph, "random_graph");
    GraphMemoryTest(1000, 100, GetFunctionalGraph, "functional_graph");
    GraphMemoryTest(1000, 100, GetAcyclicGraph, "acyclic_graph");
}
