#pragma once

#include "graph.h"
#include "dfs.h"

class CyclicSearchClass
{
    bool graph_has_cyclic_;
public:
    CyclicSearchClass() : graph_has_cyclic_(false)
    {}

    bool DoesGraphHaveCyclic()
    {
        return graph_has_cyclic_;
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
    {}
};

bool DoesGraphHaveCyclic(const Graph& graph)
{
    CyclicSearchClass user_class;
    DFS(graph, &user_class);
    return user_class.DoesGraphHaveCyclic();
}
