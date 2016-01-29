#include <vector>

#include "condense_graph.h"

void TestGetComponentOfVerticesVector()
{
    //first test: correct result
    {
        std::vector<std::vector<size_t> > component;
        component.push_back({ 3, 4 });
        component.push_back({ 2, 1 });
        component.push_back({ 0, 5 });

        std::vector<size_t> result = GetComponentIdOfVertexVector(6, component);
        if (result[0] != result[5] || result[1] != result[2] || result[3] != result[4] ||
            result[0] == result[1] || result[0] == result[3] || result[1] == result[3])
            throw std::runtime_error("Error on TestGetComponentOfVerticesVector");
    }
    //second test: test exception
    {
        std::vector<std::vector<size_t> > component;
        component.push_back({ 1, 0 });
        component.push_back({ 1, });

        try {
            std::vector<size_t> result = GetComponentIdOfVertexVector(2, component);
            throw std::runtime_error("test error");
        }
        catch (const std::exception& ex)
        {
            std::string error_text = ex.what();
            if (error_text == "test error")
                throw std::runtime_error("Error on TestGetComponentOfVerticesVector");
        }
    }
    //third test: test exception
    {
        std::vector<std::vector<size_t> > component;
        component.push_back({ 1, });

        try {
            std::vector<size_t> result = GetComponentIdOfVertexVector(2, component);
            throw std::runtime_error("test error");
        }
        catch (const std::exception& ex)
        {
            std::string error_text = ex.what();
            if (error_text == "test error")
                throw std::runtime_error("Error on TestGetComponentOfVerticesVector");
        }
    }
}
