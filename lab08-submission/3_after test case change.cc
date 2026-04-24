/**
 * @note :上一版的代码我在测试样例改之前就过了，
 * 上一版代码是符合严格的满二叉树（含NULL）的数组映射过后的输出结果
 * 但是现在的测试样例改了，只是普通的层序遍历输出，当然我这版代码在新的测试样例下也是过的
 * 但是我觉得上一版代码更严谨一些。
 */
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <deque>
using namespace std;
struct TreeNode
{
    int val;
    TreeNode *parent;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), parent(NULL), left(NULL), right(NULL) {}
};
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
deque<TreeNode *> levelOrder(TreeNode *root)
{
    deque<TreeNode *> result;
    if (!root)
        return result;
    deque<TreeNode *> queue;
    queue.push_back(root);
    while (!queue.empty())
    {
        // 出队取出来，print（push）到result里
        TreeNode *node = queue.front();
        queue.pop_front();
        if (node)
        {
            result.push_back(node);
            queue.push_back(node->left);
            queue.push_back(node->right);
        }
        else
        {
            result.push_back(NULL);
        }
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
    if (cin >> n)
    {
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
    /*------------------遍历打印模块-----------------*/
     if (root == NULL) {
        cout << "null"; 
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