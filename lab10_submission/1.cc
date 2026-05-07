#include <iostream>
using namespace std;

struct TreeNode
{
    long long val; // 改为long long
    TreeNode *left;
    TreeNode *right;
    TreeNode(long long x) : val(x), left(NULL), right(NULL) {}
};

TreeNode* insertRec(TreeNode* root, long long val)
{
    if (root == NULL)
    {
        root = new TreeNode(val);
        return root;
    } 
    if (val < root->val)
    {
        root->left = insertRec(root->left, val);
    }
    else
    {
        root->right = insertRec(root->right, val);
    }
    return root;
}

long long solve_lca(TreeNode* root, long long a, long long b)
{
    // 先保证 a <= b
    if (a > b) swap(a, b);
    
    if (root->val >= a && root->val <= b)
    {
        return root->val;
    }
    else if (root->val < a) // 两个节点都在右子树
    {
        return solve_lca(root->right, a, b);
    }
    else // 两个节点都在左子树
    {
        return solve_lca(root->left, a, b);
    }
}

int main()
{
    ios::sync_with_stdio(false); 
    cin.tie(nullptr);
    
    int N, Q;
    cin >> N >> Q;
    
    TreeNode* root = NULL;
    for (int i = 0; i < N; ++i)
    {
        long long val;
        cin >> val;
        root = insertRec(root, val);
    }

    for (int i = 0; i < Q; ++i)
    {
        long long u, v;
        cin >> u >> v;
        cout << solve_lca(root, u, v) << endl;
    }

    return 0;
}
