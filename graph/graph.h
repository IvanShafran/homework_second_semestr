#pragma once

#include <vector>
#include <memory>

namespace {
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

    bool operator == (const Edge& first_edge, const Edge& second_edge)
    {
        return first_edge.begin == second_edge.begin && 
            first_edge.end == second_edge.end;
    }

    class Graph {
    public:
        virtual size_t GetNumberOfVertices() const = 0;

        virtual std::vector<size_t> GetIncidenceList(size_t vertex) const = 0;

        virtual ~Graph()
        {}
    };

    class ListOfEdges : public Graph {
        std::vector<std::vector<size_t> > list_of_edges_;

    public:
        ListOfEdges(size_t number_of_vertices, const std::vector<Edge>& edges)
        {
            list_of_edges_.resize(number_of_vertices);

            for (size_t i = 0; i < edges.size(); ++i) {
                list_of_edges_.at(edges[i].begin).push_back(edges[i].end);
            }
        }

        size_t GetNumberOfVertices() const
        {
            return list_of_edges_.size();
        }

        std::vector<size_t> GetIncidenceList(size_t vertex) const
        {
            if (vertex >= this->GetNumberOfVertices())
                throw std::runtime_error("GetIncidenceList: Invalid vertex");
            return list_of_edges_[vertex];
        }

        static size_t ByteSize(size_t number_of_vertices, const std::vector<Edge>& edges)
        {
            //list_memory = 3 * number_of_edges, where 3 is experimental constant
            size_t number_of_edges = edges.size();
            return 3 * number_of_edges;
        }
    };

    class MatrixOfEdges : public Graph {
        std::vector<std::vector<bool> > matrix_of_edges_;

    public:
        MatrixOfEdges(size_t number_of_vertices, const std::vector<Edge>& edges)
        {
            std::vector<bool> bool_vector(number_of_vertices, false);
            matrix_of_edges_.resize(number_of_vertices, bool_vector);

            for (size_t i = 0; i < edges.size(); ++i) {
                matrix_of_edges_.at(edges[i].begin).at(edges[i].end) = true;
            }
        }

        size_t GetNumberOfVertices() const
        {
            return matrix_of_edges_.size();
        }

        std::vector<size_t> GetIncidenceList(size_t vertex) const
        {
            if (vertex >= this->GetNumberOfVertices())
                throw std::runtime_error("GetIncidenceList: Invalid vertex");

            std::vector<size_t> incidence_list;
            for (size_t index = 0; index < this->GetNumberOfVertices(); ++index)
            if (matrix_of_edges_[vertex][index]) {
                incidence_list.push_back(index);
            }

            return incidence_list;
        }

        static size_t ByteSize(size_t number_of_vertices, const std::vector<Edge>& edges)
        {
            //matrix_memory without multiplication by 2, because we use vector.resize()
            //division by 8, because vector<bool> uses bit optimization
            return number_of_vertices * number_of_vertices / 8;
        }
    };

    std::unique_ptr<Graph> MakeCompactGraph(size_t number_of_vertices, 
        const std::vector<Edge>& edges)
    {
        Graph* graph;
        size_t numbers_of_edges = edges.size();
        if (ListOfEdges::ByteSize(number_of_vertices, edges) < 
            MatrixOfEdges::ByteSize(number_of_vertices, edges))
            graph = new ListOfEdges(number_of_vertices, edges);
        else
            graph = new MatrixOfEdges(number_of_vertices, edges);

        return std::unique_ptr<Graph>(graph);
    }

}
