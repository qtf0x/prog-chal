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

ListNode* addTwoNumbers(ListNode* l1, ListNode* l2);

int main() {
    // Create test lists
    ListNode* l1_6 = new ListNode(9);
    ListNode* l1_5 = new ListNode(9, l1_6);
    ListNode* l1_4 = new ListNode(9, l1_5);
    ListNode* l1_3 = new ListNode(9, l1_4);
    ListNode* l1_2 = new ListNode(9, l1_3);
    ListNode* l1_1 = new ListNode(9, l1_2);
    ListNode* l1 = new ListNode(9, l1_1);

    ListNode* l2_3 = new ListNode(9);
    ListNode* l2_2 = new ListNode(9, l2_3);
    ListNode* l2_1 = new ListNode(9, l2_2);
    ListNode* l2 = new ListNode(9, l2_1);

    ListNode* soln = addTwoNumbers(l1, l2);

    // std::cout << l1_2->val << l1_1->val << l1->val << " + " << l2_2->val
    //<< l2_1->val << l2->val << " = ";

    // std::cout << l1->val << " + " << l2->val << " = ";

    std::cout << l1_6->val << l1_5->val << l1_4->val << l1_3->val << l1_2->val
              << l1_1->val << l1->val << " + " << l2_3->val << l2_2->val
              << l2_1->val << l2->val << " = ";

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
    std::string l1_digits, l2_digits;

    ListNode* tempNode = l1;
    while (tempNode != nullptr) {
        l1_digits.insert(0, std::to_string(tempNode->val));
        tempNode = tempNode->next;
    }

    tempNode = l2;
    while (tempNode != nullptr) {
        l2_digits.insert(0, std::to_string(tempNode->val));
        tempNode = tempNode->next;
    }

    int l1_num, l2_num;
    std::from_chars(l1_digits.data(), l1_digits.data() + l1_digits.size(),
                    l1_num);
    std::from_chars(l2_digits.data(), l2_digits.data() + l2_digits.size(),
                    l2_num);

    int soln_num = l1_num + l2_num;

    ListNode* soln = new ListNode;
    tempNode = soln;

    for (; soln_num > 0; soln_num /= 10) {

        int tempNum = soln_num % 10;

        tempNode->val = tempNum;
        if (soln_num > 0) {
            tempNode->next = new ListNode;
        }
        tempNode = tempNode->next;
    }

    return soln;

    return nullptr;
}

