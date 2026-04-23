#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <deque>
#include <algorithm>
using namespace std;

struct TreeNode
{
    int val;
    TreeNode *parent;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), parent(NULL), left(NULL), right(NULL) {}
};

TreeNode *buildTree(deque<TreeNode *> &process)
{
    if (process.empty())
    {
        return NULL;
    }
    TreeNode *root = process.front();
    process.pop_front();
    deque<TreeNode *> currentLevel; // 当前层的节点
    if (root != NULL)
    {
        currentLevel.push_back(root);
    }

    while (!currentLevel.empty())
    {
        TreeNode *currentNode = currentLevel.front();
        currentLevel.pop_front();

        if (!process.empty())
        {
            TreeNode *leftChild = process.front();
            process.pop_front();
            currentNode->left = leftChild;
            if (leftChild != NULL)
            {
                leftChild->parent = currentNode;
                currentLevel.push_back(leftChild);
            }
        }

        if (!process.empty())
        {
            TreeNode *rightChild = process.front();
            process.pop_front();
            currentNode->right = rightChild;
            if (rightChild != NULL)
            {
                rightChild->parent = currentNode;
                currentLevel.push_back(rightChild);
            }
        }
    }

    return root;
}

void printTree(TreeNode *root, vector<string> &output)
{
    deque<TreeNode *> currentLevel;
    if (root != NULL)
    {
        currentLevel.push_back(root);
    }
    while (!currentLevel.empty())
    {
        TreeNode *currentNode = currentLevel.front();
        currentLevel.pop_front();
        if (currentNode != NULL)
        {
            output.push_back(to_string(currentNode->val));
            // 是 NULL 也放入队列，这样才能占据位置打印中间的 "null"
            currentLevel.push_back(currentNode->left);
            currentLevel.push_back(currentNode->right);
        }
        else
        {
            output.push_back("null");
        }
    }

    //queue 里可能会有很多 null，导致输出末尾有很多 "null"，需要去除末尾多余的 "null"
    while (!output.empty() && output.back() == "null")
    {
        output.pop_back();
    }
    for (size_t i = 0; i < output.size(); ++i)
    {
        cout << output[i];
        if (i != output.size() - 1)
        {
            cout << ",";
        }
    }
}

// 中序遍历，找逆序的节点对
void inorderTraversal(TreeNode *root, vector<TreeNode *> &nodes, vector<TreeNode *> &inversionNodes)
{
    if (root == NULL)
    {
        return;
    }
    inorderTraversal(root->left, nodes, inversionNodes);
   // 必须判断“前一个节点的值”是否大于“当前节点的值”
    if (!nodes.empty() && nodes.back()->val > root->val) 
    {
        if (inversionNodes.empty())
        {
            inversionNodes.push_back(nodes.back());
            inversionNodes.push_back(root);
        }
        else
        {
            inversionNodes[1] = root;
        }
    }
    // 比较完了之后，才能把当前节点加进去，给下一次循环做“前一个节点”
    nodes.push_back(root);
    inorderTraversal(root->right, nodes, inversionNodes);
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    // 处理层序建树的双端队列
    deque<TreeNode *> process;

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
        if (s == "null")
        {
            process.push_back(NULL);
        }
        else
        {
            TreeNode *node = new TreeNode(stoi(s));
            process.push_back(node);
        }
    }
    /*------------------结束-----------------*/
    root = buildTree(process);
    // 中序遍历，找逆序的节点对
    vector<TreeNode *> inversionNodes;
    vector<TreeNode *> nodes;
    inorderTraversal(root, nodes, inversionNodes);
    // swap
    swap(inversionNodes[0]->val, inversionNodes[1]->val);

    // 打印树的层序遍历结果
    vector<string> output;
    printTree(root, output);
}