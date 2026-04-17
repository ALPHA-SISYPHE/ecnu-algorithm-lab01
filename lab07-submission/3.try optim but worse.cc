#include<iostream>
#include<vector>
using namespace std;

// 二分搜索对应元素，返回元素在sorted dict中的元素下标值，没有返回-1
int binary_search(int num, vector<int> &sorted_dict){
    int left = 0;
    int right = sorted_dict.size() - 1;
    
    while (left <= right) {
        int mid = left + (right - left) / 2; 
        
        if (sorted_dict[mid] == num) {
            return mid; 
        } else if (sorted_dict[mid] < num) {
            left = mid + 1; 
        } else {
            right = mid - 1; 
        }
    }
    return -1; // 未找到
}

// sorted_dict新元素添加在最后，在主函数的应用是来一个排序一个
void insert_sort(vector<int> &sorted_dict){
    int n = sorted_dict.size();
    if (n <= 1) return; // 只有一个元素或为空，不需要排序
    
    // 刚加入的元素在最后一位，作为待插入的 key
    int key = sorted_dict[n - 1]; 
    int j = n - 2;
    
    // 将大于 key 的元素统一向后移动一位，为 key 腾出空间
    while (j >= 0 && sorted_dict[j] > key) {
        sorted_dict[j + 1] = sorted_dict[j];
        j--;
    }
    
    // 将 key 放入正确的位置
    sorted_dict[j + 1] = key;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int M,N;
    int count = 0;//外部查找次数
    cin >> M >> N;

    vector<int> cache;//缓存队列
    vector<int> sorted_dict;//
    for(int i = 0;i<N;i++){
        int num;
        cin >> num;
        //先检查缓存中有没有这个数据
        //如果有，说明不用外部查找
        int found = binary_search(num,sorted_dict);
        if(found!=-1){
            continue;
        }
        else{
            //如果没有，说明需要外部查找
            count++;
            //如果缓存满了，删除最早进入的元素
            if(cache.size()==M){
                int del = cache.front();
                sorted_dict.erase(sorted_dict.begin()+binary_search(del,sorted_dict));
                cache.erase(cache.begin());
            }
            //将新元素加入缓存
            cache.emplace_back(num);
            sorted_dict.emplace_back(num);
            insert_sort(sorted_dict);
        }
    }
    cout << count ;
}