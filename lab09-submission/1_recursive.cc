#include<iostream>
using namespace std;
struct TreeNode
{
    int val;
    TreeNode *parent;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), parent(NULL), left(NULL), right(NULL) {}
};
// 递归插入节点
TreeNode *inserRec(TreeNode *root, int val)
{
    if (root == NULL)
    {
        return new TreeNode(val);
    }
    if (val < root->val)
    {
        root->left = inserRec(root->left, val);
        root->left->parent = root;
    }
    else if (val > root->val)
    {
        root->right = inserRec(root->right, val);
        root->right->parent = root;
    }
    return root;
}

int in_range_num(TreeNode* root, int left, int right) {
    if (!root) return 0;
    if (root->val < left) {
        return in_range_num(root->right, left, right);
    } else if (root->val > right) {
        return in_range_num(root->left, left, right);
    } else {
        return 1 + in_range_num(root->left, left, right) + in_range_num(root->right, left, right);
    }
}

int main()
{
    int num_nodes;
    int query_times;
    cin >> num_nodes >> query_times;
    TreeNode *root = NULL; // 树的根节点
    for(int i = 0; i < num_nodes; i++) {
        int val;
        cin >> val;
        root = inserRec(root, val);
    }

    for(int i = 0; i < query_times; i++) {
        int left, right;
        cin >> left >> right;
        cout << in_range_num(root, left, right) << endl;
    }
}
