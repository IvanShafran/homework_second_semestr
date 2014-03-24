#pragma once

#include <vector>
#include <stack>

#include "graph.h"

enum colors { white, grey, black };

class DefaultUserClass {
public:
    DefaultUserClass()
    {}

    void BeforeStep()
    {}

    void BeforeWhiteVertex()
    {}

    void BeforeGreyVertex()
    {}

    void BeforeBlackVertex()
    {}

    void AfterStep()
    {}
};

template <class T>
void DFSStep(const Graph& graph, size_t vertex, std::vector<colors>* color, T* user_class)
{
    user_class->BeforeStep(vertex);

    (*color)[vertex] = grey;

    std::vector<size_t> incidence_list = graph.GetIncidenceList(vertex);

    for (size_t incidence_vertex_index = 0; incidence_vertex_index < incidence_list.size();
        ++incidence_vertex_index) {
        size_t incidence_vertex = incidence_list[incidence_vertex_index];
        if (color[incidence_vertex] == white) {
            user_class->BeforeWhiteVertex(vertex, incidence_vertex);
            DFSStep(graph, incidence_vertex, used);
        }
        else
        if (color[incidence_vertex] == grey) {
            user_class->BeforeGreyVertex(vertex, incidence_vertex);
        }
        else
        if (color[incidence_vertex] == black) {
            user_class->BeforeBlackVertex(vertex, incidence_vertex);
        }
    }

    (*color)[vertex] = black;

    user_class->AfterStep(vertex);
}


template <class T>
void DFS(const Graph& graph, T* user_class = DefaultUserClass())
{
    std::vector<colors> color(graph.GetNumberOfVertices(), white);

    for (size_t vertex = 0; vertex < graph.GetNumberOfVertices(); ++vertex)
    if (color[vertex] == white) {
        DFSStep(graph, vertex, color, user_class);
    }
}
