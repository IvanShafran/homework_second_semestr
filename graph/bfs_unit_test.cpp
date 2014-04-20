#include <exception>
#include <vector>

#include "bfs.h"

void BFSUnitTest()
{
    std::unique_ptr<Graph> graph1 = MakeCompactGraph(1, {}, {});
    if (BFS(graph1, 0) != std::vector<int>({ 0 }))
        throw std::runtime_error("Error on BFSUnitTest");

    std::unique_ptr<Graph> graph2 = MakeCompactGraph(3, { 0 }, { 1 });
    if (BFS(graph2, 0) != std::vector<int>({ 0, 1, -1 }))
        throw std::runtime_error("Error on BFSUnitTest");

    std::unique_ptr<Graph> graph3 = MakeCompactGraph(3, { 0, 1 }, { 1, 2 });
    if (BFS(graph3, 0) != std::vector<int>({ 0, 1, 2 }))
        throw std::runtime_error("Error on BFSUnitTest");

    std::unique_ptr<Graph> graph4 
        = MakeCompactGraph(6, { 0, 1, 2, 3, 4, 5 }, { 1, 2, 3, 4, 5, 0 });
    if (BFS(graph4, 0) != std::vector<int>({ 0, 1, 2, 3, 4, 5 }))
        throw std::runtime_error("Error on BFSUnitTest");

    std::unique_ptr<Graph> graph5 
        = MakeCompactGraph(7, { 0, 0, 1, 1, 4 }, { 1, 4, 2, 3, 5 });
    if (BFS(graph5, 0) != std::vector<int>({ 0, 1, 2, 2, 1, 2, -1}))
        throw std::runtime_error("Error on BFSUnitTest");

    std::unique_ptr<Graph> graph6 
        = MakeCompactGraph(10, { 0, 0, 1, 1, 3, 2, 2, 5, 6, 3, 8 }, 
            { 1, 2, 3, 2, 4, 4, 5, 6, 7, 8, 4 });
    if (BFS(graph6, 1) != std::vector<int>({ -1, 0, 1, 1, 2, 2, 3, 4, 2, -1 }))
        throw std::runtime_error("Error on BFSUnitTest");

    std::unique_ptr<Graph> graph7 
        = MakeCompactGraph(7, { 0, 0, 1, 1, 2, 2 }, { 1, 2, 3, 4, 5, 6 });
    if (BFS(graph7, 0) != std::vector<int>({ 0, 1, 1, 2, 2, 2, 2 }))
        throw std::runtime_error("Error on BFSUnitTest");
}
