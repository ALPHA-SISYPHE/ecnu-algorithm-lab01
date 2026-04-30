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

//dfs检查是否存在环路，如果存在环路则不是合法的红黑树
//对外判断成环的是栈底
bool isloop_node(BRTreeNode* node, vector<bool>& visited){
    if(node == NULL) return false;//空节点不构成环
    if(visited[node->idx]) return true;//如果当前节点已经被访问过，说明存在环
    visited[node->idx] = true;//标记当前节点为已访问
    //递归检查左右子树
    bool leftLoop = isloop_node(node->left, visited);
    bool rightLoop = isloop_node(node->right, visited);
    visited[node->idx] = false;//回退标记，允许其他路径访问该节点
    return leftLoop || rightLoop;//如果左右子树中任意一个存在环，则返回true
}

bool isloop_global(vector<BRTreeNode*>& nodes, vector<bool>& visited){
    for(size_t i = 1; i < nodes.size(); i++){
        if(!visited[i]){//如果当前节点未被访问过，说明它是一个新的连通分量的起点
            if(isloop_node(nodes[i], visited)){//从这个节点开始进行DFS检查是否存在环
                return true;//如果存在环，直接返回true
            }
        }
    }
    return false;//如果所有连通分量都没有环，返回false
}


//一个纯粹用来标记连通性的遍历函数
void mark_connected(BRTreeNode* node, vector<bool>& connected_visited){
    if(node == NULL) return;
    if(connected_visited[node->idx]) return; // 遇到已访问的直接返回，防止死循环
    
    connected_visited[node->idx] = true; // 永久标记
    mark_connected(node->left, connected_visited);
    mark_connected(node->right, connected_visited);
}

bool is_connected(vector<BRTreeNode*>& nodes){
    // 使用一个全新的 visited 数组，避免和判断环的数组混淆
    vector<bool> connected_visited(nodes.size(), false);
    
    mark_connected(nodes[1], connected_visited); // 从根节点开始遍历
    
    // 检查是否所有节点都被访问过
    for(size_t i = 1; i < nodes.size(); i++){
        if(!connected_visited[i]) return false;
    }
    return true;
}

bool checkBST(BRTreeNode* node, long long low, long long high) {
    if (node == NULL) return true;
    if (node->expireTime <= low || node->expireTime >= high) return false;

    return checkBST(node->left, low, node->expireTime) &&
           checkBST(node->right, node->expireTime, high);
}

bool islegal(BRTreeNode* root, vector<bool>& visited, vector<BRTreeNode*>& nodes){
    int blackHeight = -1;
    return checkBST(root, LLONG_MIN, LLONG_MAX) &&checkRedProperty(root) &&checkBlackHeight(root, 0, blackHeight) &&!isloop_global(nodes, visited) &&is_connected(nodes);
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

    // 记录节点是否被访问过，用于判断是否成环
    vector<bool> visited(num_nodes+1,false);//记录节点是否被访问过，防止死循环

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
    if(islegal(root, visited, nodes)){
        cout << "YES" << endl;
    } else {
        cout << "NO" << endl;
    }
}