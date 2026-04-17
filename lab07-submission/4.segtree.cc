#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

struct Node {
    int match;           // 区间内已经匹配的括号对数
    int left_unmatched;  // 区间内未匹配的 '(' 数量
    int right_unmatched; // 区间内未匹配的 ')' 数量
};

const int MAXN = 100005;
Node tree[MAXN * 4]; //开4N保险
string s;

Node merge(const Node& left_child, const Node& right_child) {
    Node parent;
    int new_matches = min(left_child.left_unmatched, right_child.right_unmatched);//新增的匹配对数 = 左区间的未匹配 '(' 和 右区间的未匹配 ')' 的最小值
    parent.match = left_child.match + right_child.match + new_matches;
    parent.left_unmatched = left_child.left_unmatched + right_child.left_unmatched - new_matches;
    parent.right_unmatched = left_child.right_unmatched + right_child.right_unmatched - new_matches;
    return parent;
}

// 构建线段树
// node: 当前节点编号, l: 当前区间左端点, r: 当前区间右端点
void build(int node, int l, int r) {
    if (l == r) {
        tree[node].match = 0;
        if (s[l - 1] == '(') {//输入1，实际下标0，所以是l-1
            tree[node].left_unmatched = 1;
            tree[node].right_unmatched = 0;
        } else {
            tree[node].left_unmatched = 0;
            tree[node].right_unmatched = 1;
        }
        return;
    }
    
    int mid = l + (r - l) / 2;
    int left_node = 2 * node;
    int right_node = 2 * node + 1;
    
    // 递归构建左子树和右子树
    build(left_node, l, mid);
    build(right_node, mid + 1, r);
    
    // 用左右子树的信息更新当前节点
    tree[node] = merge(tree[left_node], tree[right_node]);
}

// 查询区间 [ql, qr] 的匹配对数
Node query(int node, int l, int r, int ql, int qr) {
    if (ql > r || qr < l) {//安全检查，查询区间和当前节点区间没有交集
        return {0, 0, 0};
    }

    //从大区间到小区间，如果当前节点区间完全包含查询区间，直接返回当前节点的信息
    if (ql <= l && r <= qr) {
        return tree[node];
    }
    
    int mid = l + (r - l) / 2;
    Node left_result = query(2 * node, l, mid, ql, qr);
    Node right_result = query(2 * node + 1, mid + 1, r, ql, qr);
    
    return merge(left_result, right_result);
}

int main(){
    
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    cin >> s;
    int n = s.size();
    build(1, 1, n); // 构建线段树，节点编号从1开始，区间从1到n

    int q;
    cin >> q;
    while (q--) {
        int a, b;
        cin >> a >> b;
        Node result = query(1, 1, n, a, b);
        cout << result.match * 2 << endl; // 每对括号贡献2个字符
    }
}