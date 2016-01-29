#pragma once

#include "graph.h"
#include "dfs.h"

struct CycleSearchClass : public DFSVisitor {
    bool graph_has_cycle_;
    
    CycleSearchClass() : graph_has_cycle_(false)
    {}

    void ProcessIncidenceVertex(size_t edge_begin, size_t edge_end, colors end_color)
    {
        if (end_color == GREY)
            graph_has_cycle_ = true;
    }
};

bool DoesGraphHaveCycle(const Graph& graph)
{
    CycleSearchClass dfs_visitor;
    DFS(graph, &dfs_visitor);
    return dfs_visitor.graph_has_cycle_;
}
