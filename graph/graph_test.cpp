#include <exception>
#include <string>
#include <vector>
#include <functional>
#include <fstream>
#include <Windows.h>
#include <set>

#include "graph.h"
#include "dfs.h"
#include "gen_random_graph.h"
#include "topological_sort_test.h"
#include "random_functions.h"


// @review: Для тестирования графа необходимо и достаточно проверить:
// @review: 1. Класс ListOfEdges / MatrixOfEdges правильно инициализируется по списку ребер.
// @review: 2. Все методы ListOfEdges / MatrixOfEdges работают правильно.
// @review: 3. В классе ListOfEdges / MatrixOfEdges не течет память.
// @review: 4. Фабричный метод правильно выбирает представление в зависимости от данных.

// @review: Тесты с DFS/BFS стоит перенести в другие файлы.


Graph GetFullGraph(size_t* number_of_vertices, size_t* number_of_edges)
{
    *number_of_edges = 0;
    std::vector<size_t> edge_begin, edge_end;

    for (size_t vertex = 0; vertex < *number_of_vertices; ++vertex)
    for (size_t incidence_vertex = 0; incidence_vertex < *number_of_vertices; 
        ++incidence_vertex)
    if (vertex != incidence_vertex) {
        edge_begin.push_back(vertex);
        edge_end.push_back(incidence_vertex);
        ++(*number_of_edges);
    }

    Graph graph(*number_of_vertices, edge_begin, edge_end);
    return graph;
}

Graph GetEmptyGraph(size_t* number_of_vertices, size_t* number_of_edges)
{
    *number_of_edges = 0;
    return Graph(*number_of_vertices, {}, {});
}

Graph GetRandomGraphFunction(size_t* max_number_of_vertices, size_t* number_of_edges)
{
    return GetRandomGraph(*max_number_of_vertices, 2 * (*max_number_of_vertices), 
        max_number_of_vertices, number_of_edges);
}

Graph GetFunctionalGraph(size_t* number_of_vertices, size_t* number_of_edges)
{
    size_t number_of_incidence_vertices = Rand(1, min(*number_of_vertices - 1, 10));
    
    *number_of_edges = *number_of_vertices * number_of_incidence_vertices;

    std::vector<size_t> edge_begin, edge_end;
    for (size_t vertex = 0; vertex < *number_of_vertices; ++vertex) {
        std::set<size_t> used;
        used.insert(vertex);
        for (size_t k = 0; k < number_of_incidence_vertices; ++k)
        {
            edge_begin.push_back(vertex);

            size_t end = Rand(0, *number_of_vertices);
            while (used.find(end) != used.end())
                end = Rand(0, *number_of_vertices);

            edge_end.push_back(end);
        }
    }

    return Graph(*number_of_vertices, edge_begin, edge_end);
}

Graph GetAcyclicGraph(size_t* number_of_vertices, size_t* number_of_edges)
{
    std::vector<size_t> order;
    for (size_t i = 0; i < *number_of_vertices; ++i)
        order.push_back(i);
    
    RandomShuffle(&order);

    std::set<Edge> edges;
    size_t max_number_of_edges = 2 * (*number_of_vertices);
    *number_of_edges = 0;
    std::vector<size_t> edge_begin, edge_end;
    
    for (size_t i = 0; i < max_number_of_edges; ++i) {
        size_t begin_index = Rand(0, *number_of_vertices - 1);
        size_t end_index = Rand(begin_index, *number_of_vertices);
        size_t begin = order[begin_index];
        size_t end = order[end_index];

        if (edges.find(Edge(begin, end))
            == edges.end())
        {
            ++(*number_of_edges);
            edges.insert(Edge(begin, end));
            edge_begin.push_back(begin);
            edge_end.push_back(end);
        }
    }

    return Graph(*number_of_vertices, edge_begin, edge_end);
}



#ifdef _DEBUG

