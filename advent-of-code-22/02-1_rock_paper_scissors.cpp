/**
 * @file 02-1_rock_paper_scissors.cpp
 * @author Vincent Marias ( @qtf0x )
 * @date 12/17/2022
 *
 * @brief Advent of Code 2022
 *        Day 2: Rock Paper Scissors [Part 1]
 */

#include <fstream>
#include <iostream>
#include <unordered_map>
#include <vector>

constexpr const char* INPUT_FILE{"02_input.txt"};

enum MOVE { ROCK, PAPER, SCISSORS };
enum OUTCOME { LOST, DRAW, WON };

const std::unordered_map<char, MOVE> GUIDE_ENCODING{
    {'A', ROCK}, {'B', PAPER}, {'C', SCISSORS},
    {'X', ROCK}, {'Y', PAPER}, {'Z', SCISSORS}};

const std::unordered_map<MOVE, unsigned> MOVES_SCORES{
    {ROCK, 1u}, {PAPER, 2u}, {SCISSORS, 3u}};
const std::unordered_map<OUTCOME, unsigned> OUTCOMES_SCORES{
    {LOST, 0u}, {DRAW, 3u}, {WON, 6u}};

std::vector<std::pair<char, char>> readFromFile(std::ifstream& fin);

unsigned scoreInputs(const std::vector<std::pair<char, char>>& INPUTS);

unsigned scoreRound(const std::pair<char, char>& INPUT);

OUTCOME compareMoves(const MOVE& OPPONENT_MOVE, const MOVE& PLAYER_MOVE);

bool moveGreater(const MOVE& LHS, const MOVE& RHS);

int main() {
    std::ifstream fin(INPUT_FILE);

    if (fin.fail()) {
        std::cerr << "Failed to open file \"" << INPUT_FILE << "\"\n"
                  << "Shutting down ...\n";
        return EXIT_FAILURE;
    }

    auto inputs{readFromFile(fin)};

    fin.close();

    std::cout << "Read in " << inputs.size() << " inputs.\n";

    auto totalScore{scoreInputs(inputs)};

    std::cout << "Total score for all rounds: " << totalScore << '\n';

    return EXIT_SUCCESS;
}

std::vector<std::pair<char, char>> readFromFile(std::ifstream& fin) {
    char nextOpponentInput{'\0'}, nextPlayerInput{'\0'};
    std::vector<std::pair<char, char>> inputs;

    while (fin >> nextOpponentInput >> nextPlayerInput)
        inputs.emplace_back(nextOpponentInput, nextPlayerInput);

    return inputs;
}

unsigned scoreInputs(const std::vector<std::pair<char, char>>& INPUTS) {
    unsigned totalScore{0u};

    for (const auto& INPUT : INPUTS)
        totalScore += scoreRound(INPUT);

    return totalScore;
}

unsigned scoreRound(const std::pair<char, char>& INPUT) {
    auto opponentMove{GUIDE_ENCODING.at(INPUT.first)},
        playerMove{GUIDE_ENCODING.at(INPUT.second)};

    auto moveScore{MOVES_SCORES.at(playerMove)},
        outcomeScore{
            OUTCOMES_SCORES.at(compareMoves(opponentMove, playerMove))};

    // std::cout << "Move score " << moveScore << " + outcome score "
    //           << outcomeScore << " = " << moveScore + outcomeScore << '\n';

    return moveScore + outcomeScore;
}

OUTCOME compareMoves(const MOVE& OPPONENT_MOVE, const MOVE& PLAYER_MOVE) {
    if (moveGreater(OPPONENT_MOVE, PLAYER_MOVE))
        return LOST;

    if (OPPONENT_MOVE == PLAYER_MOVE)
        return DRAW;

    return WON;
}

// tried this as overload of > operator, but couldn't get it to call my overload
// instead of casting the enums to ints and comparing those ?????

bool moveGreater(const MOVE& LHS, const MOVE& RHS) {
    if (LHS == ROCK && RHS == SCISSORS)
        return true;
    else if (LHS == PAPER && RHS == ROCK)
        return true;
    else if (LHS == SCISSORS && RHS == PAPER)
        return true;

    return false;
}
