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
    void GenFullGraphEdges(size_t number_of_vertices, size_t* number_of_edges,
        std::vector<size_t>* edge_begin, std::vector<size_t>* edge_end)
    {
        *number_of_edges = 0;

        for (size_t vertex = 0; vertex < number_of_vertices; ++vertex)
        for (size_t incidence_vertex = 0; incidence_vertex < number_of_vertices;
            ++incidence_vertex)
        if (vertex != incidence_vertex) {
            edge_begin->push_back(vertex);
            edge_end->push_back(incidence_vertex);
            ++(*number_of_edges);
        }
    }

    std::unique_ptr<Graph> GetFullGraph(size_t number_of_vertices, size_t* number_of_edges)
    {
        std::vector<size_t> edge_begin, edge_end;
        GenFullGraphEdges(number_of_vertices, number_of_edges,
            &edge_begin, &edge_end);
        return MakeCompactGraph(number_of_vertices, edge_begin, edge_end);
    }

    void GenEmptyGraphEdges(size_t number_of_vertices, size_t* number_of_edges,
        std::vector<size_t>* edge_begin, std::vector<size_t>* edge_end)
    {
        *number_of_edges = 0;
    }

    std::unique_ptr<Graph> GetEmptyGraph(size_t number_of_vertices, size_t* number_of_edges)
    {
        std::vector<size_t> edge_begin, edge_end;
        GenEmptyGraphEdges(number_of_vertices, number_of_edges, 
            &edge_begin, &edge_end);
        return MakeCompactGraph(number_of_vertices, edge_begin, edge_end);
    }
    
    void GenRandomGraphEdges(size_t number_of_vertices, size_t* number_of_edges,
        std::vector<size_t>* edge_begin, std::vector<size_t>* edge_end)
    {
        size_t approximate_number_of_edges = 4 * number_of_vertices;

        std::set<Edge> edges;

        for (size_t vertex = 0; vertex < number_of_vertices; ++vertex) {
            edges.insert(Edge(vertex, vertex));
        }

        *number_of_edges = 0;
        for (size_t edge_index = 0; edge_index < approximate_number_of_edges; ++edge_index)
        {
            size_t begin = Rand(0, number_of_vertices);
            size_t end = Rand(0, number_of_vertices);
            if (edges.find(Edge(begin, end)) == edges.end()) {
                edge_begin->push_back(begin);
                edge_end->push_back(end);

                ++(*number_of_edges);
                edges.insert(Edge(begin, end));
            }
        }

    }

    std::unique_ptr<Graph> GetRandomGraph(size_t number_of_vertices, size_t* number_of_edges)
    {
        std::vector<size_t> edge_begin, edge_end;
        GenRandomGraphEdges(number_of_vertices, number_of_edges,
            &edge_begin, &edge_end);
        return MakeCompactGraph(number_of_vertices, edge_begin, edge_end);
    }

    void GenFunctionalGraphEdges(size_t number_of_vertices, size_t* number_of_edges,
        std::vector<size_t>* edge_begin, std::vector<size_t>* edge_end)
    {
        size_t number_of_incidence_vertices =
            Rand(1, std::min<size_t>(number_of_vertices - 1, static_cast<size_t>(10)));

        *number_of_edges = number_of_vertices * number_of_incidence_vertices;

        for (size_t vertex = 0; vertex < number_of_vertices; ++vertex) {
            std::set<size_t> used;
            used.insert(vertex);
            for (size_t k = 0; k < number_of_incidence_vertices; ++k)
            {
                edge_begin->push_back(vertex);

                size_t end = Rand(0, number_of_vertices);
                while (used.find(end) != used.end())
                    end = Rand(0, number_of_vertices);

                edge_end->push_back(end);
            }
        }
    }

    std::unique_ptr<Graph> GetFunctionalGraph(size_t number_of_vertices, size_t* number_of_edges)
    {
        std::vector<size_t> edge_begin, edge_end;
        GenFunctionalGraphEdges(number_of_vertices, number_of_edges,
            &edge_begin, &edge_end);
        return MakeCompactGraph(number_of_vertices, edge_begin, edge_end);
    }

    void GenAcyclicGraphEdges(size_t number_of_vertices, size_t* number_of_edges,
        std::vector<size_t>* edge_begin, std::vector<size_t>* edge_end)
    {
        std::vector<size_t> vertex_order;
        for (size_t i = 0; i < number_of_vertices; ++i)
            vertex_order.push_back(i);

        std::random_shuffle(vertex_order.begin(), vertex_order.end());

        std::set<Edge> edges;
        size_t max_number_of_edges = 2 * number_of_vertices;
        *number_of_edges = 0;

        for (size_t i = 0; i < max_number_of_edges; ++i) {
            size_t begin_index = Rand(0, number_of_vertices - 1);
            size_t end_index = Rand(begin_index, number_of_vertices);
            size_t begin = vertex_order[begin_index];
            size_t end = vertex_order[end_index];

            if (edges.find(Edge(begin, end)) == edges.end() && begin_index < end_index)
            {
                ++(*number_of_edges);
                edges.insert(Edge(begin, end));
                edge_begin->push_back(begin);
                edge_end->push_back(end);
            }
        }
    }

    std::unique_ptr<Graph> GetAcyclicGraph(size_t number_of_vertices, size_t* number_of_edges)
    {
        std::vector<size_t> edge_begin, edge_end;
        GenAcyclicGraphEdges(number_of_vertices, number_of_edges,
            &edge_begin, &edge_end);
        return MakeCompactGraph(number_of_vertices, edge_begin, edge_end);
    }
}
