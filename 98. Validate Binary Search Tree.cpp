/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left),
 * right(right) {}
 * };
 */
class Solution {
public:
    bool isValidBST(TreeNode* root) {
        if (!root) {
            return false;
        }

        queue<tuple<TreeNode*, long long, long long>> q{};

        q.push({root, LLONG_MIN, LLONG_MAX});

        while (!q.empty()) {
            // keep track 
            auto [node, lo, hi] = q.front();
            q.pop();

            if (node->val <= lo || node->val >= hi) {
                return false;
            }

            if (node->left) {
                q.push({node->left, lo, node->val});
            }
            if (node->right) {
                q.push({node->right, node->val, hi});
            }
        }

        return true;
    }
};
