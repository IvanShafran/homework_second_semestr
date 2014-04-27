#pragma once

#include <vector>
#include <stack>
#include <memory>

#include "graph.h"

enum colors { WHITE, GREY, BLACK };

class AbstractDFSUserClass // @review: Обычно такие сущности называют visitor.
{
public:
    virtual void BeforeProcessing(size_t vertex) = 0;
    
    virtual void ProcessEdge(size_t edge_begin, size_t edge_end, colors end_color) = 0;
      // @review: Не очевидно, когда вызывается этот метод.
      // @review: Стоит придумать более конкретное название для него.
      
    virtual void AfterProcessing(size_t vertex) = 0;
};


// @review: А для чего понадобился класс DefaultDFSUserClass?
// @review: Реализацию методов можно предоставить сделать прямо в первом классе.
class DefaultDFSUserClass : AbstractDFSUserClass {
public:
    void BeforeProcessing(size_t vertex)
    {}

    void ProcessEdge(size_t edge_begin, size_t edge_end, colors end_color)
    {}

    void AfterProcessing(size_t vertex)
    {}
};

template <class T>
void DFSStep(const std::unique_ptr<Graph>& graph, T* user_class,
    std::vector<colors>* color,
    std::vector<std::vector<size_t> >* incidence_lists, 
    std::vector<std::vector<size_t>::iterator >* incidence_iterator,
    std::stack<size_t>* vertex_stack)
{   // @review: А нельзя ли уменьшить количество аргументов, например,
    // @review: хранить в incidence_lists только те дуги, которые ещё не просмотрены?
    
    while (!vertex_stack->empty()) {
        size_t vertex = vertex_stack->top();

        if ((*color)[vertex] == WHITE) {
            user_class->BeforeProcessing(vertex);
            
            (*incidence_lists)[vertex] = graph->GetIncidenceList(vertex);
            (*incidence_iterator)[vertex] = (*incidence_lists)[vertex].begin();
            (*color)[vertex] = GREY;
        }

        if ((*incidence_iterator)[vertex] == (*incidence_lists)[vertex].end()) {
            vertex_stack->pop();
            (*incidence_lists)[vertex].resize(0);
            (*color)[vertex] = BLACK;

            user_class->AfterProcessing(vertex);
        }
        else {
            size_t incidence_vertex = *((*incidence_iterator)[vertex]);

            user_class->ProcessEdge(vertex, incidence_vertex, (*color)[incidence_vertex]);

            if ((*color)[incidence_vertex] == WHITE) {
                vertex_stack->push(incidence_vertex);
            }

            ++(*incidence_iterator)[vertex];
        }
    }
}

template <class T = DefaultDFSUserClass>
void DFS(const std::unique_ptr<Graph>& graph, T* user_class = &DefaultDFSUserClass())
{ // @review: Поиску не обязательно знать про unique_ptr.
  // @review: Естественнее принимать граф по константной ссылке.

    size_t number_of_vertices = graph->GetNumberOfVertices();
    
    std::vector<colors> color(number_of_vertices, WHITE);

    std::vector<std::vector<size_t> > incidence_lists;
    incidence_lists.resize(number_of_vertices);

    std::vector<std::vector<size_t>::iterator > incidence_iterator;
    incidence_iterator.resize(number_of_vertices);

    std::stack<size_t> vertex_stack;

    for (size_t start_vertex = 0; start_vertex < number_of_vertices; ++start_vertex) 
        if (color[start_vertex] == WHITE) {
            vertex_stack.push(start_vertex);        
            DFSStep(graph, user_class, &color, &incidence_lists, &incidence_iterator, &vertex_stack);
        }
}
