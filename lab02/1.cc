#include <iostream>
#include <vector>

void merge(std::vector<int> &arr, int l, int r, int mid)
{
    std::vector<int> temp(r - l + 1);
    int left = l;
    int right = mid+1;
    int tmp = 0;

    while (left <= mid && right <= r)
    {
        if (arr[left] <= arr[right])
        {
            temp[tmp++] = arr[left++];
        }
        else
            temp[tmp++] = arr[right++];
    }

    while (left <= mid)
    {
        temp[tmp++] = arr[left++];
    }

    while (right<=r)
    {
        temp[tmp++] = arr[right++];
    }

    for(int i = 0;i<(r-l+1);i++){
        arr[l+i] = temp[i];
    }
}
void merge_sort(std::vector<int> &arr, int l, int r){
    if(l>=r)
    return;
    int mid = (r-l)/2+l;

    merge_sort(arr,l,mid);
    merge_sort(arr,mid+1,r);
    merge(arr,l,r,mid);
}

int main()
{
    int n;
    std::cin >> n;
    std::vector<int> arr(n);
    int num;
    for (int i = 0; i < n; i++)
    {
        std ::cin >> num;
        arr[i] = num;
    }

    merge_sort(arr,0,n-1);
    
    for(int i = 0;i<n-1;i++){
        std :: cout << arr[i] <<' ';
    }
    std::cout << arr[n-1];
}