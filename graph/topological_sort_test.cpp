#include <vector>
#include <set>

#include "graph.h"
#include "topological_sort.h"
#include "random_functions.h"
#include "does_graph_have_cyclic.h"

struct Edge {
    size_t begin;
    size_t end;

    Edge(size_t edge_begin, size_t edge_end) : begin(edge_begin), end(edge_end)
    {}

};

bool operator < (const Edge& first_edge, const Edge& second_edge)
{
    return (first_edge.begin < second_edge.begin ||
        (first_edge.begin == second_edge.begin
        && first_edge.end < second_edge.end));
}

Graph GetRandomGraph(size_t max_number_of_vertices, size_t max_number_of_edges, 
    size_t* number_of_vertices,
    size_t* number_of_edges)
{
    *number_of_vertices = Rand(2, max_number_of_vertices + 1);
    size_t approximate_number_of_edges = Rand(0, max_number_of_edges + 1);

    std::set<Edge> edges;

    for (size_t vertex = 0; vertex < *number_of_vertices; ++vertex) {
        edges.insert(Edge(vertex, vertex));
    }

    *number_of_edges = 0;
    std::vector<size_t> edge_begin, edge_end;
    for (size_t edge_index = 0; edge_index < approximate_number_of_edges; ++edge_index)
    {
        size_t begin = Rand(0, *number_of_vertices);
        size_t end = Rand(0, *number_of_vertices);
        if (edges.find(Edge(begin, end)) == edges.end()) {
            edge_begin.push_back(begin);
            edge_end.push_back(end);

            ++(*number_of_edges);
            edges.insert(Edge(begin, end));
        }
    }

    return Graph(*number_of_vertices, edge_begin, edge_end);
}

void CheckTopologicalSort(const Graph& graph)
{
    std::set<Edge> edges;
    for (size_t vertex = 0; vertex < graph.GetNumberOfVertices(); ++vertex)
    {
        std::vector<size_t> incidence_list = graph.GetIncidenceList(vertex);
        
        for (size_t incidence_vertex_index = 0; 
            incidence_vertex_index < incidence_list.size();
            ++incidence_vertex_index) {
            edges.insert(Edge(vertex, incidence_list[incidence_vertex_index]));
        }
    }

    bool graph_has_cyclic;
    std::vector<size_t> order = TopologicalSort(graph, &graph_has_cyclic);

    if (graph_has_cyclic != DoesGraphHaveCyclic(graph))
        throw std::runtime_error("Error on TopologicalSortRandomTest");

    if (graph_has_cyclic)
        return;

    // @review: Вообще говоря, эту проверку можно выполнить за число дуг (а не за квадрат числа вершин как сейчас).
    for (size_t begin_index = 0; begin_index < graph.GetNumberOfVertices(); 
        ++begin_index)
    for (size_t end_index = 0; end_index < begin_index; ++end_index)
    if (edges.find(Edge(order[begin_index], order[end_index])) != edges.end())
        throw std::runtime_error("Error on TopologicalSortRandomTest");
}

void TopologicalSortRandomTest()
{
    srand(777);
    for (size_t test = 0; test < 250; ++test)
    {
        size_t unnecessary_number_of_edges;
        size_t unnecassary_number_of_vertices;
        Graph graph = GetRandomGraph(500, 1000, 
            &unnecassary_number_of_vertices,
            &unnecessary_number_of_edges);
        CheckTopologicalSort(graph);
    }
}

void TopologicalSortUnitTest()
{
    bool graph_has_cyclic;

    Graph graph1(1, {}, {});
    if (TopologicalSort(graph1, &graph_has_cyclic) != std::vector<size_t>({ { 0 } }))
        throw std::runtime_error("Error on TopologicalSortUnitTest");

    Graph graph2(2, { 0, 1 }, { 1, 0 });
    TopologicalSort(graph2, &graph_has_cyclic);
    if (!graph_has_cyclic)
        throw std::runtime_error("Error on TopologicalSortUnitTest");

    Graph graph3(5, { 0, 1, 2, 3 }, { 1, 2, 3, 4 });
    if (TopologicalSort(graph3, &graph_has_cyclic) != std::vector<size_t>({ 0, 1, 2, 3, 4 }))
        throw std::runtime_error("Error on TopologicalSortUnitTest");
}

void TopologicalSortTest()
{
    TopologicalSortUnitTest();
    TopologicalSortRandomTest();
}
