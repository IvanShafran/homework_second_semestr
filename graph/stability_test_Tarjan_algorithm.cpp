#include <memory>
#include <vector>
#include <algorithm>

#include "graph.h"
#include "Tarjan's_strongly_connected_components_algorithm.h"
#include "graph_generate.h"

void DoVerticesRandomShuffle(size_t number_of_vertices, 
    std::vector<size_t>* new_index_of_vertex)
{
    for (size_t index = 0; index < number_of_vertices; ++index)
        new_index_of_vertex->push_back(index);

    std::random_shuffle(new_index_of_vertex->begin(), new_index_of_vertex->end());
}

void ConvertEdges(
    const std::vector<size_t>& new_index_of_vertex, 
    std::vector<Edge>* edges)
{
    for (size_t edge_index = 0; edge_index < edges->size(); ++edge_index)
    {
        (*edges)[edge_index].begin = new_index_of_vertex[(*edges)[edge_index].begin];
        (*edges)[edge_index].end = new_index_of_vertex[(*edges)[edge_index].end];
    }
}

void ConvertComponent(
    const std::vector<size_t>& new_index_of_vertex, 
    std::vector<std::vector<size_t> >* component)
{
    for (size_t component_index = 0; component_index < component->size();
        ++component_index)
    for (size_t vertex_index = 0;
        vertex_index < (*component)[component_index].size();
        ++vertex_index)
    {
        (*component)[component_index][vertex_index] =
            new_index_of_vertex[(*component)[component_index][vertex_index]];
    }
}

void SortVertexInComponents(
    std::vector<std::vector<size_t> >* component)
{
    for (size_t component_index = 0; component_index < component->size();
        ++component_index)
    {
        std::sort((*component)[component_index].begin(),
            (*component)[component_index].end());
    }
}

struct ComponentMinVertex
{
    size_t min_vertex;
    size_t component_index;

    ComponentMinVertex(size_t vertex, size_t index) :
        min_vertex(vertex), component_index(index)
    {}
};

bool operator<(
    const ComponentMinVertex& first,
    const ComponentMinVertex& second)
{
    return first.min_vertex < second.min_vertex;
}

std::vector<ComponentMinVertex> ConstructStructForSort(
    std::vector<std::vector<size_t> >* component)
{
    std::vector<ComponentMinVertex> result;
    for (size_t component_index = 0; component_index < component->size();
        ++component_index)
    {
        result.push_back(ComponentMinVertex((*component)[component_index][0],
            component_index));
    }

    return result;
}

std::vector<size_t> GetComponentOrderByMinVertex(
    std::vector<std::vector<size_t> >* component)
{
    SortVertexInComponents(component);

    std::vector<ComponentMinVertex> vector_for_sort_by_min_vertex_in_component =
        ConstructStructForSort(component);

    std::sort(vector_for_sort_by_min_vertex_in_component.begin(),
        vector_for_sort_by_min_vertex_in_component.end());

    std::vector<size_t> order;
    for (size_t index = 0; index < component->size(); ++index)
        order.push_back(vector_for_sort_by_min_vertex_in_component[index].
            component_index);

    return order;
}

void CheckStabilityTarjanAlgorithm(
    const std::vector<size_t>& new_index_of_vertex,
    std::vector<std::vector<size_t> >* first_component,
    std::vector<std::vector<size_t> >* second_component)
{
    if (first_component->size() != second_component->size())
        throw std::runtime_error("Error on StabilityTestTarjanAlgorithm");

    ConvertComponent(new_index_of_vertex, first_component);

    std::vector<size_t> first_component_order = 
        GetComponentOrderByMinVertex(first_component);
    std::vector<size_t> second_component_order = 
        GetComponentOrderByMinVertex(second_component);

    size_t component_size = first_component->size();
    for (size_t order_index = 0; order_index < component_size;
        ++order_index)
    if ((*first_component)[first_component_order[order_index]] !=
        (*second_component)[second_component_order[order_index]])
        throw std::runtime_error("Error on StabilityTestTarjanAlgorithm");
}

void StabilityTestTarjanAlgorithm(size_t number_of_vertices)
{
    size_t number_of_edges;
    std::vector<Edge> edges = GenRandomGraphEdges(number_of_vertices, &number_of_edges);

    std::vector<std::vector<size_t> > first_component;
    {
        std::unique_ptr<Graph> graph = MakeCompactGraph(number_of_vertices, 
            edges);

        first_component = GetStronglyConnectedComponents(*graph);
    }

    std::vector<size_t> new_index_of_vertex;
    DoVerticesRandomShuffle(number_of_vertices, &new_index_of_vertex);
    ConvertEdges(new_index_of_vertex, &edges);
    std::random_shuffle(edges.begin(), edges.end());

    std::vector<std::vector<size_t> > second_component;
    {
        std::unique_ptr<Graph> graph = MakeCompactGraph(number_of_vertices,
            edges);

        second_component = GetStronglyConnectedComponents(*graph);
    }

    CheckStabilityTarjanAlgorithm(new_index_of_vertex, &first_component, 
        &second_component);
}

void StabilityTestTarjanAlgorithm()
{
    size_t number_of_test = 100;
    size_t number_of_vertices = 100;
    srand(777);
    for (size_t test = 0; test < number_of_test; ++test)
        StabilityTestTarjanAlgorithm(number_of_vertices);
}
