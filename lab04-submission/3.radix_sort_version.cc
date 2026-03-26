#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;

// exp截断每一位
void counting_sort(vector<pair<int, int>> &A, vector<pair<int, int>> &B, int exp)
{
    int len = A.size();
    vector<int> C(10, 0);

    for (int i = 0; i < len; ++i)
    {
        int digit = (A[i].first / exp) % 10;
        C[digit]++;
    }

    for (int i = 1; i < 10; ++i)
    {
        C[i] += C[i - 1];
    }

    for (int i = len - 1; i >= 0; --i)
    {
        int digit = (A[i].first / exp) % 10;
        B[C[digit] - 1] = A[i];
        C[digit]--;
    }

    A.swap(B);
}

// 基数排序主逻辑：对<频率, TopicID>按频率升序排序
void radix_sort(vector<pair<int, int>> &arr)
{
    if (arr.empty())
        return;

    // 找到最大频率，确定需要处理的十进制位数
    int max_count = 0;
    for (const pair<int, int> &p : arr)
    {
        max_count = max(max_count, p.first);
    }

    // 临时数组
    vector<pair<int, int>> temp(arr.size());

    // 逐位调用计数排序
    for (int exp = 1; max_count / exp > 0; exp *= 10)
    {
        counting_sort(arr, temp, exp);
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, K;
    cin >> N >> K;

    // 哈希表统计每个TopicID的出现频率
    unordered_map<int, int> freq;
    freq.reserve(N);
    for (int i = 0; i < N; ++i)
    {
        int topic_id;
        cin >> topic_id;
        freq[topic_id]++;
    }

    // 转为<频率, TopicID>数组，用于基数排序
    vector<pair<int, int>> arr;
    arr.reserve(freq.size());
    for (const pair<int, int> &p : freq)
    {
        arr.emplace_back(p.second, p.first);
    }

    radix_sort(arr);

    //这里采用逆序输出
    if (K > 0 && !arr.empty())
    {
        cout << arr[arr.size() - 1].second;
        for (int i = 1; i < K && i < arr.size(); i++)
        {
            cout << " " << arr[arr.size() - 1 - i].second;
        }
    }
    return 0;
}