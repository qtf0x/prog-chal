/**
 * @author qtf0x
 * @date 06.26.2022
 *
 * @brief LeetCode Problem 4: Median of Two Sorted Arrays
 *        Given two sorted arrays `nums1` and `nums2` of size `m` and `n`
 *        respectively, return the median of the two sorted arrays. The overall
 *        run time complexity should be O(lg(m + n)).
 */

#include <algorithm>
#include <iostream>
#include <vector>

/**
 * @brief Finds the median of all the values in the intersection of sorted lists
 * nums1 and nums2.
 *
 * @param nums1 sorted list of integers
 * @param nums2 sorted list of integers
 * @return double median of all values in nums1 and nums2
 */
double findMedianSortedArrays(std::vector<int>& nums1, std::vector<int>& nums2);

int main() {
    std::vector<int> nums1 = {1, 2};
    std::vector<int> nums2 = {3, 4};

    std::cout << findMedianSortedArrays(nums1, nums2) << '\n';

    return EXIT_SUCCESS;
}

double findMedianSortedArrays(std::vector<int>& nums1,
                              std::vector<int>& nums2) {
    std::vector<int> nums_union(nums1.size() + nums2.size());

    std::merge(nums1.begin(), nums1.end(), nums2.begin(), nums2.end(),
               nums_union.begin());

    if (nums_union.size() % 2) {
        return nums_union.at(nums_union.size() / 2);
    } else {
        return (nums_union.at(nums_union.size() / 2) +
                nums_union.at((nums_union.size() / 2) - 1)) /
               2.0;
    }
}

