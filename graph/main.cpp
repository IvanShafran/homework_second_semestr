#include <iostream>
#include <stdexcept>
#include <vector>

#include "list_of_edges_unit_test.h"
#include "matrix_of_edges_unit_test.h"
#include "test_make_compact_graph.h"
#include "dfs_unit_test.h"
#include "bfs_unit_test.h"
#include "topological_sort_test.h"
#include "graph_memory_test.h"
#include "graph_time_test.h"

int main()
{
    try {
//#ifdef _DEBUG
//        ListOfEdgesUnitTest();
//        std::cout << "ListOfEdgesUnitTest OK" << std::endl;
//        MatrixOfEdgesUnitTest();
//        std::cout << "MatrixOfEdgesUnitTest OK" << std::endl;
//        TestMakeCompactGraph();
//        std::cout << "TestMakeCompactGraph OK" << std::endl;
//        GraphMemoryTest();
//        std::cout << "GraphMemoryTest OK" << std::endl;
//#endif
//        
//#ifndef _DEBUG
//        DFSUnitTest();
//        std::cout << "DFSUnitTest OK" << std::endl;
//        BFSUnitTest();
//        std::cout << "BFSUnitTest OK" << std::endl;
//        TopologicalSortTest();
//        std::cout << "TopologicalSortTest OK" << std::endl;
//        GraphTimeTest();
//        std::cout << "GraphTimeTest OK" << std::endl;
//#endif
        system("PAUSE");
        return 0;
    }
    catch (const std::exception& ex) {
        std::cerr << "Exception: " << ex.what() << std::endl;
        system("PAUSE");
        return -1;
    }
}
