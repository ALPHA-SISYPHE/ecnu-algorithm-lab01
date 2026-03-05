#include<iostream>
#include<vector>


void bubble_sort(std::vector<int>&arr,int& swap){
    int n = arr.size();
    swap = 0 ;
    for(int i = 0;i<n-1 ;i++){
        for(int j = 0 ; j< n - i -1;j++){
            if(arr[j]<arr[j+1]){
                int temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
                swap++;
            }
        }
    }
}

void print_Array(std::vector<int>&arr,int &swap){
    int i = 0;
    int n = arr.size();
    for(;i<n-1;i++){
        std::cout<<arr[i]<<' ' ;
    }
    std::cout<<arr[i]<<std::endl;
    std::cout<<swap;
}

int main(){
    std::vector<int> arr ;
    int loop;
    int swap = 0;

    std::cin >> loop ;
    for(int i = 0;i<loop;i++){
        int n;
        std::cin >> n;
        arr.push_back(n);
    }

    bubble_sort(arr, swap);

    print_Array(arr, swap);

    return 0;
}