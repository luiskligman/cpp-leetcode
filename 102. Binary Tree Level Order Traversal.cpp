/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
    vector<vector<int>> levelOrder(TreeNode* root) {
        vector<vector<int>> ret{};
        if (root == nullptr) { return ret; }

        queue<TreeNode*> q{};
        q.push(root);

        while (!q.empty()) {
            size_t n = q.size();  // number of nodes at this level
            vector<int> level{};

            for (size_t i = 0; i < n; ++i) {
                auto node = q.front();
                q.pop();

                level.push_back(node->val);
                
                if (node->left) { q.push(node->left); }
                if (node->right) { q.push(node->right); }
            }

            ret.push_back(level);
        }

        return ret;
    }
};
