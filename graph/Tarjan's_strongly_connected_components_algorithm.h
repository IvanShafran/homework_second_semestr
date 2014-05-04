#pragma once

#include <vector>
#include <stack>
#include <algorithm>
#include <set>

#include "graph.h"
#include "dfs.h"

namespace {

    const size_t NULL_PARENT = SIZE_MAX;
    const size_t NULL_COMPONENT = SIZE_MAX;

    class TarjanStronglyConnectedComponentsDFSVisitor : public DFSVisitor {
        std::vector<size_t> entry_time_;
        std::vector<size_t> min_child_entry_time_;
        std::vector<size_t> parent_;
        std::vector<size_t> component_id_of_vertex_;
        std::stack<size_t> vertex_stack_;
        size_t number_of_compopents_;
        size_t time_;

    public:
        std::vector<std::vector<size_t> > component_;

        TarjanStronglyConnectedComponentsDFSVisitor(size_t number_of_vertices) :
            number_of_compopents_(0),
            component_id_of_vertex_(number_of_vertices, NULL_COMPONENT),
            entry_time_(number_of_vertices),
            min_child_entry_time_(number_of_vertices),
            parent_(number_of_vertices, NULL_PARENT),
            time_(0)
        {}

        void BeforeProcessing(size_t vertex)
        {
            vertex_stack_.push(vertex);
            entry_time_[vertex] = time_;
            min_child_entry_time_[vertex] = time_;
            ++time_;
        }

        void ProcessIncidenceVertex(size_t edge_begin, size_t edge_end, colors color)
        {
            if (color == GREY || (color == BLACK && component_id_of_vertex_[edge_end] == NULL_COMPONENT)) {
                min_child_entry_time_[edge_begin] =
                    std::min(min_child_entry_time_[edge_begin], min_child_entry_time_[edge_end]);
            }

            if (color == WHITE) {
                parent_[edge_end] = edge_begin;
            }
        }

        void AfterProcessing(size_t vertex)
        {
            if (parent_[vertex] != NULL_PARENT)
            {
                min_child_entry_time_[parent_[vertex]] =
                    std::min(min_child_entry_time_[parent_[vertex]],
                    min_child_entry_time_[vertex]);
            }

            if (entry_time_[vertex] == min_child_entry_time_[vertex]) {
                component_.push_back(std::vector<size_t>());

                size_t component_vertex;
                do {
                    component_vertex = vertex_stack_.top();
                    vertex_stack_.pop();
                    component_id_of_vertex_[component_vertex] =
                        number_of_compopents_;
                    component_[number_of_compopents_].
                        push_back(component_vertex);
                } while (!vertex_stack_.empty() && component_vertex != vertex);


                ++number_of_compopents_;
            }
        }
    };

    /*
    *GetStronglyConnectedComponents returns strongly connected components as vector of vectors,
    *each vector has set of vertices, which belong to this component.
    *Component vectors are in reverse topological order.
    */

    std::vector<std::vector<size_t> > GetStronglyConnectedComponents(const Graph& graph)
    {
        TarjanStronglyConnectedComponentsDFSVisitor dfs_class(graph.GetNumberOfVertices());
        DFS(graph, &dfs_class);

        return dfs_class.component_;
    }
}
