#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
// 维护最大堆的性质
void max_heapify(vector<int> &arr, int i,int size)
{
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    int largest;

    if (left < size && arr[i] < arr[left])
    {
        largest = left;
    }
    else
    {
        largest = i;
    }
    if (right < size && arr[largest] < arr[right])
    {
        largest = right;
    }

    if (largest != i)
    {
        swap(arr[i], arr[largest]);
    }
    else
    {
        return;
    }

    max_heapify(arr, largest,size);
}

void build_heap(vector<int> &arr)
{
    int size = arr.size();
    int i = (arr.size() / 2) - 1;

    for (; i >= 0; i--)
    {
        max_heapify(arr, i,size);
    }
}

void heap_sort(vector<int> &arr)
{
    int size = arr.size();
    // 先堆化
    build_heap(arr);

    for (int i = size - 1; i > 0; i--)
    {
        swap(arr[0], arr[i]);
        size--;
        max_heapify(arr, 0,size);
    }
}

int main()
{
    int n;
    cin >> n;
    vector<int> arr(n);
    for (int i = 0; i < n; i++)
    {
        cin >> arr[i];
    }

    heap_sort(arr);

    for (int i = 0; i < n - 1; i++)
    {
        cout << arr[i] << ' ';
    }
    cout << arr[n - 1];
}
