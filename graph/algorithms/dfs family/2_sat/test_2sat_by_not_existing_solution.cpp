#include <vector>

#include "2sat_solution.h"
#include "random_functions.h"

void GenDisjunctsForNotExistingSolution(size_t number_of_variables,
    std::vector<int>* first_argument,
    std::vector<int>* second_argument)
{
    //gen cycle which doesn't have solution like (a | !b) & (b | !c) & (!a | !a) & (c & c)
    size_t cycle_length = 100;
    std::vector<int> element_set;
    for (int i = 1; i <= number_of_variables; ++i)
        element_set.push_back(i);
    std::vector<int> cycle_element = RandSequence(cycle_length, element_set);

    for (size_t i = 0; i < (cycle_length - 1); ++i)
    {
        first_argument->push_back(cycle_element[i]);
        second_argument->push_back(-cycle_element[i + 1]);
    }

    first_argument->push_back(-cycle_element[0]);
    second_argument->push_back(-cycle_element[0]);

    first_argument->push_back(cycle_element[cycle_length - 1]);
    second_argument->push_back(cycle_element[cycle_length - 1]);
}

void Test2SatByNotExistingSolution()
{
    size_t number_of_tests = 1000;
    size_t number_of_variables = 50;
    srand(777);
    for (size_t test = 0; test < number_of_tests; ++test)
    {
        std::vector<int> first_argument, second_argument;
        GenDisjunctsForNotExistingSolution(number_of_variables,
            &first_argument, &second_argument);

        bool has_solution;
        std::vector<bool> solution = Get2SatSolution(number_of_variables,
            first_argument, second_argument, &has_solution);

        if (has_solution)
            throw std::runtime_error("Error on Test2SatByNotExistingSolution");
    }
}
