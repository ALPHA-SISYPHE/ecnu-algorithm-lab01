#include <iostream>
#include <vector>
#include <string>
#include <sstream>
using namespace std;

struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

TreeNode *inserRec(TreeNode *root, int val)
{
    if (root == NULL)
    {
        root = new TreeNode(val);
        return root;
    } 
    if (val < root->val)
    {
        root->left = inserRec(root->left, val);
    }
    else
    {
        root->right = inserRec(root->right, val);
    }
    return root;
}

int slove_lca(TreeNode *root, int n, int m)
{
    if (root == NULL)
    {
        return 0;
    }
    if (root->val >= n && root->val <= m)
    {
        return root->val;
    }
    else if (root->val < n)
    {
        return slove_lca(root->right, n, m);
    }
    else
    {
        return slove_lca(root->left, n, m);
    }
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    
    int n,m;
    TreeNode *root = NULL;//树的根节点
    string s, line;

    getline(cin, line);

    stringstream ss(line);
    while (getline(ss, s, ',')) {
        if (s == "null" || s.empty()) {
            continue;
        }
        int val = stoi(s);
        //插入树
        root = inserRec(root, val);
    }

    cin >> n >> m;
    cout << slove_lca(root, n, m);
}