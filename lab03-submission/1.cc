#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
//维护最大堆的性质
void max_heapify(vector<int>&arr,int i){
    int size = arr.size(); 
    int left = 2*i+1;
    int right = 2*i+2;
    int largest;
    
    if(left<size&&arr[i]<arr[left]){
        largest = left;
    }
    else{
        largest = i;
    }
    if(right<size&&arr[largest]<arr[right]){
        largest = right;
    }

    if(largest!=i){
        swap(arr[i],arr[largest]);
    }
    else{
        return;
    }

    max_heapify(arr,largest);
    
}

void build_heap(vector<int>&arr){
    int i = (arr.size()/2)-1;

    for(;i>=0;i--){
        max_heapify(arr,i);
    }
}

int main(){
    int n;
    cin >> n ;
    vector<int> arr(n);
    for(int i = 0;i<n;i++){
        cin>>arr[i];
    }

    build_heap(arr);

    for(int i = 0;i<n-1;i++){
        cout << arr[i] <<' ';
    }
    cout<<arr[n-1];

}