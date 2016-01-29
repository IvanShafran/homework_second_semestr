#pragma once

#include <memory>
#include <vector>
#include <map>

#include "graph.h"
#include "Tarjan's_strongly_connected_components_algorithm.h"
#include "condense_graph.h"

namespace {

    size_t GetVertex(int variable)
    {
        if (variable > 0)
            return (variable - 1) * 2;
        else
            return (abs(variable) - 1) * 2 + 1;
    }

    int GetVariable(size_t vertex)
    {
        if (vertex % 2 == 0)
            return (vertex / 2) + 1;
        else
            return -static_cast<int>((((vertex - 1) / 2) + 1));
    }

    std::vector<Edge> Gen2SatEdges(
        const std::vector<int>& edge_begin_variable,
        const std::vector<int>& edge_end_variable)
    {
        std::vector<Edge> edges;
        for (size_t variable_index = 0; variable_index < edge_begin_variable.size();
            ++variable_index)
            edges.push_back(Edge(GetVertex(edge_begin_variable[variable_index]),
                GetVertex(edge_end_variable[variable_index])));
        return edges;
    }

    void GenEdgesVariable(
        const std::vector<int>& first_argument,
        const std::vector<int>& second_argument,
        std::vector<int>* edge_begin_variable,
        std::vector<int>* edge_end_variable)
    {
        for (size_t index = 0; index < first_argument.size();
            ++index)
        {
            edge_begin_variable->push_back(-first_argument[index]);
            edge_end_variable->push_back(second_argument[index]);

            edge_begin_variable->push_back(-second_argument[index]);
            edge_end_variable->push_back(first_argument[index]);
        }
    }

    std::unique_ptr<Graph> Gen2SatGraph(
        size_t number_of_variables,
        const std::vector<int>& first_argument,
        const std::vector<int>& second_argument)
    {
        std::vector<int> edge_begin_variable, edge_end_variable;
        GenEdgesVariable(first_argument, second_argument,
            &edge_begin_variable, &edge_end_variable);

        std::vector<Edge> edges = Gen2SatEdges(edge_begin_variable, edge_end_variable);

        //every variable has two vertices
        return MakeCompactGraph(2 * number_of_variables, edges);
    }

    bool CheckExistenceOf2SatSolution(
        size_t number_of_variables,
        const std::vector<size_t>& component_id_of_vertex)
    {
        for (int variable = 1; variable <= number_of_variables; ++variable)
        if (component_id_of_vertex[GetVertex(variable)] ==
            component_id_of_vertex[GetVertex(-variable)])
            return false;

        return true;
    }

    std::vector<bool> Get2SatSolution(
        size_t number_of_variables,
        const std::vector<size_t>& component_id_of_vertex)
    {
        std::vector<bool> solution;
        //variables - 1..number_of_variables, solution[0] - unnecessary
        solution.push_back(false);

        //After Tarjan algotithm components are in reverse topological order 
        for (int variable = 1; variable <= number_of_variables; ++variable)
        if (component_id_of_vertex[GetVertex(variable)] <
            component_id_of_vertex[GetVertex(-variable)])
            solution.push_back(true);
        else
            solution.push_back(false);

        return solution;
    }

    std::vector<bool> Get2SatSolution(
        size_t number_of_variables,
        const std::vector<int>& first_argument,
        const std::vector<int>& second_argument,
        bool* has_a_solution)
    {
        std::unique_ptr<Graph> graph_2sat = Gen2SatGraph(number_of_variables,
            first_argument, second_argument);

        std::vector<std::vector<size_t> > component =
            GetStronglyConnectedComponents(*graph_2sat);

        std::vector<size_t> component_id_of_vertex =
            GetComponentIdOfVertexVector(2 * number_of_variables,
            component);

        (*has_a_solution) = CheckExistenceOf2SatSolution(number_of_variables,
            component_id_of_vertex);

        if (!(*has_a_solution))
            return std::vector<bool>();

        return Get2SatSolution(number_of_variables, component_id_of_vertex);
    }

}
