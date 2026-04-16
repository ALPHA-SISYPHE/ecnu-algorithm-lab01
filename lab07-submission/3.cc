#include<iostream>
#include<vector>
#include<unordered_set>
using namespace std;
int main(){
    int count = 0;
    int M, N;
    cin >> M >> N;
    vector<int> nums;//缓存队列
    unordered_set<int> set;//哈希表，存储队列中的元素

    for(int i = 0;i<N;i++){
        int num;
        cin >> num;
        //先检查缓存中有没有这个数据
        //如果有，说明不用外部查找
        if(set.find(num)!=set.end()){
            continue;
        }
        else{
            //如果没有，说明需要外部查找
            count++;

            //如果缓存满了，删除最早进入的元素
            if(nums.size()==M){
                set.erase(nums[0]);
                nums.erase(nums.begin());
            }

            //将新元素加入缓存和哈希表
            nums.push_back(num);
            set.insert(num);
        }
    }
    cout << count;
}