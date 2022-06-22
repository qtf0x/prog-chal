/**
 * @author qtf0x
 * @date 22.06.2022
 *
 * @brief LeetCode Problem 3: Longest Substring Without Repeating Characters
 *        Give a string `s`, find the length of the longest substring without
 *        repeating characters.
 */

#include <iostream>
#include <unordered_set>

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
    std::unordered_set<char> window;
    int max_len = 0;

    size_t win_start = 0;
    for (size_t i = 0; i < s.size(); ++i) {
        if (window.count(s.at(i))) {
            if (static_cast<int>(window.size()) > max_len) {
                max_len = window.size();
            }

            window.clear();

            i = s.find(s.at(i), win_start) + 1;
            win_start = i;
        }

        window.insert(s.at(i));
    }

    if (static_cast<int>(window.size()) > max_len) {
        max_len = window.size();
    }

    return max_len;
}

