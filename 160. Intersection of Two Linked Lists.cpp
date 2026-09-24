#include <bits/stdc++.h>
using namespace std;

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
        /* Walk and wrap
         * walk a pointer forward, and check for equality at each step
         * if null is reached, wrap to other list's head 
         * if both pointers reach null at the same time then there is no intersection */
        
        ListNode *i = headA;
        ListNode *j = headB;

        while(true) {
            if (i == nullptr && j == nullptr) {
                return nullptr;
            } else if (i == j) {
                return i;
            } else {
                i = (i == nullptr) ? headB : i->next;
                j = (j == nullptr) ? headA : j->next;
            }
        }



        return nullptr;
    }
};