#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <unordered_map>

using namespace std;

// 插入排序加速收尾（这里降序）
void insertion_sort(vector<pair<int, int>> &arr, int low, int high)
{
    for (int i = low + 1; i <= high; i++)
    {
        pair<int, int> key = arr[i];
        int j = i - 1;
        while (j >= low && arr[j].second < key.second)
        {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

// 三数取中：返回中位数的索引，并把它放到最高位
int m_3(vector<pair<int, int>> &arr, int low, int high)
{
    int mid = low + (high - low) / 2;
    // 简单的冒泡排序三个数，把中位数放到 mid
    if (arr[low].second < arr[mid].second)
        swap(arr[low], arr[mid]);
    if (arr[low].second < arr[high].second)
        swap(arr[low], arr[high]);
    if (arr[mid].second < arr[high].second)
        swap(arr[mid], arr[high]);
    // 现在把mid放在最高位上
    swap(arr[mid], arr[high]);
    return arr[high].second; // 返回的值将作为三数随机的pivot
}

// 三路快排的partition 算法
pair<int, int> three_way_partition(vector<pair<int, int>> &arr, int low, int high)
{
    // 先用m_3取pivot
    int pivot = m_3(arr, low, high);

    // 利用索引，把数据划分为大于，小于，等于三段
    int lptr = low;
    int rptr = high;
    int mptr = low;

    while (mptr <= rptr)
    {
        if (arr[mptr].second > pivot)
        {
            swap(arr[mptr], arr[lptr]);
            lptr++;
            mptr++;
        }
        else if (arr[mptr].second < pivot)
        {
            swap(arr[mptr], arr[rptr]);
            rptr--;
            // 这里的mptr不用递增
        }
        else
            mptr++; // 等于直接递增
    }
    return {lptr, rptr};
}

// 尾递归优化的快速排序
void quick_sort(vector<pair<int, int>> &arr, int low, int high)
{
    while (low < high)
    {

        // 最后的小数据量直接用插入排序加速收尾
        if (high - low + 1 <= 15)
        {
            insertion_sort(arr, low, high);
            return;
        }

        // 划分3区：
        pair<int, int> p = three_way_partition(arr, low, high);
        int l = p.first;
        int r = p.second;

        // 尾递归优化：每轮循环只处理少的一半的数据量，剩下的一半留给迭代下一轮做，这样减小栈溢出风险
        if (l - low < high - r)
        {
            quick_sort(arr, low, l - 1); // 递归左边
            low = r + 1;                 // 迭代更新，处理右边
        }
        else
        {
            quick_sort(arr, r + 1, high);
            high = l - 1;
        }
        // 中间的留着不动
    }
}

int main()
{
    ios::sync_with_stdio(false); // 加速 cin
    cin.tie(nullptr);            // 解除 cin 和 cout 的绑定

    int N, K;
    cin >> N >> K;

    // 哈希表统计每个TopicID的出现频率
    unordered_map<int, int> freq;
    for (int i = 0; i < N; i++)
    {
        int topic_id;
        cin >> topic_id;
        freq[topic_id]++;
    }

    // 转为vector,便于排序
    vector<pair<int, int>> arr;
    for (const pair<int, int> &p : freq)
    {
        arr.emplace_back(p.first, p.second);
    }

    // 直接对统计好的频率排序
    if (!arr.empty())
    {
        quick_sort(arr, 0, arr.size() - 1);
    }

    if (K > 0 && !arr.empty())
    {
        cout << arr[0].first;
        for (int i = 1; i < K && i < arr.size(); i++)
        {
            cout << " " << arr[i].first;
        }
    }
    return 0;
}