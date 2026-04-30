#include<iostream>
#include<vector>
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

void print_inorder(TreeNode* root, vector<int>& inorder_vals) {
    if (!root) return;
    print_inorder(root->left, inorder_vals);
    inorder_vals.push_back(root->val);
    print_inorder(root->right, inorder_vals);
}

int in_range_num_by_inorder(TreeNode* root, int left, int right,int num_nodes) {
    vector<int> inorder_vals;
    // 中序遍历
    print_inorder(root, inorder_vals);
    // 计算在范围内的节点数量
    int count = 0;
    for (int val : inorder_vals) {
        if (val >= left && val <= right) {
            count++;
        }
    }
    return count;
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
        cout << in_range_num_by_inorder(root, left, right, num_nodes) << endl;
    } 
}
