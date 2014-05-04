#pragma once

#include <memory>
#include <algorithm>
#include <set>

#include "graph.h"
#include "random_functions.h"

/*
*EmptyGraph
*FullGraph
*AcyclicGraph
*FunctionalGraph
*RandomGraph
*/

namespace {
    std::vector<Edge> GenFullGraphEdges(size_t number_of_vertices, size_t* number_of_edges)
    {
        std::vector<Edge> edges;
        *number_of_edges = 0;

        for (size_t vertex = 0; vertex < number_of_vertices; ++vertex)
        for (size_t incidence_vertex = 0; incidence_vertex < number_of_vertices;
            ++incidence_vertex)
        if (vertex != incidence_vertex) {
            edges.push_back(Edge(vertex, incidence_vertex));
            ++(*number_of_edges);
        }

        return edges;
    }

    std::unique_ptr<Graph> GetFullGraph(size_t number_of_vertices, size_t* number_of_edges)
    {
        std::vector<Edge> edges = GenFullGraphEdges(number_of_vertices, number_of_edges);
        return MakeCompactGraph(number_of_vertices, edges);
    }

    std::vector<Edge> GenEmptyGraphEdges(size_t number_of_vertices, size_t* number_of_edges)
    {
        std::vector<Edge> edges;
        *number_of_edges = 0;
        return edges;
    }

    std::unique_ptr<Graph> GetEmptyGraph(size_t number_of_vertices, size_t* number_of_edges)
    {
        std::vector<Edge> edges = GenEmptyGraphEdges(number_of_vertices, number_of_edges);
        return MakeCompactGraph(number_of_vertices, edges);
    }
    
    std::vector<Edge> GenRandomGraphEdges(size_t number_of_vertices, size_t* number_of_edges)
    {
        std::vector<Edge> edges;
        *number_of_edges = Rand<size_t>(0, number_of_vertices * number_of_vertices + 1);

        for (size_t edge_index = 0; edge_index < *number_of_edges; ++edge_index)
        {
            size_t begin = Rand<size_t>(0, number_of_vertices);
            size_t end = Rand<size_t>(0, number_of_vertices);
            edges.push_back(Edge(begin, end));
        }

        return edges;
    }

    std::unique_ptr<Graph> GetRandomGraph(size_t number_of_vertices, size_t* number_of_edges)
    {
        std::vector<Edge> edges = GenRandomGraphEdges(number_of_vertices, number_of_edges);
        return MakeCompactGraph(number_of_vertices, edges);
    }

    std::vector<Edge> GenFunctionalGraphEdges(size_t number_of_vertices, size_t* number_of_edges)
    {
        std::vector<Edge> edges;
        size_t number_of_incidence_vertices =
            Rand<size_t>(0, std::min<size_t>(number_of_vertices - 1, 10));

        *number_of_edges = number_of_vertices * number_of_incidence_vertices;

        for (size_t vertex = 0; vertex < number_of_vertices; ++vertex) {
            for (size_t k = 0; k < number_of_incidence_vertices; ++k)
                edges.push_back(Edge(vertex, Rand<size_t>(0, number_of_vertices)));
        }   

        return edges;
    }

    std::unique_ptr<Graph> GetFunctionalGraph(size_t number_of_vertices, size_t* number_of_edges)
    {
        std::vector<Edge> edges = GenFunctionalGraphEdges(number_of_vertices, number_of_edges);
        return MakeCompactGraph(number_of_vertices, edges);
    }

    std::vector<Edge> GenAcyclicGraphEdges(size_t number_of_vertices, size_t* number_of_edges)
    {
        std::vector<Edge> edges;
        std::vector<size_t> vertex_order;
        for (size_t i = 0; i < number_of_vertices; ++i)
            vertex_order.push_back(i);

        std::random_shuffle(vertex_order.begin(), vertex_order.end());

        *number_of_edges = Rand<size_t>(0, number_of_vertices * number_of_vertices + 1);

        for (size_t i = 0; i < *number_of_edges; ++i) {
            size_t begin_index = Rand<size_t>(0, number_of_vertices - 1);
            size_t end_index = Rand(begin_index, number_of_vertices);
            size_t begin = vertex_order[begin_index];
            size_t end = vertex_order[end_index];

            edges.push_back(Edge(begin, end));
        }

        return edges;
    }

    std::unique_ptr<Graph> GetAcyclicGraph(size_t number_of_vertices, size_t* number_of_edges)
    {
        std::vector<Edge> edges = GenAcyclicGraphEdges(number_of_vertices, number_of_edges);
        return MakeCompactGraph(number_of_vertices, edges);
    }

}
