#include <iostream>
#include <vector>

using namespace std;

void dfs(int u, const vector<vector<int>>& tree) {
    for (int v : tree[u]) {
        dfs(v, tree);
    }

    cout << u << ' ';
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<vector<int>> tree(n + 1);

    for (int i = 2; i <= n; i++)
    {
        int fa;
        cin >> fa;
        tree[fa].push_back(i); 
    }

    dfs(1, tree);

    return 0;
}