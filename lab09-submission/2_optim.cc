#include <iostream>
#include <vector>
#include <climits>
using namespace std;

struct BRTreeNode
{
    int idx;//树节点之间的关系是通过idx来确定的
    int expireTime;
    char color; 
    BRTreeNode *parent;
    BRTreeNode *left;
    BRTreeNode *right;
    BRTreeNode(int x, int i) : expireTime(x), idx(i), color('R'), parent(NULL), left(NULL), right(NULL) {}
};

bool checkRedProperty(BRTreeNode* node){
    if(node == NULL) return true;//空节点视为黑色节点，满足红色性质
    if(node->color == 'R'){
        //如果当前节点是红色的，那么它的左右子节点必须都是黑色的
        if((node->left && node->left->color == 'R') || (node->right && node->right->color == 'R')){
            return false;//违反了红色性质
        }
    }
    //递归检查左右子树
    return checkRedProperty(node->left) && checkRedProperty(node->right);
}

//检查黑色高度性质，currentBlackCount记录当前路径上的黑色节点数量，blackHeight记录第一次到达叶子节点时的黑色节点数量
//blackHeight初始值为-1，传递引用是为了在第一次到达叶子节点时记录黑色节点数量，并在后续到达叶子节点时进行比较，确保所有路径上的黑色节点数量一致
//blackcurrent传递的是值拷贝，不会影响其他路径的计数
bool checkBlackHeight(BRTreeNode* node, int currentBlackCount, int& blackHeight){
    if(node == NULL){
        //到达叶子节点，检查当前路径上的黑色节点数量是否一致
        if(blackHeight == -1){
            blackHeight = currentBlackCount;//第一次到达叶子节点，记录黑色节点数量
        } else {
            return currentBlackCount == blackHeight;//后续到达叶子节点，必须与第一次记录的黑色节点数量一致
        }
        //第一次默认为合法，后续如果不一致则返回false
        return true;
    }
    //如果当前节点是黑色的，增加当前路径上的黑色节点数量
    if(node->color == 'B'){
        currentBlackCount++;
    }
    //递归检查左右子树
    return checkBlackHeight(node->left, currentBlackCount, blackHeight) && checkBlackHeight(node->right, currentBlackCount, blackHeight);
}

bool checkBST(BRTreeNode* node, long long low, long long high) {
    if (node == NULL) return true;
    if (node->expireTime <= low || node->expireTime >= high) return false;

    return checkBST(node->left, low, node->expireTime) &&
           checkBST(node->right, node->expireTime, high);
}

bool hasCycle(int u, vector<BRTreeNode*>& nodes, vector<int>& state) {
    if (u == 0) return false;
    if (state[u] == 1) return true;
    if (state[u] == 2) return false;

    state[u] = 1;
    if (nodes[u]->left && hasCycle(nodes[u]->left->idx, nodes, state)) return true;
    if (nodes[u]->right && hasCycle(nodes[u]->right->idx, nodes, state)) return true;
    state[u] = 2;
    return false;
}

void dfsMark(int u, vector<BRTreeNode*>& nodes, vector<bool>& seen) {
    if (u == 0 || seen[u]) return;
    seen[u] = true;
    if (nodes[u]->left) dfsMark(nodes[u]->left->idx, nodes, seen);
    if (nodes[u]->right) dfsMark(nodes[u]->right->idx, nodes, seen);
}

bool islegal(BRTreeNode* root, vector<BRTreeNode*>& nodes, int num_nodes){
    int blackHeight = -1;

    if (!checkBST(root, LLONG_MIN, LLONG_MAX)) return false;
    if (!checkRedProperty(root)) return false;
    if (!checkBlackHeight(root, 0, blackHeight)) return false;

    vector<int> state(num_nodes + 1, 0);
    for(int i = 1; i <= num_nodes; ++i){
        if(state[i] == 0 && hasCycle(i, nodes, state)){
            return false;
        }
    }

    vector<bool> seen(num_nodes + 1, false);
    dfsMark(1, nodes, seen);
    for(int i = 1; i <= num_nodes; ++i){
        if(!seen[i]) return false;
    }

    return true;
}

int main(){
    int num_nodes;
    cin >> num_nodes;

    /** @note point1:如果没有节点，直接输出YES */
    if(num_nodes == 0){
        cout <<"YES";
        return 0;
    }

    //num_nodes+1是为了让节点的idx从1开始，方便根据输入的idx来访问对应的节点
    // 先创建所有节点，并存储在一个数组中，方便后续建立关系
    vector<BRTreeNode*> nodes(num_nodes+1,nullptr);
    // 记录每个节点的左右子节点的idx，后续根据这些idx来建立树的结构
    vector<int> left(num_nodes+1,0);
    vector<int> right(num_nodes+1,0);

    // 读入每个节点的信息，并创建节点对象
    for(int i = 1; i <= num_nodes; i++){
        int expireTime;
        char color;
        int left_idx, right_idx;//如果没有左边或者右边的子节点，则对应的idx为0
        cin >> expireTime >> color >> left_idx >> right_idx;

        /** @note point2:如果根节点是红色的，直接输出NO */
        if(i == 1 && color == 'R'){
            cout << "NO";
            return 0;
        }


        nodes[i] = new BRTreeNode(expireTime, i);
        nodes[i]->color = color;
        left[i] = left_idx;
        right[i] = right_idx;
    }

    // 根据读入的左右子节点的idx来建立树的结构
    for(int i = 1; i <= num_nodes; i++){
        if(left[i] != 0){
            if(nodes[left[i]]->parent != NULL){
                /** @note point3:如果左子节点已经有父节点了，说明存在多个父节点指向同一个子节点，直接输出NO */
                cout << "NO";
                return 0;
            }
            nodes[i]->left = nodes[left[i]];
            nodes[left[i]]->parent = nodes[i];
        }
        if(right[i] != 0){
            if(nodes[right[i]]->parent != NULL){
                /** @note point3:如果右子节点已经有父节点了，说明存在多个父节点指向同一个子节点，直接输出NO */
                cout << "NO";
                return 0;
            }
            nodes[i]->right = nodes[right[i]];
            nodes[right[i]]->parent = nodes[i];
        }
    }
    // 现在树的结构已经建立好了，根节点就是nodes[1]
    BRTreeNode* root = nodes[1];
    if(islegal(root, nodes, num_nodes)){
        cout << "YES" << endl;
    } else {
        cout << "NO" << endl;
    }
}