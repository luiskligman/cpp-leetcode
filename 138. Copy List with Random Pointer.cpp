#include <bits/stdc++.h>
using namespace std;
/*
// Definition for a Node.
class Node {
public:
    int val;
    Node* next;
    Node* random;

    Node(int _val) {
        val = _val;
        next = NULL;
        random = NULL;
    }
};
*/

class Solution {
public:
    Node* copyRandomList(Node* head) {
        // first pass, recreate the initial list, not worrying about random
        // store each node in an unordered map
        unordered_map<Node*, Node*> nodes;
        Node dummy(0);
        Node* curr = &dummy;

        for (Node* orig = head; orig != nullptr; orig = orig->next) {
            curr->next = new Node(orig->val);
            nodes[orig] = curr->next;
            curr = curr->next;
        }

        for (Node* orig = head; orig != nullptr; orig = orig->next) {
            nodes[orig]->random = nodes[orig->random];
        }

        return dummy.next;
    }
};