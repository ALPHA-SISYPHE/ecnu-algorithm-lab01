#include<iostream>
#include<vector>
using namespace std;

struct TreeNode
{
    int val; 
    TreeNode *left;
    TreeNode *right;
    TreeNode *parent; 
    TreeNode(int x) : val(x), left(NULL), right(NULL), parent(NULL) {}
};

bool build_and_test_with_preorder_sq(vector<TreeNode*>& preorder, int low, int high) {
    if (low > high) return true;
    
    TreeNode* root = preorder[low];
    int i = low + 1;
    while (i <= high && preorder[i]->val < root->val) {
        i++;
    }
    //i最终停在第一个大于等于根节点的元素的位置
    
    //先遍历剩余元素,如果出现小于根节点的元素,说明不是二叉搜索树
    int j = i; 
    while (j <= high) {
        if (preorder[j]->val < root->val) {
            return false;
        }
        j++;
    }
    
    //到达这一步说明当前根合法
    //构建当前的根左右
    if (low + 1 < i) {
        root->left = preorder[low + 1];
        root->left->parent = root;
        if (!build_and_test_with_preorder_sq(preorder, low + 1, i - 1)) {
            return false;
        }
    }
    if (i <= high) {
        root->right = preorder[i];
        root->right->parent = root;
        if (!build_and_test_with_preorder_sq(preorder, i, high)) {
            return false;
        }
    }
    return true;
}

void get_post_order(TreeNode* root, vector<int>& res) {
    if (root == NULL) {
        return;
    }
    get_post_order(root->left, res);
    get_post_order(root->right, res);
    res.push_back(root->val);
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    if (!(cin >> n)) return 0;
    
    for(int i=0;i<n;i++){
        int val;
        cin>>val;
        vector<TreeNode*> preorder;
        for(int j=0;j<val;j++){
            int node_val;
            cin>>node_val;
            preorder.emplace_back(new TreeNode(node_val));
        }
        
        if (!preorder.empty() && build_and_test_with_preorder_sq(preorder, 0, preorder.size() - 1)) {
            cout << "YES\n";
            
            vector<int> post_res;
            get_post_order(preorder[0], post_res);
            
            for (int k = 0; k < post_res.size(); ++k) {
                cout << post_res[k] << (k == post_res.size() - 1 ? "" : " ");
            }
            cout << "\n";
        } else {
            cout << "NO\n";
        }
        
        for (auto node : preorder) {
            delete node;
        }
    }
    return 0;
}