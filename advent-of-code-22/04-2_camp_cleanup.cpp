/**
 * @file 04-1_camp_cleanup.cpp
 * @author Vincent Marias ( @qtf0x )
 * @date 12/20/2022
 *
 * @brief Advent of Code 2022
 *        Day 4: Camp Cleanup [Part 2]
 */

#include <algorithm>
#include <fstream>
#include <iostream>
#include <set>
#include <vector>

constexpr const char* INPUT_FILE{"04_input.txt"};

std::vector<std::pair<std::set<unsigned>, std::set<unsigned>>>
readFileInput(std::ifstream& fin);

std::set<unsigned> constructRange(const unsigned& beginRange,
                                  const unsigned& endRange);

unsigned countSubsets(
    const std::vector<std::pair<std::set<unsigned>, std::set<unsigned>>>&
        inputs);

bool isOverlap(const std::pair<std::set<unsigned>, std::set<unsigned>>& input);

int main() {
    std::ifstream fin(INPUT_FILE);

    if (fin.fail()) {
        std::cerr << "Failed to open file \"" << INPUT_FILE << "\"\n"
                  << "Shutting down ...\n";

        return EXIT_FAILURE;
    }

    auto inputs{readFileInput(fin)};

    fin.close();

    std::cout << "Read in " << inputs.size() << " inputs.\n";

    // for (const auto& input : inputs) {
    //     std::cout << '{';

    //     for (const auto& element : input.first)
    //         std::cout << element << ", ";

    //     std::cout << "}, {";

    //     for (const auto& element : input.second)
    //         std::cout << element << ", ";

    //     std::cout << "}\n";
    // }

    auto numSubsets{countSubsets(inputs)};

    std::cout << "Found " << numSubsets << " subset pairs.\n";

    return EXIT_SUCCESS;
}

std::vector<std::pair<std::set<unsigned>, std::set<unsigned>>>
readFileInput(std::ifstream& fin) {
    std::vector<std::pair<std::set<unsigned>, std::set<unsigned>>> inputs;
    std::pair<std::set<unsigned>, std::set<unsigned>> nextInput;
    unsigned beginRange{0u}, endRange{0u};

    while (!fin.eof()) {
        fin >> beginRange;
        fin.get();
        fin >> endRange;
        fin.get();

        nextInput.first = constructRange(beginRange, endRange);

        fin >> beginRange;
        fin.get();
        fin >> endRange;
        fin.get();

        nextInput.second = constructRange(beginRange, endRange);

        if (!fin.fail())
            inputs.push_back(nextInput);
    }

    return inputs;
}

std::set<unsigned> constructRange(const unsigned& beginRange,
                                  const unsigned& endRange) {
    std::set<unsigned> range;

    for (unsigned i{beginRange}; i <= endRange; ++i)
        range.insert(i);

    return range;
}

unsigned countSubsets(
    const std::vector<std::pair<std::set<unsigned>, std::set<unsigned>>>&
        inputs) {
    unsigned numSubsets{0ul};

    for (const auto& input : inputs)
        numSubsets += isOverlap(input);

    return numSubsets;
}

bool isOverlap(const std::pair<std::set<unsigned>, std::set<unsigned>>& input) {
    std::set<unsigned> intersection;

    std::set_intersection(input.first.begin(), input.first.end(),
                          input.second.begin(), input.second.end(),
                          std::inserter(intersection, intersection.begin()));

    return intersection.size();
}
