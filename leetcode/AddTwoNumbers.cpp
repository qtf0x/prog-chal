/**
 * @author qtf0x
 * @date 19.06.2022
 *
 * @brief LeetCode Problem 2: Add Two Numbers
 *        You are given two non-empty linked lists representing two non-negative
 *        integers. The digits are stored in reverse order, and each of their
 *        nodes contains a single digit. Add the two numbers and return the sum
 *        as a linked list. You may assume the two numbers do not contain any
 *        leading zero, except the number 0 itself.
 */

#include <charconv>
#include <iostream>
#include <stack>

struct ListNode {
    int val;
    ListNode* next;

    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode* next) : val(x), next(next) {}
};

/**
 * @brief Given two non-empty linked lists containing the digits of two numbers
 * in reverse order, add the numbers and return their sum as a similar
 * reverse-digit linked list.
 *
 * @param l1 the first number represented as a linked list of digits
 * @param l2 the second number represnted as a linked list of digits
 * @return ListNode* the sum of the two argument numbers as a linked list of
 * digits in reverse order
 */
ListNode* addTwoNumbers(ListNode* l1, ListNode* l2);

int main() {
    // Create test lists
    ListNode* l1_2 = new ListNode(3);
    ListNode* l1_1 = new ListNode(4, l1_2);
    ListNode* l1 = new ListNode(2, l1_1);

    ListNode* l2_2 = new ListNode(4);
    ListNode* l2_1 = new ListNode(6, l2_2);
    ListNode* l2 = new ListNode(5, l2_1);

    ListNode* soln = addTwoNumbers(l1, l2);

    std::cout << l1_2->val << l1_1->val << l1->val << " + " << l2_2->val
              << l2_1->val << l2->val << " = ";

    // use a stack to print out nodes in reverse
    std::stack<int> soln_nums;
    ListNode* tempNode = soln;
    while (tempNode != nullptr) {
        soln_nums.push(tempNode->val);
        tempNode = tempNode->next;
    }

    while (!soln_nums.empty()) {
        std::cout << soln_nums.top();
        soln_nums.pop();
    }
    std::cout << '\n';

    return EXIT_SUCCESS;
}

ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
    // a single digit in l1 or l2 is [0, 9] so with carry solution digits are
    // only [0, 19] and the carry is either 0 or 1 (no need for more memory like
    // an int)
    char digit1, digit2, soln_digit;
    bool carry = 0;

    // allocate dummy head on the stack to avoid cleaning up dynamic memory
    ListNode soln;
    ListNode* tempNode = &soln;

    while (l1 || l2 || carry) {
        digit1 = 0;
        digit2 = 0;

        if (l1) {
            digit1 = l1->val;
            l1 = l1->next;
        }

        if (l2) {
            digit2 = l2->val;
            l2 = l2->next;
        }

        soln_digit = digit1 + digit2 + carry;

        // only push back least significant digit of current sum
        tempNode->next = new ListNode(soln_digit % 10);
        tempNode = tempNode->next;

        carry = soln_digit > 9;
    }

    return soln.next;
}

