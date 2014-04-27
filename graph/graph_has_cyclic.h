#pragma once

#include "graph.h"
#include "dfs.h"


/** @review:
 *  Как правило чем меньше кода и чем он проще, тем лучше:
 * 
 *  struct CyclicSearchClass : public DefaultDFSUserClass {
 *    bool graph_has_cyclic = false;
 *
 *    void ProcessEdge(size_t, size_t, colors end_color)
 *    {
 *      if (end_color == GREY)
 *        graph_has_cyclic = true;
 *    }
 *  };
 */

class CyclicSearchClass : AbstractDFSUserClass { // @review: Private наследование ничего вам не даёт.
    bool graph_has_cyclic_;
public:
    CyclicSearchClass() : graph_has_cyclic_(false)
    {}

    bool GraphHasCyclic()
    {
        return graph_has_cyclic_;
    }

    void BeforeProcessing(size_t vertex)
    {}

    void ProcessEdge(size_t edge_begin, size_t edge_end, colors end_color)
    {
        if (end_color == GREY)
            graph_has_cyclic_ = true;
    }

    void AfterProcessing(size_t vertex)
    {}
};

bool DoesGraphHaveCyclic(const std::unique_ptr<Graph>& graph)
{
    CyclicSearchClass user_class;
    DFS(graph, &user_class);
    return user_class.GraphHasCyclic();
}
