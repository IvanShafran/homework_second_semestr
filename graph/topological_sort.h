#pragma once

#include <vector>

#include "graph.h"
#include "dfs.h"

class TopologicalSortClass
{
    size_t number_of_vertices_;
    size_t position_;
    std::vector<size_t> order_;
    bool graph_has_cyclic_;

public:
    TopologicalSortClass(size_t number_of_vertices) : 
        position_(number_of_vertices - 1), 
        number_of_vertices_(number_of_vertices),
        graph_has_cyclic_(false)
    {
        order_.resize(number_of_vertices);
    }

    bool DoesGraphHaveCyclic()
    {
        return graph_has_cyclic_;
    }

    std::vector<size_t> GetOrder()
    {
        return order_;
    }

    void BeforeProcessing(size_t vertex)
    {}

    void ProcessWhiteVertex(size_t edge_begin, size_t edge_end)
    {}

    void ProcessGreyVertex(size_t edge_begin, size_t edge_end)
    {
        graph_has_cyclic_ = true;
    }

    void ProcessBlackVertex(size_t edge_begin, size_t edge_end)
    {}

    void AfterProcessing(size_t vertex)
    {
        order_[position_] = vertex;
        --position_;
    }
};

std::vector<size_t> TopologicalSort(const Graph& graph, bool* graph_has_cyclic)
{
    TopologicalSortClass user_class(graph.GetNumberOfVertices());
    DFS<TopologicalSortClass>(graph, &user_class);
    
    *graph_has_cyclic = user_class.DoesGraphHaveCyclic();

    if (user_class.DoesGraphHaveCyclic())
        return std::vector<size_t>({});
    else
        return user_class.GetOrder();
}
