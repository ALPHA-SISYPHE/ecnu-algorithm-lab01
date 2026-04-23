#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <deque>
#include <cmath>
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
// 查找,拿到这个元素的指针
TreeNode *search(TreeNode *root, int val)
{
    if (root == NULL || root->val == val)
    {
        return root;
    }
    if (val < root->val)
    {
        return search(root->left, val);
    }
    return search(root->right, val);
}
void deleteNode(TreeNode *&root, int key, TreeNode *pos)
{
    TreeNode *del;
    if (pos == NULL)
    {
        del = search(root, key);
    }
    else
    {
        del = pos;
    }
    if (del == NULL)
    {
        return;
    }
    // 叶子节点
    else if (del->left == NULL && del->right == NULL)
    {
        // 根节点
        if (root == del)
        {
            root = NULL;
        }
        // 左叶子
        else if (del == del->parent->left)
        {
            del->parent->left = NULL;
        }
        // 右叶子
        else
        {
            del->parent->right = NULL;
        }
    }
    // 只有一个子节点
    else if (del->left == NULL || del->right == NULL)
    {
        TreeNode *child = (del->left != NULL) ? del->left : del->right;
        // 根节点
        if (root == del)
        {
            root = child;
            child->parent = NULL;
        }
        // 左分支
        else if (del == del->parent->left)
        {
            del->parent->left = child;
            child->parent = del->parent;
        }
        // 右分支
        else
        {
            del->parent->right = child;
            child->parent = del->parent;
        }
    }
    // 有两个子节点
    else
    {
        // 找到后继，即右子树的最左节点
        TreeNode *successor = del->right;
        while (successor->left != NULL)
        {
            successor = successor->left;
        }
        del->val = successor->val; // 替换值,这一步相当于已经把del给覆盖删除了
        // 这一步相当于删除了successor节点,因为successor节点的值已经被复制到del节点了
        deleteNode(root, successor->val, successor); // 删除后继节点
    }
}

// 新增辅助函数：获取树的最大深度
int getDepth(TreeNode* root) {
    if (!root) return 0;
    return 1 + max(getDepth(root->left), getDepth(root->right));
}

deque<TreeNode *> levelOrder(TreeNode *root) {
    deque<TreeNode *> result;
    if (!root) return result;

    int depth = getDepth(root);
    // 使用双队列或带层级计数的队列，确保即使是null也按照 2i+1, 2i+2 展开
    // @note 2i+1 和 2i+2 的映射关系
    deque<TreeNode *> queue;
    queue.push_back(root);
    
    int current_level = 0;
    while (current_level < depth) {
        int level_size = queue.size();
        for (int i = 0; i < level_size; i++) {
            TreeNode* node = queue.front();
            queue.pop_front();
            result.push_back(node);
            
            if (node) {
                queue.push_back(node->left);
                queue.push_back(node->right);
            } else {
                // @note 2i+1 的映射，也要补入虚拟空子节点
                queue.push_back(NULL);
                queue.push_back(NULL);
            }
        }
        current_level++;
    }

    return result;
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    TreeNode *root = NULL; // 树的根节点
    /*----------------读入初始tree数据---------------------------*/
    string s, line;
    getline(cin, line);
    stringstream ss(line);
    while (getline(ss, s, ','))
    {
        // 剔除可能存在的回车符，防止 stoi 报错
        if (!s.empty() && s.back() == '\r')
        {
            s.pop_back();
        }
        if (s == "null" || s.empty())
        {
            continue;
        }
        int val = stoi(s);
        root = inserRec(root, val);
    }
    /*------------------结束-----------------*/

    /*---------------操作模块-------------------*/
    int n;
    if (cin >> n) {
        for (int i = 0; i < n; i++)
        {
            char operate, comma; // 声明一个 comma 用来吸收逗号
            int data;
            // cin >> 会自动跳过任何空格
            cin >> operate >> comma >> data;
            if (operate == 'I')
            {
                root = inserRec(root, data);
            }
            else if (operate == 'D')
            {
                deleteNode(root, data, NULL);
            }
        }
    }
    /*------------------结束-----------------*/

    /*------------------遍历打印模块-----------------*/
    if (root == NULL) {
        cout << "null" << "\n";
        return 0;
    }
    deque<TreeNode *> result = levelOrder(root);
    // 先去除尾部多余的NULL
    while (!result.empty() && result.back() == NULL)
    {
        result.pop_back();
    }
    for (size_t i = 0; i < result.size(); ++i)
    {
        if (result[i])
        {
            cout << result[i]->val;
        }
        else
        {
            cout << "null";
        }
        if (i != result.size() - 1)
        {
            cout << ",";
        }
    }
}