#include<iostream>
#include<vector>

using namespace std;
vector<int> slide_max(vector<int>&arr,int k){
    //结果数组
    vector<int> res;
    //单调递减队列，记录的是元素的下标,小于窗格下界弹出
    vector<int> id_queue;

    for(int i = 0;i<arr.size();i++){
        //弹出小于窗格下界的元素
        while(!id_queue.empty()&&id_queue.front()<=i-k){
            id_queue.erase(id_queue.begin());
        }
        //弹出小于当前元素的元素
        while(!id_queue.empty()&&arr[id_queue.back()]<=arr[i]){
            id_queue.pop_back();
        }
        //加入当前元素!!!先弹出了再加入
        id_queue.push_back(i);

        //滚动窗口形成，开始记录结果
        if(i>=k-1){
            res.push_back(arr[id_queue.front()]);
        }
    }

    return res;
    
}

int main(){
    int n,k;
    cin >> n >> k;
    vector<int> arr(n);
    for(int i = 0;i<n;i++){
        cin >> arr[i];
    }

    vector<int> res = slide_max(arr,k);
    for(int num:res){
        cout << num << " ";
    }
}