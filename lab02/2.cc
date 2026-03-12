#include<iostream>
#include<vector>

int calculate_cross(std::vector<int>&arr,int l,int r){
    int mid = (r-l)/2+l;
    int left_max,right_max;
    left_max = right_max;
    int leftsum,right_sum;
    leftsum = right_sum = 0;
    for(int i = mid;i>=l;i--){
        leftsum+=arr[i];
        if(i == mid)
        left_max = arr[mid];
        else
        left_max = left_max>leftsum?left_max:leftsum;
    }

    for(int i = mid+1;i<=r;i++){
        right_sum+=arr[i];
        if(i==mid+1)
        right_max = arr[mid+1];
        else
        right_max = right_max>right_sum?right_max:right_sum;
    }

    return right_max+left_max;

    
}

int sum_max(std::vector<int>&arr,int l,int r){
    if(l>=r){
        return arr[r];
    }

    int mid = (r-l)/2+l;
    int left = sum_max(arr,l,mid);
    int right = sum_max(arr,mid+1,r);
    int cross = calculate_cross(arr,l,r);

    int max = left>right?left:right;
    max = max>cross?max:cross;
    return max;
}

int main()
{
    int n;
    std::cin >> n;
    std::vector<int> arr(n);
    int num;
    for (int i = 0; i < n; i++)
    {
        std ::cin >> arr[i];
    }

    int max = sum_max(arr,0,n-1);

    std::cout << max;
  
}