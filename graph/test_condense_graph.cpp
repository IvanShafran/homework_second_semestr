#include <memory>
#include <vector>

#include "graph.h"
#include "condense_graph.h"

void TestCondenseGraph()
{
    std::vector<Edge> edges = { { 0, 5 }, { 0, 3 }, { 1, 2 }, { 1, 3 }, 
        { 2, 1 }, { 2, 4 }, { 3, 4 }, { 3, 4 }, { 4, 3 }, { 4, 3 }, 
        { 5, 0 }, { 5, 4 } };
    std::vector<std::vector<size_t> > component = 
    { { 0, 5 }, { 3, 4 }, { 1, 2 } };

    std::unique_ptr<Graph> graph = MakeCompactGraph(6, edges);
    std::unique_ptr<Graph> condesed_graph =
        GetCondensedGraph(*graph, component);

    if (condesed_graph->GetNumberOfVertices() != 3)
        throw std::runtime_error("Error on TestCondenseGraph");

    if (condesed_graph->GetIncidenceList(0) != std::vector<size_t>(1, 1))
        throw std::runtime_error("Error on TestCondenseGraph");

    if (condesed_graph->GetIncidenceList(1) != std::vector<size_t>())
        throw std::runtime_error("Error on TestCondenseGraph");

    if (condesed_graph->GetIncidenceList(2) != std::vector<size_t>(1, 1))
        throw std::runtime_error("Error on TestCondenseGraph");

}
