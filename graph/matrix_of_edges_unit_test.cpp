#include <Windows.h>
#include <memory>

#include "graph.h"
#include "memory_monitor.h"

void TestEmptyGraphMatrixOfEdges()
{
    std::vector<size_t> edge_begin, edge_end;
    std::unique_ptr<Graph> empty_graph = MakeCompactGraph(1, edge_begin, edge_end);

    if (empty_graph->GetNumberOfVertices() != 1)
        throw std::runtime_error("Error on TestEmptyGraphListOfEdges: wrong number of vertices");

    std::vector<size_t> list_indence = empty_graph->GetIncidenceList(0);
    if (list_indence.size() != 0)
        throw std::runtime_error("Error on TestEmptyGraphListOfEdges: wrong indence list");
}

void SmallUnitTestGraphMatrixOfEdges()
{
    std::vector<size_t> edge_begin = { 0, 1, 2, 2, 3, 4 };
    std::vector<size_t> edge_end = { 1, 2, 0, 3, 4, 2 };
    std::unique_ptr<Graph> graph = MakeCompactGraph(5, edge_begin, edge_end);

    if (graph->GetNumberOfVertices() != 5)
        throw std::runtime_error("Error on SmallUnitTestGraphListOfEdges: wrong number of vertices");

    if (graph->GetIncidenceList(2).size() != 2)
        throw std::runtime_error("Error on SmallUnitTestGraphListOfEdges: wrong incidence list");

    if (graph->GetIncidenceList(2)[0] != 0 || graph->GetIncidenceList(2)[1] != 3)
        throw std::runtime_error("Error on SmallUnitTestGraph: wrong incidence list");
}

void TestNumbersOfVerticesMatrixOfEdges()
{
    std::vector<size_t> edge_begin, edge_end;
    std::unique_ptr<Graph> graph1 = MakeCompactGraph(1, edge_begin, edge_end);
    std::unique_ptr<Graph> graph2 = MakeCompactGraph(7, edge_begin, edge_end);
    std::unique_ptr<Graph> graph3 = MakeCompactGraph(100, edge_begin, edge_end);
    std::unique_ptr<Graph> graph4 = MakeCompactGraph(1000, edge_begin, edge_end);
    // @review: Из названия метода можно предположить. что тестируется MatrixOfEdges. Но при этом вызывается
    // @review: функция MakeCompactGraph(). Это очень странно!
    // @review: По идее, вы должены пользоваться конструктором тестируемого класса напрямую.

    if (graph1->GetNumberOfVertices() != 1)
        throw std::runtime_error("Error on TestNumbersOfVerticesListOfEdges");
    if (graph2->GetNumberOfVertices() != 7)
        throw std::runtime_error("Error on TestNumbersOfVerticesListOfEdges");
    if (graph3->GetNumberOfVertices() != 100)
        throw std::runtime_error("Error on TestNumbersOfVerticesListOfEdges");
    if (graph4->GetNumberOfVertices() != 1000)
        throw std::runtime_error("Error on TestNumbersOfVerticesListOfEdges");
}

void TestIncidenceListMatrixOfEdges()
{
    std::vector<size_t> edge_begin = { 0, 0, 0, 0, 0 }, edge_end = { 1, 2, 3, 4, 5 };
    std::unique_ptr<Graph> graph = MakeCompactGraph(6, edge_begin, edge_end);

    if (graph->GetIncidenceList(0) != std::vector<size_t>({ 1, 2, 3, 4, 5 }))
        throw std::runtime_error("Error on TestIncidenceListListOfEdges");

}

void MatrixOfEdgesUnitTest()
{
    MemoryMonitor memory_monitor;
    TestEmptyGraphMatrixOfEdges();
    if (memory_monitor.CheckMemoryLeaks())
        throw std::runtime_error("Memory leaks on ListOfEdgesUnitTest"); // @review: Текст сообщения определённо относился к другой функции.

    SmallUnitTestGraphMatrixOfEdges();
    if (memory_monitor.CheckMemoryLeaks())
        throw std::runtime_error("Memory leaks on ListOfEdgesUnitTest");

    TestNumbersOfVerticesMatrixOfEdges();
    if (memory_monitor.CheckMemoryLeaks())
        throw std::runtime_error("Memory leaks on ListOfEdgesUnitTest");

    TestIncidenceListMatrixOfEdges();
    if (memory_monitor.CheckMemoryLeaks())
        throw std::runtime_error("Memory leaks on ListOfEdgesUnitTest");
}
