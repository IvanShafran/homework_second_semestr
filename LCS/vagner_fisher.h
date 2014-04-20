#pragma once

template <class Sequence>
int VagnerFisher(const Sequence& first_vector, const Sequence& second_vector)
// @review: В названии функции стоит отразить. что она делает. Тогда читателю не придётся
// @review: искать описание алгоритма, чтобы выяснить его назначение.
{
    int first_size = first_vector.size();
    int second_size = second_vector.size();
    std::vector<int> previous_line;

    for (int i = 0; i <= first_size; i++) {
        // @review: Однобуквенные переменных подходят для коротких циклов без вложений.
        // @review: В более сложных циклах лучше пользоваться более подробными названиями.
        std::vector<int> line;
        for (int j = 0; j <= second_size; j++)
        if (j == 0 || i == 0) {
            line.push_back(std::max(i, j));
        }
        else {
            if (first_vector[i - 1] == second_vector[j - 1])
                line.push_back(std::min(previous_line[j - 1],
                std::min(line[j - 1], previous_line[j]) + 1));
            else
                line.push_back(std::min(line[j - 1], previous_line[j]) + 1);
        }

        swap(previous_line, line);
    }

    return previous_line[second_size];
}
