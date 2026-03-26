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

void quick_select(vector<pair<int, int>> &arr, int low, int high, int k_id)
{
    while (low < high)
    {
        if (high - low + 1 <= 15)
        {
            insertion_sort(arr, low, high);
            return;
        }
        pair<int, int> p = three_way_partition(arr, low, high);
        int l = p.first;
        int r = p.second;
        if (k_id < l)
        {
            high = l - 1; 
        }
        else if (k_id > r)
        {
            low = r + 1; 
        }
        else
        {
            return; 
        }
    }
}

int main()
{

    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, K;
    cin >> N >> K;
    
    unordered_map<int, int> freq;
    for (int i = 0; i < N; i++)
    {
        int topic_id;
        cin >> topic_id;
        freq[topic_id]++;
    }

    vector<pair<int, int>> arr;
    for (const auto &p : freq)
    {
        arr.emplace_back(p.first, p.second);
    }

    if (!arr.empty() && K > 0)
    {
    
        quick_select(arr, 0, arr.size() - 1, K - 1);
        cout << arr[0].first;
        for (int i = 1; i < K && i < arr.size(); i++)
        {
            cout << " " << arr[i].first;
        }
    }

    return 0;
}