#include <iostream>
#include <vector>

void insert_sort(std::vector<int> &arr)
{
    int n = arr.size();
    for (int i = 1; i < n; i++)
    {
        int key = arr[i];
        int j = i;
        while (j > 0 && arr[j - 1] > key)
        {
            int temp = arr[j];
            arr[j] = arr[j - 1];
            arr[j - 1] = temp;
            j--;
        }
        int k = 0;
        for(;k<=i-1;k++){
                std::cout<<arr[k]<<' ';
            }
            std::cout<<arr[k]<<std::endl;
    }
}

int main()
{
    std::vector<int> arr;
    int loop;
    int swap = 0;

    std::cin >> loop;
    for (int i = 0; i < loop; i++)
    {
        int n;
        std::cin >> n;
        arr.push_back(n);
    }

    insert_sort(arr);

    return 0;
}