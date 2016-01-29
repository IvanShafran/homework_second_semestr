#pragma once

#include <set>
#include <vector>

#include "graph.h"

namespace {

    std::vector<size_t> GetComponentIdOfVertexVector(
        size_t number_of_vertices,
        const std::vector<std::vector<size_t> >& component)
    {
        size_t null_component = number_of_vertices;
        std::vector<size_t> component_id_of_vertex;
        component_id_of_vertex.resize(number_of_vertices, null_component);

        for (size_t component_index = 0; component_index < component.size();
            ++component_index)
        for (size_t vertex_index = 0; vertex_index < component[component_index].size();
            ++vertex_index)
        {
            size_t vertex = component[component_index][vertex_index];

            if (component_id_of_vertex[vertex] == null_component)
                component_id_of_vertex[vertex] = component_index;
            else
                throw std::runtime_error("Error on GetComponentIdOfVertexVector: two or more components have same vertex");
        }

        for (size_t vertex = 0; vertex < number_of_vertices; ++vertex)
        if (component_id_of_vertex[vertex] == null_component)
            throw std::runtime_error("Error on GetComponentIdOfVertexVector: neither component doesn't have one or more vertex");

        return component_id_of_vertex;
    }

    std::set<Edge> ConstructEdgeSet(const Graph& graph,
        const std::vector<std::vector<size_t> >& component)
    {
        std::vector<size_t> component_id_of_vertex =
            GetComponentIdOfVertexVector(graph.GetNumberOfVertices(), component);

        std::set<Edge> edge_set;
        for (size_t vertex = 0; vertex < graph.GetNumberOfVertices(); ++vertex)
        {
            std::vector<size_t> incidence_list = graph.GetIncidenceList(vertex);

            for (size_t incidence_index = 0; incidence_index < incidence_list.size();
                ++incidence_index)
            {
                size_t incidence_vertex = incidence_list[incidence_index];
                size_t first_component = component_id_of_vertex[vertex],
                    second_component = component_id_of_vertex[incidence_vertex];

                if (first_component != second_component &&
                    edge_set.find(Edge(first_component, second_component)) == edge_set.end()) {
                    edge_set.insert(Edge(first_component, second_component));
                }
            }
        }

        return edge_set;
    }

    void ConstructEdges(const std::set<Edge>& edge_set,
        std::vector<Edge>* edges)
    {
        for (std::set<Edge>::iterator iterator = edge_set.begin();
            iterator != edge_set.end(); ++iterator) {
            edges->push_back(Edge(iterator->begin, iterator->end));
        }
    }

    std::unique_ptr<Graph> GetCondensedGraph(const Graph& graph,
        const std::vector<std::vector<size_t> >& component)
    {
        std::set<Edge> edge_set;
        edge_set = ConstructEdgeSet(graph, component);

        std::vector<Edge> edges;
        ConstructEdges(edge_set, &edges);

        return MakeCompactGraph(component.size(), edges);
    }
}
