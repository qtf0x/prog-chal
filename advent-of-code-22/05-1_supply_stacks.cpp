/**
 * @file 05-1_supply_stacks.cpp
 * @author Vincent Marias ( @qtf0x )
 * @date 12/21/2022
 *
 * @brief Advent of Code 2022
 *        Day 5: Supply Stacks [Part 1]
 */

#include <algorithm>
#include <array>
#include <fstream>
#include <iostream>
#include <sstream>
#include <stack>
#include <vector>

constexpr const char* INPUT_FILE{"05_input.txt"};

std::vector<std::stack<char>> readFileInputStacks(std::ifstream& fin);

std::vector<std::array<size_t, 3ul>> readFileInputMoves(std::ifstream& fin);

void moveCrates(std::vector<std::stack<char>>& crateStacks,
                const std::vector<std::array<size_t, 3ul>>& crateMoves);

std::string getTopCrates(const std::vector<std::stack<char>>& crateStacks);

int main() {
    std::ifstream fin(INPUT_FILE);

    if (fin.fail()) {
        std::cerr << "Failed to open file \"" << INPUT_FILE << "\"\n"
                  << "Shutting down ...\n";

        return EXIT_FAILURE;
    }

    auto crateStacks{readFileInputStacks(fin)};
    auto crateMoves{readFileInputMoves(fin)};

    fin.close();

    std::cout << "Read in " << crateStacks.size() << " crate stacks.\n"
              << "Read in " << crateMoves.size() << " crate moves.\n";

    // simulate crate movements
    moveCrates(crateStacks, crateMoves);

    auto topCrates{getTopCrates(crateStacks)};
    std::cout << "Top crates: " << topCrates << '\n';

    return EXIT_SUCCESS;
}

std::vector<std::stack<char>> readFileInputStacks(std::ifstream& fin) {
    std::vector<std::stack<char>> crateStacks;
    char nextCrate{'\0'};

    std::vector<std::string> inputLines;
    std::string nextLine;

    do {
        std::getline(fin, nextLine);
        inputLines.push_back(nextLine);
    } while (inputLines.back().at(1ul) != '1');

    inputLines.pop_back();

    std::reverse(nextLine.begin(), nextLine.end());
    std::stringstream stackCounts(nextLine);
    size_t numStacks{0ul};
    stackCounts >> numStacks;

    crateStacks.resize(numStacks);

    std::reverse(inputLines.begin(), inputLines.end());
    for (const auto& line : inputLines) {
        for (size_t i{0ul}; i < numStacks; ++i) {
            nextCrate = line.at((i + 1ul) * 4ul - 3ul);

            if (nextCrate != ' ')
                crateStacks.at(i).push(nextCrate);
        }
    }

    return crateStacks;
}

std::vector<std::array<size_t, 3ul>> readFileInputMoves(std::ifstream& fin) {
    std::vector<std::array<size_t, 3ul>> crateMoves;
    std::array<size_t, 3ul> nextMove{0u};

    std::string discard;

    while (!fin.eof()) {
        fin >> discard >> nextMove.at(0ul) >> discard >> nextMove.at(1ul) >>
            discard >> nextMove.at(2ul);

        if (!fin.fail())
            crateMoves.push_back(nextMove);
    }

    return crateMoves;
}

void moveCrates(std::vector<std::stack<char>>& crateStacks,
                const std::vector<std::array<size_t, 3ul>>& crateMoves) {
    for (const auto& crateMove : crateMoves) {
        size_t numMoves{crateMove.at(0ul)}, fromStack{crateMove.at(1ul) - 1ul},
            toStack{crateMove.at(2ul) - 1ul};

        for (size_t i{0ul}; i < numMoves; ++i) {
            crateStacks.at(toStack).push(crateStacks.at(fromStack).top());
            crateStacks.at(fromStack).pop();
        }
    }
}

std::string getTopCrates(const std::vector<std::stack<char>>& crateStacks) {
    std::string topCrates;

    for (const auto& crateStack : crateStacks)
        topCrates += crateStack.top();

    return topCrates;
}
