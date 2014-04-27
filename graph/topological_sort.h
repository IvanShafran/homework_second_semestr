#pragma once

#include <vector>
#include <memory>

#include "graph.h"
#include "dfs.h"

/** @review:
 * Как правило чем проще код, тем лучше:
 * 
 * struct TopologicalSortClass : public DefaultDFSUserClass {
 *   std::vector<size_t> reversed_topological_order;
 *   bool graph_has_cyclic;
 * 
 *   TopologicalSortClass() : graph_has_cyclic(false)
 *   { }
 *
 *   void ProcessEdge(size_t, size_t, colors end_color)
 *   {
 *       if (end_color == GREY)
 *           graph_has_cyclic_ = true;
 *   }
 *
 *   void AfterProcessing(size_t vertex)
 *   {
 *       reversed_topological_order.push_back(vertex);
 *   }
 * };
 */
class TopologicalSortClass : AbstractDFSUserClass {
    size_t number_of_vertices_;
    size_t position_;
    std::vector<size_t> topological_order_;
    bool graph_has_cyclic_;

public:
    explicit TopologicalSortClass(size_t number_of_vertices) : 
        position_(number_of_vertices - 1), 
        number_of_vertices_(number_of_vertices),
        graph_has_cyclic_(false)
    {
        topological_order_.resize(number_of_vertices);
    }

    bool GraphHasCyclic() // @review: const
    {
        return graph_has_cyclic_;
    }

    /* const */ std::vector<size_t> /* & */ GetTopologicalOrder()
    {
        return topological_order_;
    }

    void BeforeProcessing(size_t vertex)
    {}

    void ProcessEdge(size_t edge_begin, size_t edge_end, colors end_color)
    {
        if (end_color == GREY)
            graph_has_cyclic_ = true;
    }

    void AfterProcessing(size_t vertex)
    {
        topological_order_[position_] = vertex;
        --position_;
    }
};

std::vector<size_t> TopologicalSort(const std::unique_ptr<Graph>& graph, bool* graph_has_cyclic)
{
    TopologicalSortClass topological_sort_class(graph->GetNumberOfVertices());
    DFS(graph, &topological_sort_class);
    
    *graph_has_cyclic = topological_sort_class.GraphHasCyclic();

    if (topological_sort_class.GraphHasCyclic())
        return std::vector<size_t>({});  // @review: В таком случае естественнее бросить исключение.
    else
        return topological_sort_class.GetTopologicalOrder();
}
