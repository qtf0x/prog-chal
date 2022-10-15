/**
 * @file LongestPalindromicSubstring.cpp
 * @author Vincent Marias ( @qtf0x )
 * @date 10.15.2022
 *
 * @brief LeetCode Problem 5: Longest Palindromic Substring
 *        Given a string `s`, return the longest palindromic substring in `s`. A
 *        string is called a palindrome string if the reverse of that string is
 *        the same as the original string.
 */

#include <algorithm>
#include <iostream>
#include <string>

bool isPalindrome(std::string input) {
    size_t input_size = input.size();

    for (size_t i = 0; i < input_size / 2; ++i) {
        if (input.at(i) != input.at(input_size - i - 1))
            return false;
    }

    return true;
}

std::string longestPalindrome(std::string s) {
    std::string curr, longest(s.substr(0, 1));
    int s_size = s.size();
    char left(0), center(s.at(0)), right(0);

    for (size_t i = 0; i < s_size - 2; ++i) {
        center = s.at(i);

        if (s_size > 1 && center == s.at(i + 1))
            longest = longest.size() >= 2 ? longest : s.substr(i, 2);

        if (i != 0) {
            for (size_t j = 1; j <= i && i + j <= s_size - 1; ++j) {
                left = s.at(i - j);
                right = s.at(i + j);

                if (left != right)
                    break;

                if (2 * j + 1 > longest.size())
                    longest = s.substr(left, right - left + 1);
            }
        }
    }

    // for (size_t i = 0; i < s_size - 1; ++i) {
    //     for (size_t j = 1; j <= s_size - i; ++j) {
    //         curr = s.substr(i, j);

    //         if (isPalindrome(curr) && curr.size() > longest.size())
    //             longest = curr;
    //     }
    // }

    return longest;
}

int main() {
    std::string input;

    std::cin >> input;

    std::cout << longestPalindrome(input) << '\n';
}
