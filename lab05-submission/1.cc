#include <iostream>
#include <vector>
#include<utility>
#include<algorithm>

using namespace std;

// 插入排序加速收尾（这里升序）
void insertion_sort(vector<int> &arr, int low, int high)
{
    for (int i = low + 1; i <= high; i++)
    {
        int key = arr[i];
        int j = i - 1;
        while (j >= low && arr[j] > key)
        {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

pair<int, int> three_way_partition(vector<int> &a, int pivot,int low,int high){
    int lt = low;
    int gt = high;
    int mt = low;
    while (mt <= gt){
        if (a[mt] < pivot){
            swap(a[lt], a[mt]);
            lt++;
            mt++;
        }
        else if (a[mt] > pivot){
            swap(a[mt], a[gt]);
            gt--;
        }
        else{
            mt++;
        }
    }
    return {lt, gt};
}

int bfprt(vector<int> &a, int k,int low,int high){

    int n = high - low + 1;
    //小数据量加速收尾的递归终止条件
    //如果长度小于5，直接排序返回第k小元素
    if (n <= 5) {
        insertion_sort(a, low, high);
        return a[k];
    }

    /*---------------------------------大于5的情况---------------------------------*/
    //大于5的情况，将数组分成5个一组，每组排序后取中位数
    vector<int> medians;
    for (int i = low; i <= high; i += 5) {
        int right = min(i + 4, high);
        insertion_sort(a, i, right);
        int median_idx = i + (right - i) / 2;
        medians.emplace_back(a[median_idx]);
    }
    //递归调用bfprt，找到中位数数组的中位数
    int pivot = bfprt(medians, medians.size() / 2, 0, medians.size() - 1);

    //用partition划分三部分
    pair<int, int> partition_result = three_way_partition(a, pivot,low,high);
    int lt = partition_result.first;
    int gt = partition_result.second;
    if (k < lt){
        return bfprt(a, k, low, lt - 1);
    }
    else if (k > gt){
        return bfprt(a, k, gt + 1, high);
    }
    else{
        return a[k];
    }
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n,k;
    cin >> n >> k;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    cout << bfprt(a, k-1, 0, n - 1) << endl;
}