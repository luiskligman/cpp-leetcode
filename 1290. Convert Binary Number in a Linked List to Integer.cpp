#include <bits/stdc++.h>
using namespace std;
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
public:
    int getDecimalValue(ListNode* head) {
        int ret = head->val;
        head = head->next;

        // slli by 1 is the same as multiplying by 2
        while (head != nullptr) {
            ret = ret * 2 + head->val;
            head = head->next;
        }

        return ret;
    }
};
