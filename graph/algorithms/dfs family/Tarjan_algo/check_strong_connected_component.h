#pragma once

#include <memory>
#include <vector>
#include <string>

#include "graph.h"
#include "Tarjan's_strongly_connected_components_algorithm.h"
#include "graph_generate.h"
#include "condense_graph.h"

namespace {
    std::vector<colors> GetColorAfterDFSStep(size_t vertex,
        const Graph& graph)
    {
        size_t number_of_vertices = graph.GetNumberOfVertices();
        std::vector<colors> color(number_of_vertices, WHITE);
        std::vector<std::vector<size_t> > incidence_lists(number_of_vertices);
        std::vector<std::vector<size_t>::iterator > incidence_iterator(number_of_vertices);
        std::stack<size_t> vertex_stack;
        DFSVisitor default_dfs_class;
        vertex_stack.push(vertex);

        DFSStep(graph, &default_dfs_class, &color, &incidence_lists,
            &incidence_iterator, &vertex_stack);

        return color;
    }

    void MarkVisitedVertices(const std::vector<colors>& color, std::vector<size_t>* number_of_visit)
    {
        for (size_t vertex = 0; vertex < color.size(); ++vertex)
        if (color[vertex] == BLACK)
            ++((*number_of_visit)[vertex]);
    }

    size_t GetNumberOfVisitedInComponent(
        const std::vector<colors>& color,
        const std::vector<bool>& vertex_in_component)
    {
        size_t result = 0;
        size_t number_of_vertices = color.size();
        for (size_t vertex = 0; vertex < number_of_vertices; ++vertex)
        if (vertex_in_component[vertex] && color[vertex] == BLACK)
            ++result;

        return result;
    }

    void CheckComponent(
        const Graph& graph,
        const std::vector<size_t>& component,
        const std::vector<size_t>& number_of_visit,
        const std::string& error_text)
    {
        size_t number_of_vertices = number_of_visit.size();
        size_t number_of_vertices_in_component = component.size();
        std::vector<bool> vertex_in_component(number_of_vertices, false);

        for (size_t vertex_index = 0; vertex_index < number_of_vertices_in_component;
            ++vertex_index)
        {
            size_t vertex = component[vertex_index];
            vertex_in_component[vertex] = true;
            if (number_of_visit[vertex] != number_of_vertices_in_component)
                throw std::runtime_error("Error on test " + error_text + " some vertex isn't in component");
        }

        for (size_t vertex = 0; vertex < number_of_vertices; ++vertex)
        if (!vertex_in_component[vertex] && number_of_visit[vertex] == number_of_vertices_in_component) {
            std::vector<colors> color = GetColorAfterDFSStep(vertex, graph);

            if (GetNumberOfVisitedInComponent(color, vertex_in_component) == number_of_vertices_in_component)
                throw std::runtime_error("Error on " + error_text + " some vertex must be in component");
        }
    }

    void CheckStronglyConnectedComponents(
        const Graph& graph,
        const std::vector<std::vector<size_t> >& component,
        const std::string& error_text)
    {
        size_t number_of_vertices = graph.GetNumberOfVertices();

        for (size_t component_index = 0; component_index < component.size();
            ++component_index)
        {
            std::vector<size_t> number_of_visit(number_of_vertices, 0);

            for (size_t vertex_index = 0; vertex_index < component[component_index].size();
                ++vertex_index)
            {
                size_t vertex = component[component_index][vertex_index];
                std::vector<colors> color = GetColorAfterDFSStep(vertex, graph);
                MarkVisitedVertices(color, &number_of_visit);
            }

            CheckComponent(graph, component[component_index], number_of_visit, error_text);
        }
    }
}
