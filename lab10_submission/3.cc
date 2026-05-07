#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

struct BRTreeNode
{
    int color; // 0 代表黑色，1 代表红色
    int idx; // 节点编号，用于输出
    BRTreeNode *left;
    BRTreeNode *right;
    BRTreeNode *parent; 
    BRTreeNode(int x) : color(x), left(NULL), right(NULL), parent(NULL) {}
};

void insert_sort(vector<int>& unbalanced_nodes){
    int n = unbalanced_nodes.size();
    int unsort = unbalanced_nodes[n-1];
    int i = n - 2;
    while (i >= 0 && unbalanced_nodes[i] > unsort) {
        unbalanced_nodes[i + 1] = unbalanced_nodes[i];
        i--;
    }
    unbalanced_nodes[i + 1] = unsort;
}

int check_balance(BRTreeNode* node,vector<int>& unbalanced_nodes){
    if(node == NULL) return 1; // 空节点（NIL）被视为黑色，黑高贡献为 1
    
    int left_black_height = check_balance(node->left, unbalanced_nodes);
    int right_black_height = check_balance(node->right, unbalanced_nodes);
    
    if(left_black_height != right_black_height || left_black_height == -1 || right_black_height == -1){
        unbalanced_nodes.push_back(node->idx);
        insert_sort(unbalanced_nodes);
        return -1; // 标记报废，以后有这个节点的子树都不合法了
    }
    
    return left_black_height + (node->color == 0 ? 1 : 0); // 如果当前节点是黑色，则向上传递的黑高加 1
}

BRTreeNode* find_root(vector<BRTreeNode*>& nodes) {
    for (BRTreeNode* node : nodes) {
        if (node != NULL && node->parent == NULL) {
            return node; // 找到根节点
        }
    }
    return NULL; // 如果输入合法，理论上不会执行到这里
}

int main(){
    // 加速输入输出
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int n;
    cin >> n;

    vector<BRTreeNode*> nodes(n+1); // 数组索引从 1 开始，方便与节点编号对齐
    vector<int> left(n+1);
    vector<int> right(n+1);

    for(int i = 1; i <= n; i++) {
        nodes[i] = new BRTreeNode(0); // 使用默认颜色 0 (黑色) 进行初始化
        cin >> nodes[i]->color;
        nodes[i]->idx = i;
        cin >> left[i] >> right[i];
    }

    for(int i = 1; i <= n; i++) {
        if(left[i] != -1) {
            nodes[i]->left = nodes[left[i]];
            nodes[left[i]]->parent = nodes[i];
        }
        if(right[i] != -1) {
            nodes[i]->right = nodes[right[i]];
            nodes[right[i]]->parent = nodes[i];
        }
    }

    vector<int> unbalanced_nodes;

    // 寻找根节点（入度为 0，即没有父节点的节点）
    BRTreeNode* root = find_root(nodes);
    
    check_balance(root, unbalanced_nodes); // 从根节点开始进行深度优先搜索，检查平衡性
    
    if (!unbalanced_nodes.empty()) {
        cout << "Unbalanced" << endl;
        for(int idx : unbalanced_nodes) {
            cout << idx << " ";
        }
    } else {
        cout << "Balanced" << endl;
        cout << "None" << endl;
    }
}
