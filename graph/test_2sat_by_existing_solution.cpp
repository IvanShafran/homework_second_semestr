#include <vector>

#include "2sat_solution.h"
#include "random_functions.h"

int GetVariableSign(bool value)
{
    if (value)
        return 1;
    else
        return -1;
}

std::vector<bool> GenDisjunctsForExistingAndOneSolution(
    size_t number_of_variables,
    std::vector<int>* first_argument,
    std::vector<int>* second_argument)
{
    //variables index - 1..number_of_variables
    std::vector<bool> bool_set = { false, true };
    std::vector<bool> variables = RandSequence(number_of_variables + 1, bool_set);
    variables[0] = false;

    first_argument->push_back(GetVariableSign(variables[1]) * 1);
    second_argument->push_back(GetVariableSign(variables[1]) * 1);

    for (int variable = 2; variable <= number_of_variables; ++variable)
    {
        first_argument->push_back(GetVariableSign(variables[variable]) * variable);
        second_argument->push_back(GetVariableSign(!variables[1]) * 1);
    }

    return variables;
}

void Test2SatByExistingSolution()
{
    size_t number_of_tests = 1000;
    size_t number_of_variables = 50;
    srand(777);
    for (size_t test = 0; test < number_of_tests; ++test)
    {
        std::vector<int> first_argument, second_argument;
        std::vector<bool> variables = GenDisjunctsForExistingAndOneSolution(number_of_variables,
            &first_argument, &second_argument);

        bool has_solution;
        std::vector<bool> solution = Get2SatSolution(number_of_variables, 
            first_argument, second_argument, &has_solution);

        if (!has_solution || solution != variables)
            throw std::runtime_error("Error on Test2SatByExistingSolution");
    }
}
