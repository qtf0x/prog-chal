/**
 * @file 03-1_rucksack_reorganization.cpp
 * @author Vincent Marias ( @qtf0x )
 * @date 12/19/2022
 *
 * @brief Advent of Code 2022
 *        Day 3: Rucksack Reorganization [Part 2]
 */

#include <algorithm>
#include <fstream>
#include <iostream>
#include <set>
#include <vector>

constexpr const char* INPUT_FILE{"03_input.txt"};
constexpr size_t GROUP_SIZE{3ul};

std::vector<std::vector<std::set<char>>> readFileInput(std::ifstream& fin);

char commonElement(const std::vector<std::set<char>>& elements);

unsigned getPriority(const char& element);

unsigned
calcPriorityTotal(const std::vector<std::vector<std::set<char>>>& elements);

int main() {
    std::ifstream fin(INPUT_FILE);

    if (fin.fail()) {
        std::cerr << "Failed to open file \"" << INPUT_FILE << "\"\n"
                  << "Shutting down ...\n";
    }

    auto inputs{readFileInput(fin)};

    std::cout << "Read in " << inputs.size() << " inputs.\n";

    auto priorityTotal{calcPriorityTotal(inputs)};

    std::cout << "Sum of priorities of common elements: " << priorityTotal
              << '\n';

    return EXIT_SUCCESS;
}

std::vector<std::vector<std::set<char>>> readFileInput(std::ifstream& fin) {
    std::vector<std::vector<std::set<char>>> inputs;
    std::vector<std::set<char>> nextInput(GROUP_SIZE);
    char nextInputElement{'\0'};

    for (size_t i{0ul}; fin >> nextInputElement;) {
        nextInput.at(i).insert(nextInputElement);
        i += (fin.peek() == '\n');

        if (i == GROUP_SIZE) {
            inputs.push_back(nextInput);
            nextInput.clear();
            nextInput.resize(GROUP_SIZE);
            i = 0ul;
        }
    }

    return inputs;
}

char commonElement(const std::vector<std::set<char>>& elements) {
    std::set<char> intersection, intersection2;

    std::set_intersection(elements.at(0ul).begin(), elements.at(0ul).end(),
                          elements.at(1ul).begin(), elements.at(1ul).end(),
                          std::inserter(intersection, intersection.begin()));

    std::set_intersection(intersection.begin(), intersection.end(),
                          elements.at(2ul).begin(), elements.at(2ul).end(),
                          std::inserter(intersection2, intersection2.begin()));

    return *(intersection2.begin());
}

unsigned getPriority(const char& element) {
    if (element == toupper(element))
        return element - 'A' + static_cast<char>(27);
    else
        return element - 'a' + static_cast<char>(1);
}

unsigned
calcPriorityTotal(const std::vector<std::vector<std::set<char>>>& elements) {
    unsigned priorityTotal{0u};

    for (const auto& element : elements)
        priorityTotal += getPriority(commonElement(element));

    return priorityTotal;
}
