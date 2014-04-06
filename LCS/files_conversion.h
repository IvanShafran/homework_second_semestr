#include <fstream>
#include <map>
#include <vector>
#include <string>

#include "longest_common_subsequence.h"

// @review: Будет нагляднее если разделить чтение строк и их оцифровку:
// @review:   std::vector<std::string> readFile(const std::string& filename);
// @review:   std::vector<size_t> integrize(const std::vector<std::string>& sequence,
// @review:                                 std::map<std::string, size_t>* string_map);
// @review: ?
void IntegrizeFile(std::ifstream* file, std::vector<size_t>* sequence,
    std::map<std::string, size_t>* get_key,
    std::vector<std::string>* get_string, size_t* key)
{
    while (!file->eof() && !file->fail()) {
        std::string line;
        std::getline(*file, line); // @review: Состояние потока нужно проверять после операции чтения.

        if (get_key->find(line) == get_key->end()) { // @review: Оцифровку строк лучше вынести в самостоятельную функцию.
            (*get_key)[line] = *key;
            get_string->push_back(line);
            (*key)++;
        }

        sequence->push_back((*get_key)[line]);
    }

    // @review: Ошибки ввод-вывода вывода нужно обрабатывать чуть более системно.
    // @review: Пример того, как это сделать можно найти здесь:
    // @review:   http://gehrcke.de/2011/06/reading-files-in-c-using-ifstream-dealing-correctly-with-badbit-failbit-eofbit-and-perror/
    if (file->fail() && !file->eof())
        throw std::runtime_error("Error on ReadFile: Failure reading file");
}

template <class Iterator>
void WriteLine(std::ofstream& file, const std::vector<std::string>& get_string,
    Iterator iterator, std::string addition)
{
    file << addition << get_string[*iterator] << std::endl;
}

// @review: Как-то много аргументов. Давайте заменим const std::vector<size_t>& first_sequence
// @review: на const std::string и уберем get_string.
void WriteConversion(std::string filename,  // @review: Составные объекты, которые не планируется менять, лучше принимать по константной ссылке.
    const std::vector<size_t>& first_sequence,
    const std::vector<size_t>& second_sequence,
    const std::vector<size_t>& subsequence,
    const std::vector<std::string>& get_string)
{
    std::ofstream file(filename);

    auto first_iterator = first_sequence.begin();
    auto second_iterator = second_sequence.begin();
    auto subsequence_iterator = subsequence.begin();

    while (first_iterator != first_sequence.end() &&
        second_iterator != second_sequence.end() &&
        subsequence_iterator != subsequence.end()) {

        if (*first_iterator == *second_iterator
            && *second_iterator == *subsequence_iterator) {
            WriteLine(file, get_string, first_iterator, "");
            first_iterator++;
            second_iterator++;
            subsequence_iterator++;
        }
        else if (*second_iterator == *subsequence_iterator) {
            WriteLine(file, get_string, first_iterator, "-");
            first_iterator++;
        }
        else {
            WriteLine(file, get_string, second_iterator, "+");
            second_iterator++;
        }
    }

    if (subsequence_iterator != subsequence.end())
        throw std::logic_error("WriteConversion: Wrong common subsequence");

    while (first_iterator != first_sequence.end()) {
        WriteLine(file, get_string, first_iterator, "-");
        first_iterator++;
    }

    while (second_iterator != second_sequence.end()) {
        WriteLine(file, get_string, second_iterator, "+");
        second_iterator++;
    }
}

// @review: В названии функции не хватает глагола.
void FilesConverison(std::string first_filename, std::string second_filename,
                     std::string difference_filename)
{
    // @review: Если вместо имен файлов принимать потоки:
    // @review:   std::istream& first_file_istream,
    // @review:   std::istream& second_file_istream,
    // @review:   std::ostream& result_ostream
    // @review: то в тестах можно будет воспользоваться потоками
    // @review:   std::istringstream и std::ostringstream
    // @review: И настоящие файлы не потребуются.
    std::ifstream first_file(first_filename);
    std::ifstream second_file(second_filename);

    std::map<std::string, size_t> get_key;
    std::vector<std::string> get_string;

    std::vector<size_t> first_sequence;
    std::vector<size_t> second_sequence;
    size_t key = 0;

    IntegrizeFile(&first_file, &first_sequence, &get_key, &get_string, &key);
    IntegrizeFile(&second_file, &second_sequence, &get_key, &get_string, &key);

    std::vector<size_t> common_subsequence =
        LCSGetSubsequence(first_sequence, second_sequence);

    WriteConversion(difference_filename, first_sequence, second_sequence,
        common_subsequence, get_string);
}
