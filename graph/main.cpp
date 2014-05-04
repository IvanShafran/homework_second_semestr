#include <iostream>
#include <stdexcept>
#include <vector>

#include "list_of_edges_unit_test.h"
#include "matrix_of_edges_unit_test.h"
#include "test_make_compact_graph.h"
#include "dfs_test.h"
#include "bfs_unit_test.h"
#include "topological_sort_test.h"
#include "graph_memory_test.h"
#include "graph_time_test.h"
#include "test_get_component_id_of_vertices_vector.h"
#include "test_tarjan_random.h"
#include "test_all_before_6_vertices_graph.h"
#include "stability_test_Tarjan_algorithm.h"
#include "test_condense_graph.h"
#include "test_gen_2sat_graph.h"
#include "test_2sat_by_existing_solution.h"
#include "test_2sat_by_not_existing_solution.h"

int main()
{
    try {
        ListOfEdgesUnitTest();
        std::cout << "ListOfEdgesUnitTest OK" << std::endl;
        MatrixOfEdgesUnitTest();
        std::cout << "MatrixOfEdgesUnitTest OK" << std::endl;
#ifdef _DEBUG
        TestMakeCompactGraph();
        std::cout << "TestMakeCompactGraph OK" << std::endl;
        GraphMemoryTest();
        std::cout << "GraphMemoryTest OK" << std::endl;
#endif
        GraphTimeTest();
        std::cout << "GraphTimeTest OK" << std::endl;
        DFSTest();
        std::cout << "DFSUnitTest OK" << std::endl;
        BFSUnitTest();
        std::cout << "BFSUnitTest OK" << std::endl;
        TopologicalSortTest();
        std::cout << "TopologicalSortTest OK" << std::endl;
        TestTarjanRandom();
        std::cout << "TestTarjanRandom OK" << std::endl;
        TestAllBefore6VerticesGraph();
        std::cout << "TestAllBefore6VerticesGraph OK" << std::endl;
        StabilityTestTarjanAlgorithm();
        std::cout << "StabilityTestTarjanAlgorithm OK" << std::endl;
        TestGetComponentOfVerticesVector();
        std::cout << "TestGetComponentOfVerticesVector OK" << std::endl;
        TestCondenseGraph();
        std::cout << "TestCondenseGraph OK" << std::endl;
        TestGen2SatGraph();
        std::cout << "TestGen2SatGraph OK" << std::endl;
        Test2SatByExistingSolution();
        std::cout << "Test2SatByExistingSolution OK" << std::endl;
        Test2SatByNotExistingSolution();
        std::cout << "Test2SatByNotExistingSolution OK" << std::endl;
        system("PAUSE");
        return 0;
    }
    catch (const std::exception& ex) {
        std::cerr << "Exception: " << ex.what() << std::endl;
        system("PAUSE");
        return -1;
    }
}
