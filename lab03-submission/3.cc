#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
// 维护最小堆
void min_heapify(vector<int> &arr, int i, int size)
{
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    int min;

    if (left < size && arr[i] > arr[left])
    {
        min = left;
    }
    else
    {
        min = i;
    }
    if (right < size && arr[min] > arr[right])
    {
        min = right;
    }

    if (min != i)
    {
        swap(arr[i], arr[min]);
    }
    else
    {
        return;
    }

    min_heapify(arr, min, size);
}

void build_heap(vector<int> &arr)
{
    int size = arr.size();
    int i = (arr.size() / 2) - 1;

    for (; i >= 0; i--)
    {
        min_heapify(arr, i, size);
    }
}

void heap_sort(vector<int> &arr)
{
    int size = arr.size();
    // 这里不用堆化了，之前已经做过了
    //build_heap(arr);

    for (int i = size - 1; i > 0; i--)
    {
        swap(arr[0], arr[i]);
        // 这里不可以直接用vector的pop，因为这会导致元素从vector中的彻底删除
        size--;
        min_heapify(arr, 0, size);
    }
}

int main()
{
    int n, k;
    cin >> n;
    cin >> k;
    vector<int> arr(k);

    // 先读取3个进行堆排序
    for (int i = 0; i < k; i++)
    {
        cin >> arr[i];
    }

    //这里是构造小顶堆，排序过后就不是小顶堆了
    build_heap(arr);

    // 继续读取后面的
    for (int i = k; i < n; i++)
    {
        int cmp;
        cin >> cmp;

        if(cmp>=arr[0]){
            arr[0] = cmp;
            min_heapify(arr,0,k);
        }
        
    }

    //所有读取完后开始小数据量排序
    //最小优先下沉后，直接实现的是
    heap_sort(arr);

    for (int i = 0; i < k - 1; i++)
    {
        cout << arr[i] << ' ';
    }
    cout << arr[k-1];
}