/**
 * @file 03-1_rucksack_reorganization.cpp
 * @author Vincent Marias ( @qtf0x )
 * @date 12/19/2022
 *
 * @brief Advent of Code 2022
 *        Day 3: Rucksack Reorganization [Part 1]
 */

#include <algorithm>
#include <fstream>
#include <iostream>
#include <set>
#include <vector>

constexpr const char* INPUT_FILE{"03_input.txt"};

std::vector<std::pair<std::set<char>, std::set<char>>>
readFileInput(std::ifstream& fin);

char commonElement(const std::pair<std::set<char>, std::set<char>>& elements);

unsigned getPriority(const char& element);

unsigned calcPriorityTotal(
    const std::vector<std::pair<std::set<char>, std::set<char>>>& elements);

int main() {
    std::ifstream fin(INPUT_FILE);

    if (fin.fail()) {
        std::cerr << "Failed to open file \"" << INPUT_FILE << "\"\n"
                  << "Shutting down ...\n";
    }

    auto inputs{readFileInput(fin)};

    std::cout << "Read in " << inputs.size() << " inputs.\n";

    // for (const auto& input : inputs) {
    //     std::cout << '{';

    //     for (const auto& nextChar : input.first)
    //         std::cout << nextChar << ", ";

    //     std::cout << "}, {";

    //     for (const auto& nextChar : input.second)
    //         std::cout << nextChar << ", ";

    //     std::cout << "}\n";
    // }

    auto priorityTotal{calcPriorityTotal(inputs)};

    std::cout << "Sum of priorities of common elements: " << priorityTotal
              << '\n';

    return EXIT_SUCCESS;
}

std::vector<std::pair<std::set<char>, std::set<char>>>
readFileInput(std::ifstream& fin) {
    std::vector<std::pair<std::set<char>, std::set<char>>> inputs;
    std::pair<std::set<char>, std::set<char>> nextInput;
    std::string nextInputLine;

    while (std::getline(fin, nextInputLine)) {
        for (size_t i{0ul}; i < nextInputLine.size(); ++i) {
            if (i < nextInputLine.size() / 2ul)
                nextInput.first.insert(nextInputLine.at(i));
            else
                nextInput.second.insert(nextInputLine.at(i));
        }

        inputs.push_back(nextInput);

        nextInput.first.clear();
        nextInput.second.clear();
    }

    return inputs;
}

char commonElement(const std::pair<std::set<char>, std::set<char>>& elements) {
    std::set<char> intersection;

    std::set_intersection(elements.first.begin(), elements.first.end(),
                          elements.second.begin(), elements.second.end(),
                          std::inserter(intersection, intersection.begin()));

    return *(intersection.begin());
}

unsigned getPriority(const char& element) {
    if (element == toupper(element))
        return element - 'A' + static_cast<char>(27);
    else
        return element - 'a' + static_cast<char>(1);
}

unsigned calcPriorityTotal(
    const std::vector<std::pair<std::set<char>, std::set<char>>>& elements) {
    unsigned priorityTotal{0u};

    for (const auto& element : elements)
        priorityTotal += getPriority(commonElement(element));

    return priorityTotal;
}
