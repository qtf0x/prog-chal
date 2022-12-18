#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>

constexpr const char* FILE_PATH{"input.txt"};

int main() {
    std::ifstream fin(FILE_PATH);

    if (fin.fail()) {
        std::cerr << "Failed to open file \"" << FILE_PATH << "\"\n"
                  << "Shutting down ...\n";
        return EXIT_FAILURE;
    }

    unsigned next_calories_count{0u};

    std::vector<unsigned> calorie_counts(1ul, 0ul);

    for (size_t i{0ul}; fin >> next_calories_count;) {
        calorie_counts.at(i) += next_calories_count;

        fin.get();

        if (fin.peek() == '\n') {
            calorie_counts.push_back(0ul);
            ++i;
        }
    }

    fin.close();

    std::sort(calorie_counts.begin(), calorie_counts.end());
    std::reverse(calorie_counts.begin(), calorie_counts.end());

    std::cout << "Top total calories:\n"
              << "\t1: " << calorie_counts.at(0ul) << '\n'
              << "\t2: " << calorie_counts.at(1ul) << '\n'
              << "\t3: " << calorie_counts.at(2ul) << '\n'
              << "Total: "
              << calorie_counts.at(0ul) + calorie_counts.at(1ul) +
                     calorie_counts.at(2ul)
              << '\n';

    return EXIT_SUCCESS;
}
