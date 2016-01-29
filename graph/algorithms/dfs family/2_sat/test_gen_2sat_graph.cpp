#include <memory>
#include <vector>
#include <set>

#include "graph.h"
#include "random_functions.h"
#include "2sat_solution.h"

void GenRandomListOfDisjunct(
    size_t number_of_variables,
    std::vector<int>* first_argument,
    std::vector<int>* second_argument)
{
    size_t number_of_disjunct = Rand<size_t>(0, number_of_variables);

    for (size_t i = 0; i < number_of_disjunct; ++i)
    {
        int first_variable = Rand<int>(1, number_of_variables + 1);
        int second_variable = Rand<int>(1, number_of_variables + 1);

        if (RandBool())
            first_variable = -first_variable;
        if (RandBool())
            second_variable = -second_variable;

        first_argument->push_back(first_variable);
        second_argument->push_back(second_variable);
    }
}

void Check2SatGraph(
    const Graph& graph,
    size_t number_of_variables,
    const std::vector<int>& first_argument,
    const std::vector<int>& second_argument)
{
    std::set<std::pair<int, int> > set_of_disjunct;

    for (size_t i = 0; i < first_argument.size(); ++i)
    {
        set_of_disjunct.insert(std::pair<int, int>(first_argument[i], second_argument[i]));
        set_of_disjunct.insert(std::pair<int, int>(second_argument[i], first_argument[i]));
    }

    for (size_t vertex = 0; vertex < graph.GetNumberOfVertices(); ++vertex)
    {
        std::vector<size_t> incidence_list = graph.GetIncidenceList(vertex);
        for (size_t incidence_vertex_index = 0; incidence_vertex_index < incidence_list.size();
            ++incidence_vertex_index)
        {
            //a->b=!a|b=b|!a
            size_t incidence_vertex = incidence_list[incidence_vertex_index];
            if (set_of_disjunct.find(std::pair<int, int>(-GetVariable(vertex), GetVariable(incidence_vertex))) ==
                set_of_disjunct.end() &&
                set_of_disjunct.find(std::pair<int, int>(GetVariable(incidence_vertex), -GetVariable(vertex))) ==
                set_of_disjunct.end())
                throw std::runtime_error("Error on TestGen2SatGraph");
        }
    }
}

void TestGen2SatGraph()
{
    size_t number_of_variables = 100;
    size_t number_of_tests = 1000;

    srand(777);
    for (size_t test = 0; test < number_of_tests; ++test)
    {
        std::vector<int> first_argument, second_argument;
        GenRandomListOfDisjunct(number_of_variables, 
            &first_argument, &second_argument);

        std::unique_ptr<Graph> graph = Gen2SatGraph(2 * number_of_variables, 
            first_argument, second_argument);

        Check2SatGraph(*graph, number_of_variables, first_argument, second_argument);
    }
}
