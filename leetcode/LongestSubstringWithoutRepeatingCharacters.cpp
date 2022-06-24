/**
 * @author qtf0x
 * @date 22.06.2022
 *
 * @brief LeetCode Problem 3: Longest Substring Without Repeating Characters
 *        Give a string `s`, find the length of the longest substring without
 *        repeating characters.
 */

#include <cinttypes>
#include <iostream>

/**
 * @brief Find the length of the longest substring without repeating characters
 * in a given string.
 *
 * @param s string to search through for a substring
 * @return length of the longest substring without repeating characters
 */
int lengthOfLongestSubstring(std::string s);

int main() {
    std::string s;

    while (true) {
        std::cout << "Please enter string: ";

        std::getline(std::cin, s);

        std::cout
            << "Length of longest substring without repeating characters: "
            << lengthOfLongestSubstring(s) << "\n\n";
    }

    return EXIT_SUCCESS;
}

int lengthOfLongestSubstring(std::string s) {
    bool window[95] = {0};
    // problem requirements state 0 <= s.size() <= 5e4 (only need two bytes)
    uint_fast16_t curr_len(0), max_len(0);

    // loop until second pointer reaches end
    for (uint_fast16_t i(0), j(0); j < s.size(); ++j) {
        // move first pointer forward until no repeats
        for (; window[static_cast<size_t>(s.at(j)) - 32]; ++i) {
            window[static_cast<size_t>(s.at(i)) - 32] = 0;
            --curr_len;
        }

        window[static_cast<size_t>(s.at(j)) - 32] = 1;
        ++curr_len;

        if (curr_len > max_len) {
            max_len = curr_len;
        }
    }

    return max_len;
}

