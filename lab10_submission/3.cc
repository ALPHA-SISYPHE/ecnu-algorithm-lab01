#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
struct BRTreeNode
{
    int color; // 0 for black, 1 for red
    int idx; // Node index for output
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
    if(node == NULL) return 1; // Null nodes are considered black
    int left_black_height = check_balance(node->left, unbalanced_nodes);
    int right_black_height = check_balance(node->right, unbalanced_nodes);
    if(left_black_height!=right_black_height||left_black_height==-1||right_black_height==-1){
        unbalanced_nodes.push_back(node->idx);
        insert_sort(unbalanced_nodes);
        return -1; // 标记报废，以后有这个节点的子树都不合法了
    }
    return left_black_height + (node->color == 0 ? 1 : 0); // If current node is black, add 1 to black height
}

BRTreeNode* find_root(vector<BRTreeNode*>& nodes) {
    for (BRTreeNode* node : nodes) {
        if (node != NULL && node->parent == NULL) {
            return node; // Found the root node
        }
    }
    return NULL; // Should not happen if input is valid
}
int main(){
    //加速
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int n;
    cin >> n;

    vector<BRTreeNode*> nodes(n+1); // 1-based indexing
    vector<int> left(n+1);
    vector<int> right(n+1);

    for(int i = 1; i <= n; i++) {
        nodes[i] = new BRTreeNode(0); // Initialize with default color 0 (black)
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

    //find the root node (the one with no parent)
    BRTreeNode* root = find_root(nodes);
    check_balance(root, unbalanced_nodes); // Start from the root node
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