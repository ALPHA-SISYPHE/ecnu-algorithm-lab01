#include<iostream>
#include<vector>

using namespace std;
int main(){
    int n;
    cin>>n;
    vector<int> T(n);
    vector<int> ans(n,0);
    vector<int> stack(n);

    for(int i = 0;i<n;i++){
        cin >> T[i];
    }

    for(int i = 0;i<n;i++){
       while(!stack.empty() && T[stack.back()] < T[i]){
           int idx = stack.back();
           stack.pop_back();
           ans[idx] = i - idx;
        }
        stack.emplace_back(i);
    }

    for(int i=0;i<n;i++){
        cout<<ans[i]<<" ";
    }
}