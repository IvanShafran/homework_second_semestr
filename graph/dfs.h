#pragma once

#include <vector>
#include <stack>

#include "graph.h"

enum colors { WHITE, GREY, BLACK };

class DefaultUserClass {
public:
    DefaultUserClass()
    {}

    void BeforeProcessing(size_t vertex)
    {}

    void ProcessWhiteVertex(size_t edge_begin, size_t edge_end)
    {}

    void ProcessGreyVertex(size_t edge_begin, size_t edge_end)
    {}

    void ProcessBlackVertex(size_t edge_begin, size_t edge_end)
    {}

    void AfterProcessing(size_t vertex)
    {}
};

template <class T>
void DFSStep(const Graph& graph, T* user_class,
    std::vector<colors>* color,
    std::vector<std::vector<size_t> >* incidence_list, 
    std::vector<std::vector<size_t>::iterator >* incidence_iterator,
    std::stack<size_t>* vertex_stack)
{
    while (!vertex_stack->empty()) {
        size_t vertex = vertex_stack->top();

        if ((*color)[vertex] == WHITE) {
            user_class->BeforeProcessing(vertex);
            
            (*incidence_list)[vertex] = graph.GetIncidenceList(vertex);
            (*incidence_iterator)[vertex] = (*incidence_list)[vertex].begin();
            (*color)[vertex] = GREY;
        }

        if ((*incidence_iterator)[vertex] == (*incidence_list)[vertex].end()) {
            vertex_stack->pop();
            (*incidence_list)[vertex].resize(0);
            (*color)[vertex] = BLACK;

            user_class->AfterProcessing(vertex);
        }
        else {
            size_t incidence_vertex = *((*incidence_iterator)[vertex]);
            if ((*color)[incidence_vertex] == WHITE) {
                user_class->ProcessWhiteVertex(vertex, incidence_vertex);

                vertex_stack->push(incidence_vertex);
            }
            else
            if ((*color)[incidence_vertex] == GREY) {
                user_class->ProcessGreyVertex(vertex, incidence_vertex);
            }
            else
            if ((*color)[incidence_vertex] == BLACK) {
                user_class->ProcessBlackVertex(vertex, incidence_vertex);
            }

            ++(*incidence_iterator)[vertex];
        }
    }
}

template <class T = DefaultUserClass>
void DFS(const Graph& graph, T* user_class = &DefaultUserClass())
{
    size_t number_of_vertices = graph.GetNumberOfVertices();
    
    std::vector<colors> color(number_of_vertices, WHITE);

    std::vector<std::vector<size_t> > incidence_list;
    incidence_list.resize(number_of_vertices);

    std::vector<std::vector<size_t>::iterator > incidence_iterator;    
    incidence_iterator.resize(number_of_vertices);

    std::stack<size_t> vertex_stack;

    for (size_t start_vertex = 0; start_vertex < number_of_vertices;
        ++start_vertex) 
    if (color[start_vertex] == WHITE) {
        vertex_stack.push(start_vertex);        
        DFSStep(graph, user_class, &color, &incidence_list, &incidence_iterator,
            &vertex_stack);
    }
}
