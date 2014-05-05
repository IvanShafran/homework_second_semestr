#include <stdexcept>
#include <vector>
#include <functional>
#include <memory>
#include <string>

#include "graph.h"
#include "memory_monitor.h"
#include "graph_generate.h"

void TestMakeCompactGraph(size_t max_number_of_vertices, size_t number_step,
    const std::function<std::vector<Edge>(size_t, size_t*)>& GenEdges,
    const std::string& graph_type)
{
    for (size_t number_of_vertices = 0; number_of_vertices < max_number_of_vertices; 
        number_of_vertices += number_step) {
        
        size_t number_of_edges;

        std::vector<Edge> edges = GenEdges(number_of_vertices, &number_of_edges);

        MemoryMonitor compact_graph_memory_monitor;
        std::unique_ptr<Graph> graph = MakeCompactGraph(number_of_vertices, 
            edges);
        size_t compact_graph_memory = compact_graph_memory_monitor.GetDifference();

        MemoryMonitor list_memory_monitor;
        std::unique_ptr<ListOfEdges> graph_by_list(
            new ListOfEdges(number_of_vertices, edges));
        size_t list_memory = list_memory_monitor.GetDifference();

        MemoryMonitor matrix_memory_monitor;
        std::unique_ptr<MatrixOfEdges> graph_by_matrix(
            new MatrixOfEdges(number_of_vertices, edges));
        size_t matrix_memory = matrix_memory_monitor.GetDifference();
        
        double reliability = 1.5;//experimental constant
        if ((compact_graph_memory > reliability * list_memory || 
            compact_graph_memory > reliability * matrix_memory) &&
            (2 * compact_graph_memory - list_memory - matrix_memory) > (1 << 5))
            throw std::runtime_error("Error on TestMakeCompactGraph(" + graph_type 
            + "): graph is not compact more than " + std::to_string(reliability) + " times "
                + "and more than 2^5 bytes");
    }
}

void TestMakeCompactGraph()
{
    srand(777);
    TestMakeCompactGraph(200, 20, GenFullGraphEdges, "full graph");
    TestMakeCompactGraph(10000, 1000, GenEmptyGraphEdges, "empty graph");
    TestMakeCompactGraph(10000, 1000, GenFunctionalGraphEdges, "functional graph");
    TestMakeCompactGraph(10000, 1000, GenAcyclicGraphEdges, "acycic graph");
    TestMakeCompactGraph(10000, 1000, GenRandomGraphEdges, "random graph");
}
