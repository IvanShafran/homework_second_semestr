#include <iostream>
#include <stdexcept>

#include "graph_unit_test.h"
#include "graph_test.h"
#include "bfs_unit_test.h"
#include "topological_sort_test.h"

int main()
{
    try {
        //GraphTest();
#ifndef _DEBUG
        GraphUnitTest();
        BFSUnitTest();
        TopologicalSortTest();
#endif
    }
    catch (const std::exception& ex) {
        std::cerr << "Exception: " << ex.what() << std::endl;
        system("PAUSE");
        return -1;
    }    
}
