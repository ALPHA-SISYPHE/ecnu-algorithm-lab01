#include <iostream>
#include <queue>
#include <unordered_set>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int M, N;
    cin >> M >> N;

    int count = 0;             // 记录外部查找次数
    queue<int> cache_queue;    // 使用队列维护进入缓存的先后顺序
    unordered_set<int> cache_set; // 使用哈希表实现 O(1) 的快速查找

    for (int i = 0; i < N; i++) {
        int word;
        cin >> word;

        if (cache_set.find(word) != cache_set.end()){;
            continue;
        }


        count++;

        // 3. 如果缓存已经满了，执行淘汰逻辑
        if (cache_queue.size() == M) {
            // 获取最早进入缓存的元素（队头元素）
            int oldest_word = cache_queue.front();
            
            // 将其从队列中弹出 (O(1) 复杂度，不需要平移数据)
            cache_queue.pop();
            
            // 同步将其从哈希表中移除
            cache_set.erase(oldest_word);
        }

        // 4. 将新单词加入缓存
        cache_queue.push(word);
        cache_set.insert(word);
    }

    // 输出最终查询次数
    cout << count ;

}