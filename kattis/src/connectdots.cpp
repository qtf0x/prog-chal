/**
 * @file connectdots.cpp
 * @author Vincent Marias (vmarias@mines.edu)
 * @brief https://open.kattis.com/problems/connectdots
 * @date 2022-03-13
 */

#include <iostream>

#include <cmath>

static const int ROWS = 4;
static const int COLS = 4;

std::pair<int, int> find(int*, const int&, const int&, const int&);

bool isAdjacent(std::pair<int, int>, std::pair<int, int>);

int relation(std::pair<int, int>, std::pair<int, int>);

int connectTheDots(int*, const int&, const int&);

int main() {
    // get user input
    int* grid = new int[ROWS * COLS];

    for (int i = 0; i < ROWS; ++i) {
        for (int j = 0; j < COLS; ++j) {
            std::cin >> grid[j + COLS * i];
        }
    }

    std::cout << connectTheDots(grid, ROWS, COLS);

    return EXIT_SUCCESS;
}

std::pair<int, int> find(int* grid, const int& rows, const int& cols,
                         const int& value) {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (grid[j + cols * i] == value) {
                return std::make_pair(i, j);
            }
        }
    }

    return std::make_pair(-1, -1);
}

bool isAdjacent(std::pair<int, int> pointOne, std::pair<int, int> pointTwo) {
    return pointOne.first == pointTwo.first ||
           pointOne.second == pointTwo.second ||
           std::abs(pointOne.first - pointTwo.first) ==
               std::abs(pointOne.second - pointTwo.second);
}

int relation(std::pair<int, int> pointOne, std::pair<int, int> pointTwo) {
    // same row
    if (pointOne.first == pointTwo.first)
        return 0;

    // same column
    if (pointOne.second == pointTwo.second)
        return 1;

    // same diagonal
    if (std::abs(pointOne.first - pointTwo.first) ==
        std::abs(pointOne.second - pointTwo.second))
        return 2;

    return -1;
}

int connectTheDots(int* grid, const int& rows, const int& cols) {
    int value(1), lineSegs(0);

    auto prev = find(grid, rows, cols, value);
    auto next = find(grid, rows, cols, value + 1);

    while (value < rows * cols) {
        // determine relationship
        int relate = relation(prev, next);

        // get another line segment
        while (isAdjacent(prev, next)) { // add relationship

            // if loop exits because points not adjacent, must draw a line
            // segment between them

            // if loop exits because points adjacent, but not in the same way as
            // the last set, do not draw a line segment between them

            prev = next;
            next = find(grid, rows, cols, value + 1);

            value++;
        }

        prev = next;
        next = find(grid, rows, cols, value + 1);
        lineSegs++;
    }

    // if last relationship was row-wise, next point must be in the same row, at
    // a greater column

    // if last relationship was column-wise, next point must be in the same
    // column, at a greater row

    // if last relationship was diagonal-wise, next point must be in the same
    // diagonal, at a greater difference of row AND column

    return lineSegs;
}
