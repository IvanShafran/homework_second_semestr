#include <stdexcept>
#include <vector>
#include <memory>

#include "dfs.h"
#include "graph.h"

class DFSColors : AbstractDFSUserClass {
public:
    std::vector<colors> color_;

    explicit DFSColors(size_t number_of_vertices) : color_(number_of_vertices, WHITE)
    {}

    void BeforeProcessing(size_t vertex)
    {
        color_[vertex] = GREY;
    }

    void ProcessEdge(size_t edge_begin, size_t edge_end, colors end_color)
    {
        // @review: Здесь можно проверить, что ваше знание о цвете вершины не противоречит с end_color.
    }

    void AfterProcessing(size_t vertex)
    {
        color_[vertex] = BLACK;
    }
};

void DFSUnitTestFirst()
{
    std::unique_ptr<Graph> graph = MakeCompactGraph(3, {}, {});

    DFS(graph);
}

void DFSUnitTestSecond()
{
    std::unique_ptr<Graph> graph = MakeCompactGraph(3, {}, {});

    DFSColors colors_class(3);

    DFS(graph, &colors_class);

    if (colors_class.color_ != std::vector<colors>(3, BLACK))
        throw std::runtime_error("Error on DFSUnitTestSecond: DFS wasn't visit all vertices");

}

void DFSUnitTestThird() // @review: Этот тест аналогичен предыдущему.
                        // @review: Общую часть стоит вынести в отдельную функцию.
                        // @review: А потом позвать эту функцию для разных графов.
                        // @review: (у вас даже есть функции для генерации случайных графов).
{
    std::unique_ptr<Graph> graph = MakeCompactGraph(5, {0, 1, 2, 3, 1}, {1, 2, 3, 1, 3});

    DFSColors colors_class(5);

    DFS(graph, &colors_class);

    if (colors_class.color_ != std::vector<colors>(5, BLACK))
        throw std::runtime_error("Error on DFSUnitTestFirst: DFS wasn't visit all vertices");

}

void DFSUnitTest()
{
    DFSUnitTestFirst();
    DFSUnitTestSecond();
    DFSUnitTestThird();
}
