#include <stdexcept>
#include <vector>
#include <functional>
#include <memory>
#include <string>

#include "graph.h"
#include "memory_monitor.h"
#include "graph_generate.h"

void TestMakeCompactGraph(size_t max_number_of_vertices, size_t number_step,
    const std::function<void(size_t, size_t*,
         std::vector<size_t>*, std::vector<size_t>*)>& GenEdges,
    const std::string& graph_type)
{
    for (size_t number_of_vertices = 0; number_of_vertices < max_number_of_vertices; 
        number_of_vertices += number_step) {
        
        size_t number_of_edges;

        std::vector<size_t> edge_begin;
        std::vector<size_t> edge_end;
        GenEdges(number_of_vertices, &number_of_edges, &edge_begin, &edge_end);

        MemoryMonitor compact_graph_memory_monitor;
        std::unique_ptr<Graph> graph = MakeCompactGraph(number_of_vertices, 
            edge_begin, edge_end);
        size_t compact_graph_memory = compact_graph_memory_monitor.GetDifference();

        MemoryMonitor list_memory_monitor;
        std::unique_ptr<ListOfEdges> graph_by_list(
            new ListOfEdges(number_of_vertices, edge_begin, edge_end));
        size_t list_memory = list_memory_monitor.GetDifference();

        MemoryMonitor matrix_memory_monitor;
        std::unique_ptr<MatrixOfEdges> graph_by_matrix(
            new MatrixOfEdges(number_of_vertices, edge_begin, edge_end));
        size_t matrix_memory = matrix_memory_monitor.GetDifference();
        
        if (compact_graph_memory > 2 * list_memory || compact_graph_memory > 2 * matrix_memory)
            throw std::runtime_error("Error on TestMakeCompactGraph(" + graph_type 
            + "): graph is not compact more than twice");
    }
}

void TestMakeCompactGraph()
{
    srand(777);
    TestMakeCompactGraph(200, 20, GenFullGraphEdges, "full graph");
    TestMakeCompactGraph(100, 20, GenEmptyGraphEdges, "empty graph");
    TestMakeCompactGraph(300, 20, GenFunctionalGraphEdges, "functional graph");
    TestMakeCompactGraph(300, 20, GenAcyclicGraphEdges, "acycic graph");
    TestMakeCompactGraph(300, 20, GenRandomGraphEdges, "random graph");
}
