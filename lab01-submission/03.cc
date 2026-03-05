#include <iostream>
#include <vector>
typedef struct
{
    int id;
    int price;
} Stock;

int q_slice(std::vector<Stock> &arr, int l, int r)
{
    int pivot = arr[r].price;
    int i = l - 1; // less_ptr
    int j = l;     // larger_ptr
    while (j < r)
    {
        if (arr[j].price < pivot)
        {
            i++;
            Stock temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
        j++;
    }
    Stock temp = arr[i + 1];
    arr[i + 1] = arr[r];
    arr[r] = temp;
    return i + 1;
}

void Quick_Sort(std::vector<Stock> &arr, int l, int r)
{
    if (l >= r)
        return;

    int p = q_slice(arr, l, r);
    Quick_Sort(arr, l, p - 1);
    Quick_Sort(arr, p + 1, r);
}

void merge(std::vector<Stock> &arr, int l, int r)
{
    std::vector<Stock> temp(r - l + 1);
    int mid = l + (r - l) / 2;
    int i = l;
    int j = mid + 1;
    int k = 0;
    while (i <= mid && j <= r)
    {
        if (arr[i].price <= arr[j].price)//归并排序优先保证左边小于等于有助于稳定性的提升
        {
            temp[k++] = arr[i++];
        }
        else{
            temp[k++] = arr[j++];
        }
    }

    while (i<=mid)
    {
       temp[k++] = arr[i++];
    }

    while (j<=r)
    {
        temp[k++] = arr[j++];
    }
    
    for(int t = 0;t<r-l+1;t++){
        arr[l+t] = temp[t];//#########注意最后的拷贝逻辑
    }
    
}

void merge_sort(std::vector<Stock> &arr, int l, int r){
    if(l>=r)
    return;

    int mid = l + (r - l) / 2;
    merge_sort(arr,l,mid);
    merge_sort(arr,mid+1,r);
    merge(arr,l,r);
}

void print_array(std::vector<Stock>&arr){
    int n = arr.size();
    for(int i = 0;i<n-1;i++){
        std::cout << arr[i].id <<' ';
    }
    std::cout << arr[n-1].id;
    return;
}

int main()
{
    int n;
    std::cin >> n;

    std::vector<Stock> arr(n);
    for (int i = 0; i < n; i++)
    {
        std::cin >> arr[i].id;
        std::cin >> arr[i].price;
    }
    
    std::vector<Stock> arr2(n);
    for(int i = 0;i<n;i++){
        arr2[i] = arr[i];
    }

    Quick_Sort(arr,0,n-1);
    print_array(arr);
    std::cout << std::endl;


    merge_sort(arr2,0,n-1);
    print_array(arr2);
    return 0;
}