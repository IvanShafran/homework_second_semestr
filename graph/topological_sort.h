#pragma once

#include <vector>

#include "graph.h"
#include "dfs.h"
#include "graph_has_cycle.h"

struct TopologicalSortVisitor : public DFSVisitor {
    std::vector<size_t> topological_reverse_order_;

    void AfterProcessing(size_t vertex)
    {
        topological_reverse_order_.push_back(vertex);
    }
};

std::vector<size_t> TopologicalSort(const Graph& graph)
{
    TopologicalSortVisitor topological_sort_visitor;
    DFS(graph, &topological_sort_visitor);
    
    bool graph_has_cycle = DoesGraphHaveCycle(graph);

    if (graph_has_cycle)
        throw std::runtime_error("Error on TopologicalSort: Graph has cycle");
    else {
        std::reverse(topological_sort_visitor.topological_reverse_order_.begin(), 
            topological_sort_visitor.topological_reverse_order_.end());
        return topological_sort_visitor.topological_reverse_order_;
    }
}
