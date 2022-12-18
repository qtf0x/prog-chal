#include <fstream>
#include <iostream>

constexpr const char* FILE_PATH{"input.txt"};

int main() {
    std::ifstream fin(FILE_PATH);

    if (fin.fail()) {
        std::cerr << "Failed to open file \"" << FILE_PATH << "\"\n"
                  << "Shutting down ...\n";
        return EXIT_FAILURE;
    }

    unsigned next_calories_count{0u}, curr_total_calories{0u},
        max_total_calories{0u};

    while (fin >> next_calories_count) {
        curr_total_calories += next_calories_count;

        fin.get();
        if (fin.peek() == '\n') {
            max_total_calories =
                std::max(max_total_calories, curr_total_calories);

            curr_total_calories = 0u;
        }
    }

    std::cout << "Max total calories: " << max_total_calories << '\n';

    return EXIT_SUCCESS;
}
