#pragma once

#include <vector>
#include <stack>

#include "graph.h"

enum colors { WHITE, GREY, BLACK };

class DFSVisitor
{
public:
    virtual void BeforeProcessing(size_t vertex) {};

    virtual void ProcessIncidenceVertex(size_t edge_begin, size_t edge_end, colors end_color) {};

    virtual void AfterProcessing(size_t vertex) {};
};

template <class T>
void DFSStep(const Graph& graph, T* visitor,
    std::vector<colors>* color,
    std::vector<std::vector<size_t> >* incidence_lists, 
    std::vector<std::vector<size_t>::iterator >* incidence_iterator,
    std::stack<size_t>* vertex_stack)
{
    while (!vertex_stack->empty()) {
        size_t vertex = vertex_stack->top();

        if ((*color)[vertex] == WHITE) {
            visitor->BeforeProcessing(vertex);
            
            (*incidence_lists)[vertex] = graph.GetIncidenceList(vertex);
            (*incidence_iterator)[vertex] = (*incidence_lists)[vertex].begin();
            (*color)[vertex] = GREY;
        }

        if ((*incidence_iterator)[vertex] == (*incidence_lists)[vertex].end()) {
            vertex_stack->pop();
            (*incidence_lists)[vertex].resize(0);
            (*color)[vertex] = BLACK;

            visitor->AfterProcessing(vertex);
        }
        else {
            size_t incidence_vertex = *((*incidence_iterator)[vertex]);

            visitor->ProcessIncidenceVertex(vertex, incidence_vertex, 
                (*color)[incidence_vertex]);

            if ((*color)[incidence_vertex] == WHITE) {
                vertex_stack->push(incidence_vertex);
            }

            ++(*incidence_iterator)[vertex];
        }
    }
}

template <class T = DFSVisitor>
void DFS(const Graph& graph, T* visitor = &DFSVisitor())
{
    size_t number_of_vertices = graph.GetNumberOfVertices();
    
    std::vector<colors> color(number_of_vertices, WHITE);

    std::vector<std::vector<size_t> > incidence_lists;
    incidence_lists.resize(number_of_vertices);

    std::vector<std::vector<size_t>::iterator > incidence_iterator;
    incidence_iterator.resize(number_of_vertices);

    std::stack<size_t> vertex_stack;

    for (size_t start_vertex = 0; start_vertex < number_of_vertices; ++start_vertex)
    if (color[start_vertex] == WHITE) {
        vertex_stack.push(start_vertex);
        DFSStep(graph, visitor, &color, &incidence_lists, &incidence_iterator,
            &vertex_stack);
    }
}
