#include <memory>
#include <vector>
#include <string>

#include "graph.h"
#include "Tarjan's_strongly_connected_components_algorithm.h"
#include "check_strong_connected_component.h"

void TestAllBefore6VerticesGraph(const Graph& graph)
{
    std::vector<std::vector<size_t> > component =
        GetStronglyConnectedComponents(graph);
    CheckStronglyConnectedComponents(graph, component, "TestAllBefore6VerticesGraph");
}

std::vector<std::vector<size_t> > GenMatrixOfEdges(
    size_t number_of_vertices,
    size_t mask)
{
    std::vector<std::vector<size_t> > matrix(number_of_vertices, 
        std::vector<size_t>(number_of_vertices));
    size_t bit = 0;

    for (size_t first_index = 0; first_index < number_of_vertices; ++first_index)
    for (size_t second_index = 0; second_index < number_of_vertices; ++second_index)
    if (first_index != second_index)
    {
        if ((mask & (1 << bit)) != 0)
            matrix[first_index][second_index] = 1;
        ++bit;
    }

    return matrix;
}

void GenEdgesFromMatrix(
    const std::vector<std::vector<size_t> >& matrix,
    std::vector<Edge>* edges)
{
    size_t number_of_vertices = matrix.size();
    for (size_t first_index = 0; first_index < number_of_vertices; ++first_index)
    for (size_t second_index = 0; second_index < number_of_vertices; ++second_index)
    if (matrix[first_index][second_index] == 1)
    {
        edges->push_back(Edge(first_index, second_index));
    }
}

void TestAllBefore6VerticesGraph()
{
    for (size_t number_of_vertices = 0; number_of_vertices < 6; 
        ++number_of_vertices)
    for (size_t mask = 0; mask < 
        (1 << (number_of_vertices * number_of_vertices - number_of_vertices)); 
        ++mask)
    {
        std::vector<std::vector<size_t> > matrix_of_edges = GenMatrixOfEdges(number_of_vertices, 
            mask);

        std::vector<Edge> edges;
        GenEdgesFromMatrix(matrix_of_edges, &edges);

        std::unique_ptr<Graph> graph = MakeCompactGraph(number_of_vertices, edges);
        TestAllBefore6VerticesGraph(*graph);
    }
}