// @review: Почему бы не завести функцию выполняющую тест на фиксированном наборе вершин и дуг.
// @review: И затем уже вызывать её с разными наборами данных.
void GraphMemoryTest(size_t number_of_tests, size_t number_of_vertices_step,  
    const std::function<Graph(size_t*, size_t*)>& GetGraph, 
    std::string graph_type)
{
    std::ofstream graph_memory_test_log(".\\memory_logs\\" + graph_type + "_memory_test.log");
    
    for (size_t test = 0; test < number_of_tests; ++test)
    {
        // @review: Логику отвечающую за поиск утечек стоит вынести в отдельный класс:
        // @review:   MemoryMonitor monitor;
        // @review:   ... // Do some computations.
        // @review:   monitor.findLeaks();
        _CrtMemState memory_state_before_test;
        _CrtMemCheckpoint(&memory_state_before_test);

        {
            size_t number_of_vertices = (test + 1) * number_of_vertices_step;
            size_t number_of_edges;
            
            _CrtMemState memory_state_before_creation;
            _CrtMemCheckpoint(&memory_state_before_creation);

            //number_of_vertices changes on RandTest
            Graph graph = GetGraph(&number_of_vertices, &number_of_edges);

            _CrtMemState memory_state_after_creation;
            _CrtMemCheckpoint(&memory_state_after_creation);

            _CrtMemState graph_memory;
            _CrtMemDifference(&graph_memory, &memory_state_before_creation, 
                &memory_state_after_creation);

            graph_memory_test_log << "Size of used memory by " + graph_type 
                + " is " + std::to_string(graph_memory.lTotalCount) + " bytes " 
                + "on " + std::to_string(number_of_vertices) + " vertices and " 
                + std::to_string(number_of_edges) + " edges" << std::endl;

        }
        _CrtMemState memory_state_after_test;
        _CrtMemCheckpoint(&memory_state_after_test);
        _CrtMemState memore_difference; // @review: memore -> memory

        if (_CrtMemDifference(&memore_difference, &memory_state_before_test,
            &memory_state_after_test)) {
            throw std::runtime_error("Memory leaks on " + graph_type);
            }
    }
}
#endif

void GraphTimeTest(size_t number_of_tests, size_t number_of_vertices_step,
    const std::function<Graph(size_t*, size_t*)>& GetGraph,
    std::string graph_type)
{
    std::ofstream graph_time_test_log(".\\time_logs\\" + graph_type + "_time_test.log");

    for (size_t test = 0; test < number_of_tests; ++test)
    {
        size_t number_of_vertices = (test + 1) * number_of_vertices_step;
        size_t number_of_edges;

        //number_of_vertices changes on RandTest
        Graph graph = GetGraph(&number_of_vertices, &number_of_edges);

        int time_before_DFS = GetTickCount();

        DFS(graph);

        int time_after_DFS = GetTickCount();

        graph_time_test_log << "Time used by DFS on " + graph_type
            + " with " + std::to_string(number_of_vertices) 
            + " vertices and "
            + std::to_string(number_of_edges) + " edges is " 
            + std::to_string(time_after_DFS - time_before_DFS) + "ms"
            << std::endl;
    }
}

void GraphTest()
{
#ifdef _DEBUG
    GraphMemoryTest(10, 10, GetFullGraph, "full_graph");
    GraphMemoryTest(10, 1000, GetEmptyGraph, "empty_graph");
    srand(777);
    GraphMemoryTest(50, 100, GetRandomGraphFunction, "random_graph");
    GraphMemoryTest(50, 100, GetFunctionalGraph, "functional_graph");
    GraphMemoryTest(20, 100, GetAcyclicGraph, "acyclic_graph");
#endif
    
#ifndef _DEBUG
    GraphTimeTest(5, 1000, GetFullGraph, "full_graph");
    GraphTimeTest(10, 1000, GetEmptyGraph, "empty_graph");
    srand(777);
    GraphTimeTest(100, 100, GetRandomGraphFunction, "random_graph");
    GraphTimeTest(20, 500, GetFunctionalGraph, "functional_graph");
    GraphTimeTest(60, 100, GetAcyclicGraph, "acyclic_graph");
#endif
}
