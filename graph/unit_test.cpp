#include <Windows.h>

#include "graph.h"
#include "check_memory_leaks.h"

void EmptyGraph1()
{
    std::vector<size_t> edge_begin, edge_end;
    Graph empty_graph(1, edge_begin, edge_end);

    if (empty_graph.GetNumberOfVertices() != 1)
        throw std::runtime_error("Error on EmptyGraph1: wrong number of vertices");

    std::vector<size_t> list_indence = empty_graph.GetIncidenceList(0);
    if (list_indence.size() != 0)
        throw std::runtime_error("Error on EmptyGraph1: wrong indence list");
}

void EmptyGraph2()
{
    std::vector<size_t> edge_begin, edge_end;
    Graph empty_graph(10000, edge_begin, edge_end);

    if (empty_graph.GetNumberOfVertices() != 10000)
        throw std::runtime_error("Error on EmptyGraph2: wrong number of vertices");

    std::vector<size_t> list_indence = empty_graph.GetIncidenceList(1000);
    if (list_indence.size() != 0)
        throw std::runtime_error("Error on EmptyGraph2: wrong indence list");
}

void SmallUnitTestGraph()
{
    std::vector<size_t> edge_begin = { 0, 1, 2, 2, 3, 4 };
    std::vector<size_t> edge_end = { 1, 2, 0, 3, 4, 2 };
    Graph graph(5, edge_begin, edge_end);

    if (graph.GetNumberOfVertices() != 5)
        throw std::runtime_error("Error on SmallUnitTestGraph: wrong number of vertices");

    if (graph.GetIncidenceList(2).size() != 2)
        throw std::runtime_error("Error on SmallUnitTestGraph: wrong incidence list");

    if (graph.GetIncidenceList(2)[0] != 0 || graph.GetIncidenceList(2)[1] != 3)
        throw std::runtime_error("Error on SmallUnitTestGraph: wrong incidence list"); 
}

void CheckNumbersOfVertices()
{
    std::vector<size_t> edge_begin, edge_end;
    Graph graph1(1, edge_begin, edge_end);
    Graph graph2(7, edge_begin, edge_end);
    Graph graph3(1000, edge_begin, edge_end);
    Graph graph4(100000, edge_begin, edge_end);

    if (graph1.GetNumberOfVertices() != 1)
        throw std::runtime_error("Error on CheckNumbersOfVertices");
    if (graph2.GetNumberOfVertices() != 7)
        throw std::runtime_error("Error on CheckNumbersOfVertices");
    if (graph3.GetNumberOfVertices() != 1000)
        throw std::runtime_error("Error on CheckNumbersOfVertices");
    if (graph4.GetNumberOfVertices() != 100000)
        throw std::runtime_error("Error on CheckNumbersOfVertices");
}

void UnitTest()
{
    EmptyGraph1();
    CheckMemoryLeak();

    EmptyGraph2();
    CheckMemoryLeak();

    SmallUnitTestGraph();
    CheckMemoryLeak();

    CheckNumbersOfVertices();
    CheckMemoryLeak();
}
