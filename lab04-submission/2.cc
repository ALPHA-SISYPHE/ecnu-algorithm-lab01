#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ctime>

using namespace std;

// 插入排序加速收尾（这里降序）
void insertion_sort(vector<int> &arr, int low, int high)
{
    for (int i = low + 1; i <= high; i++)
    {
        int key = arr[i];
        int j = i - 1;
        while (j >= low && arr[j] < key)
        {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

// 三数取中：返回中位数的索引，并把它放到最高位
int m_3(vector<int> &arr, int low, int high)
{
    int mid = low + (high - low) / 2;
    // 简单的冒泡排序三个数，把中位数放到 mid
    if (arr[low] < arr[mid])
        swap(arr[low], arr[mid]);
    if (arr[low] < arr[high])
        swap(arr[low], arr[high]);
    if (arr[mid] < arr[high])
        swap(arr[mid], arr[high]);
    // 现在把mid放在最高位上
    swap(arr[mid], arr[high]);
    return arr[high]; // 返回的值将作为三数随机的pivot
}

// 三路快排的partition 算法
pair<int, int> three_way_partition(vector<int> &arr, int low, int high)
{
    // 先用m_3取pivot
    int pivot = m_3(arr, low, high);

    // 利用索引，把数据划分为大于，小于，等于三段
    int lptr = low;
    int rptr = high;
    int mptr = low;

    while (mptr <= rptr)
    {
        if (arr[mptr] > pivot)
        {
            swap(arr[mptr], arr[lptr]);
            lptr++;
            mptr++;
        }
        else if (arr[mptr] < pivot)
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
int quick_select(vector<int> &arr, int low, int high, int k_id)
{
    while (low < high)
    {
        // 小数据量直接插入排序，快速收尾
        if (high - low + 1 <= 15)
        {
            insertion_sort(arr, low, high);
            return arr[k_id];
        }

        // 三路划分
        pair<int, int> p = three_way_partition(arr, low, high);
        int l = p.first;
        int r = p.second;

        // 只处理包含目标的区间，直接舍弃另一部分
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
            // 命中等于pivot的区间，直接返回结果
            return arr[k_id];
        }
    }
    // 区间只剩一个元素，直接返回
    return arr[k_id];
}

int main()
{
    ios::sync_with_stdio(false); // 加速 cin
    cin.tie(nullptr);            // 解除 cin 和 cout 的绑定

    int n, m;
    cin >> n;
    cin >> m;
    vector<int> arr(n);
    for (int i = 0; i < n; i++)
    {
        cin >> arr[i];
    }

    quick_select(arr, 0, n - 1,m);

    cout << arr[m-1];
    return 0;
}