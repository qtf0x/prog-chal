/**
 * @author qtf0x
 * @date 18.06.2022
 *
 * @brief LeetCode Problem 1: Two Sum
 *        Given an array of integers `nums` and an integer `target`, return
 *        indices of the two numbers such that they add up to `target`. You
 *        may assume that each input would have exactly one solution, and you
 *        may not use the same element twice. You can return the answer in any
 *        order.
 */

#include <cmath>
#include <iostream>
#include <unordered_map>
#include <vector>

std::vector<int> twoSum(std::vector<int>& nums, int target);

int main() {
    std::vector<int> nums = {-3, 4, 3, 90};
    int target = 0;

    std::vector<int> soln = twoSum(nums, target);

    std::cout << "Solution with input nums: {";
    for (size_t i = 0; i < nums.size() - 1; ++i) {
        std::cout << nums.at(i) << ", ";
    }
    std::cout << nums.at(nums.size() - 1) << "} and target: " << target << '\n';

    std::cout << '{' << soln.at(0) << ", " << soln.at(1) << "}\n";

    return EXIT_SUCCESS;
}

std::vector<int> twoSum(std::vector<int>& nums, int target) {
    // Naive Solution
    /*for (int i = 0; i < nums.size() - 1; ++i) {
        for (int j = i + 1; j < nums.size(); ++j) {
            if (nums.at(i) + nums.at(j) == target) {
                return {i, j};
            }
        }
    }

    return {-1, -1};*/

    // Hash Map Solution
    std::unordered_map<int, size_t> hash_map;

    // iterate over list and search hash map for corresponding indices
    for (size_t i = 0;; ++i) {
        auto it = hash_map.find(target - nums.at(i));

        // the element currently being checked is never in the hash map
        if (it != hash_map.end()) {
            return {static_cast<int>(i), static_cast<int>(it->second)};
        }

        // all previous elements are in the hash map
        hash_map[nums.at(i)] = i;
    }

    return {};
}

