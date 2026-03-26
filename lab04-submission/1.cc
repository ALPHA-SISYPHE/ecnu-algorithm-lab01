#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ctime>

using namespace std;

//插入排序加速收尾（这里降序）
void insertion_sort(vector<int> &arr, int low, int high) {
    for (int i = low + 1; i <= high; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= low && arr[j] < key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

//三数取中：返回中位数的索引，并把它放到最高位
int m_3(vector<int> &arr, int low, int high){
    int mid = low + (high - low) / 2;
    // 简单的冒泡排序三个数，把中位数放到 mid
    if (arr[low] < arr[mid]) swap(arr[low], arr[mid]); 
    if (arr[low] < arr[high]) swap(arr[low], arr[high]);
    if (arr[mid] < arr[high]) swap(arr[mid], arr[high]);
    //现在把mid放在最高位上
    swap(arr[mid], arr[high]);
    return arr[high];//返回的值将作为三数随机的pivot
}

//三路快排的partition 算法
pair<int, int> three_way_partition(vector<int> &arr, int low, int high) {
    //先用m_3取pivot
    int pivot = m_3(arr,low,high);

    //利用索引，把数据划分为大于，小于，等于三段
    int lptr = low;
    int rptr = high;
    int mptr = low;

    while(mptr<=rptr){
        if(arr[mptr]>pivot){
            swap(arr[mptr],arr[lptr]);
            lptr++;
            mptr++;
        }
        else if(arr[mptr]<pivot){
            swap(arr[mptr],arr[rptr]);
            rptr--;
            //这里的mptr不用递增
        }
        else
        mptr++;//等于直接递增
    }
    return {lptr, rptr};
}

//尾递归优化的快速排序
void quick_sort(vector<int> &arr, int low, int high){
    while(low<high){

        //最后的小数据量直接用插入排序加速收尾
        if (high - low + 1 <= 15) {
            insertion_sort(arr, low, high);
            return;
        }

        //划分3区：
        pair<int, int> p = three_way_partition(arr, low, high);
        int l = p.first;
        int r = p.second;

        //尾递归优化：每轮循环只处理少的一半的数据量，剩下的一半留给迭代下一轮做，这样减小栈溢出风险
        if(l-low<high-r){
            quick_sort(arr,low,l-1);//递归左边
            low = r+1;//迭代更新，处理右边
        }
        else{
            quick_sort(arr,r+1,high);
            high = l-1;
        }
        //中间的留着不动

    }
}

int main() {    
    ios::sync_with_stdio(false); // 加速 cin
    cin.tie(nullptr);             // 解除 cin 和 cout 的绑定

    int n;
    cin >> n;
    vector<int> arr(n);
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }

    quick_sort(arr, 0, n - 1);

    for (int i = 0; i < n; i++) {
        cout << arr[i];
        if (i < n - 1) cout << ' ';
    }
    return 0;
}