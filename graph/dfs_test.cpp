#include <stdexcept>
#include <vector>
#include <algorithm>
#include <set>

#include "graph.h"
#include "dfs.h"
#include "graph_generate.h"

struct DFSTestClass : public DFSVisitor {
    std::vector<colors> color_;
    std::set<Edge> edges_;

    explicit DFSTestClass(size_t number_of_vertices) : color_(number_of_vertices, WHITE)
    {}

    void BeforeProcessing(size_t vertex)
    {
        if (color_[vertex] != WHITE)
            throw std::runtime_error("Error on DFSTest: wrong color of vertex");
        color_[vertex] = GREY;
    }

    void ProcessIncidenceVertex(size_t edge_begin, size_t edge_end, colors end_color) 
    {
        edges_.insert(Edge(edge_begin, edge_end));
        if (color_[edge_begin] != GREY)
            throw std::runtime_error("Error on DFSTest: wrong color of vertex");
        if (end_color != color_[edge_end])
            throw std::runtime_error("Error on DFSTest: wrong color of vertex");
    };

    void AfterProcessing(size_t vertex)
    {
        if (color_[vertex] != GREY)
            throw std::runtime_error("Error on DFSTest: wrong color of vertex");
        color_[vertex] = BLACK;
    }
};

void CheckDFS(const Graph& graph, std::vector<Edge>* edges)
{
    DFSTestClass visitor(graph.GetNumberOfVertices());
    DFS(graph, &visitor);

    if (visitor.color_ != std::vector<colors>(graph.GetNumberOfVertices(), BLACK))
        throw std::runtime_error("Error on DFSRandomTest");

    std::set<Edge> edges_set;
    for (size_t i = 0; i < edges->size(); ++i)
        edges_set.insert(edges->at(i));

    if (!std::equal(edges_set.begin(), edges_set.end(), visitor.edges_.begin()))
        throw std::runtime_error("Error on DFSRandomTest");
}

void DFSRandomTest()
{
    srand(777);
    for (size_t test = 0; test < 150; ++test)
    {
        size_t unnecessary_number_of_edges;

        std::unique_ptr<Graph> graph;
        std::vector<Edge> edges;

        switch (test % 5) {
        case 0: 
            edges = GenEmptyGraphEdges(10, &unnecessary_number_of_edges);
            graph = MakeCompactGraph(10, edges);
            break;
        case 1: 
            edges = GenFullGraphEdges(5, &unnecessary_number_of_edges);
            graph = MakeCompactGraph(5, edges);
            break;
        case 2: 
            edges = GenAcyclicGraphEdges(20, &unnecessary_number_of_edges);
            graph = MakeCompactGraph(20, edges);
            break;
        case 3: 
            edges = GenFunctionalGraphEdges(20, &unnecessary_number_of_edges);
            graph = MakeCompactGraph(20, edges);
            break;
        case 4: 
            edges = GenRandomGraphEdges(20, &unnecessary_number_of_edges);
            graph = MakeCompactGraph(20, edges);
            break;
        }

        CheckDFS(*graph, &edges);
    }
}


void DFSTest()
{
    DFSRandomTest();
}
