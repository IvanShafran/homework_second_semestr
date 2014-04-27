#pragma once

#include <vector>
#include <memory>

namespace {
    class Graph {
    public:
        virtual size_t GetNumberOfVertices() const = 0;

        virtual std::vector<size_t> GetIncidenceList(size_t vertex) const = 0;

        virtual ~Graph()
        {}
    };

    class ListOfEdges : public Graph {
        size_t number_of_vertices_; // @review: Количество вершин можно узнать из размера списка смежности.
                                    // @review: Поэтому отдельное поле для этого не нужно.
        std::vector<std::vector<size_t> > list_of_edges_;

    public:
        ListOfEdges(size_t number_of_vertices, const std::vector<size_t>& edge_begin,
            const std::vector<size_t>& edge_end)
        {
            number_of_vertices_ = number_of_vertices;
            list_of_edges_.resize(number_of_vertices);

            for (size_t i = 0; i < edge_begin.size(); ++i) {
                list_of_edges_.at(edge_begin[i]).push_back(edge_end[i]);
            }
        }

        size_t GetNumberOfVertices() const
        {
            return number_of_vertices_;
        }

        std::vector<size_t> GetIncidenceList(size_t vertex) const
        {
            if (vertex >= number_of_vertices_ || vertex < 0) // @review: size_t не бывают отрицательными.
                throw std::runtime_error("Invalid vertex");
            return list_of_edges_[vertex];
        }
    };

    class MatrixOfEdges : public Graph {
        size_t number_of_vertices_; // @review: Аналогично, количество вершин можно не хранить.
        std::vector<std::vector<bool> > matrix_of_edges_;

    public:
        MatrixOfEdges(size_t number_of_vertices, const std::vector<size_t>& edge_begin,
            const std::vector<size_t>& edge_end)
        {
            number_of_vertices_ = number_of_vertices;
            std::vector<bool> bool_vector(number_of_vertices, false);
            matrix_of_edges_.resize(number_of_vertices, bool_vector);

            for (size_t i = 0; i < edge_begin.size(); ++i) {
                matrix_of_edges_.at(edge_begin[i]).at(edge_end[i]) = true;
            }
        }

        size_t GetNumberOfVertices() const
        {
            return number_of_vertices_;
        }

        std::vector<size_t> GetIncidenceList(size_t vertex) const
        {
            if (vertex >= number_of_vertices_ || vertex < 0)
                throw std::runtime_error("Invalid vertex");

            std::vector<size_t> incidence_list;
            for (size_t index = 0; index < number_of_vertices_; ++index)
                if (matrix_of_edges_[vertex][index]) {
                    incidence_list.push_back(index);
                }

            return incidence_list;
        }
    };

    bool IsListBetterThanMatrix(size_t number_of_vertices, size_t number_of_edges)
    {
        long long list_memory = 2 * number_of_edges; // @review: Откуда взялась величина 2?
        long long long_number_of_vertices = number_of_vertices;
        long long matrix_memory = long_number_of_vertices * long_number_of_vertices / 8;
        
        /** @review:
         *  Естественнее было бы завести вспомогательный статический метод в каждом классе:
         * 
         *    class ListOfEdges {
         *      static size_t byteSize(number_of_vertices, edge_begin, edge_end);
         *    };
         *
         *    class MatrixOfEdges {
         *      static size_t byteSize(number_of_vertices, edge_begin, edges_end);
         *    };
         * 
         *  Тогда знания о том, как именно хранится граф хранилось бы локально в каждом классе.
         *  И если представление потребуется поменять, то исправить нужно будет только один класс:
         * 
         *  Выбрать лучшее представление из двух можно будет с помощью вызов:
         *    if (ListOfEdges::byteSize(...) < MatrixOfEdges::byteSize(...)) {
         *      ...
         *    }
         */

        return list_memory <= matrix_memory;
    }

    std::unique_ptr<Graph> MakeCompactGraph(size_t number_of_vertices, 
        const std::vector<size_t>& edge_begin,
        const std::vector<size_t>& edge_end)
    {
        Graph* edges;  // @review: Почему edges? Естественнее было бы назвать graph или result.
        
        size_t numbers_of_edges = edge_begin.size();
        if (IsListBetterThanMatrix(number_of_vertices, numbers_of_edges))
            edges = new ListOfEdges(number_of_vertices, edge_begin, edge_end);
        else
            edges = new MatrixOfEdges(number_of_vertices, edge_begin, edge_end);

        return std::unique_ptr<Graph>(edges);
    }

    struct Edge { // @review: Эту структуру можно было бы использовать в конструкторе классов.
                  // @review: Вместо двух векторов edge_begin, end_end сделать один вектор edges.
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
}
