#include <Windows.h>
#include <memory>

#include "graph.h"
#include "memory_monitor.h"

void TestEmptyGraphListOfEdges()
{
    std::vector<Edge> edges;
    std::unique_ptr<Graph> empty_graph(new ListOfEdges(1, edges));

    if (empty_graph->GetNumberOfVertices() != 1)
        throw std::runtime_error("Error on TestEmptyGraphListOfEdges: wrong number of vertices");

    std::vector<size_t> list_indence = empty_graph->GetIncidenceList(0);
    if (list_indence.size() != 0)
        throw std::runtime_error("Error on TestEmptyGraphListOfEdges: wrong indence list");
}

void SmallUnitTestGraphListOfEdges()
{
    std::vector<Edge> edges = { { 0, 1 }, { 1, 2 }, { 2, 0 }, { 2, 3 }, { 3, 4 }, { 4, 2 } };
    std::unique_ptr<Graph> graph(new ListOfEdges(5, edges));

    if (graph->GetNumberOfVertices() != 5)
        throw std::runtime_error("Error on SmallUnitTestGraphListOfEdges: wrong number of vertices");

    if (graph->GetIncidenceList(2).size() != 2)
        throw std::runtime_error("Error on SmallUnitTestGraphListOfEdges: wrong incidence list");

    if (graph->GetIncidenceList(2)[0] != 0 || graph->GetIncidenceList(2)[1] != 3)
        throw std::runtime_error("Error on SmallUnitTestGraphListOfEdges: wrong incidence list"); 
}

void TestNumbersOfVerticesListOfEdges()
{
    std::vector<Edge> edges;
    std::unique_ptr<Graph> graph1(new ListOfEdges(1, edges));
    std::unique_ptr<Graph> graph2(new ListOfEdges(7, edges));
    std::unique_ptr<Graph> graph3(new ListOfEdges(100, edges));
    std::unique_ptr<Graph> graph4(new ListOfEdges(1000, edges));

    if (graph1->GetNumberOfVertices() != 1)
        throw std::runtime_error("Error on TestNumbersOfVerticesListOfEdges");
    if (graph2->GetNumberOfVertices() != 7)
        throw std::runtime_error("Error on TestNumbersOfVerticesListOfEdges");
    if (graph3->GetNumberOfVertices() != 100)
        throw std::runtime_error("Error on TestNumbersOfVerticesListOfEdges");
    if (graph4->GetNumberOfVertices() != 1000)
        throw std::runtime_error("Error on TestNumbersOfVerticesListOfEdges");
}

void TestIncidenceListListOfEdges()
{
    std::vector<Edge> edges = { { 0, 1 }, { 0, 2 }, { 0, 3 }, 
        { 0, 4 }, { 0, 5 } };
    std::unique_ptr<Graph> graph(new ListOfEdges(6, edges));

    if (graph->GetIncidenceList(0) != std::vector<size_t>({ 1, 2, 3, 4, 5 }))
        throw std::runtime_error("Error on TestIncidenceListListOfEdges");

}

void ListOfEdgesUnitTest()
{
    MemoryMonitor memory_monitor;
    TestEmptyGraphListOfEdges();
    if (memory_monitor.CheckMemoryLeaks())
        throw std::runtime_error("Memory leaks on ListOfEdgesUnitTest");

    SmallUnitTestGraphListOfEdges();
    if (memory_monitor.CheckMemoryLeaks())
        throw std::runtime_error("Memory leaks on ListOfEdgesUnitTest");

    TestNumbersOfVerticesListOfEdges();
    if (memory_monitor.CheckMemoryLeaks())
        throw std::runtime_error("Memory leaks on ListOfEdgesUnitTest");

    TestIncidenceListListOfEdges(); 
    if (memory_monitor.CheckMemoryLeaks())
        throw std::runtime_error("Memory leaks on ListOfEdgesUnitTest");
}
