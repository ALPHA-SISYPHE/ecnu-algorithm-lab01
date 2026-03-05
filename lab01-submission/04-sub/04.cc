#include <iostream>
#include <vector>
#include <random>
#include <chrono>
#include <iomanip>      // for std::fixed, std::setprecision
#include <fstream>      // 正确头文件：ofstream 属于 fstream
#include <string>       // 需要用到 std::string, std::to_string
#include <tuple>        // 需要用到 std::tuple, std::tie 等

using namespace std;  
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
        if (arr[i].price <= arr[j].price)
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
        arr[l+t] = temp[t];
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

std::vector<Stock> generate_random_stocks(int n) {
    std::vector<Stock> arr(n);
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(1, 10000);
    for (int i = 0; i < n; ++i) {
        arr[i].id = i + 1;
        arr[i].price = dist(gen);
    }
    return arr;
}


int main() {
    std::vector<long long> sizes = {100, 1000, 10000, 100000, 1000000};

    std::vector<std::tuple<long long, double, double>> time_results;

    cout << "开始测试...\n";

    for (auto n : sizes) {
        cout << "规模 " << n << " ... ";

        auto original = generate_random_stocks(static_cast<int>(n));

        // QuickSort 时间测量
        double q_time = 0.0;
        for (int rep = 0; rep < 5; ++rep) {
            auto copy = original;
            auto start = std::chrono::high_resolution_clock::now();
            Quick_Sort(copy, 0, static_cast<int>(n) - 1);
            auto end = std::chrono::high_resolution_clock::now();
            q_time += std::chrono::duration<double, std::milli>(end - start).count();
        }
        q_time /= 5.0;

        // MergeSort 时间测量
        double m_time = 0.0;
        for (int rep = 0; rep < 5; ++rep) {
            auto copy = original;
            auto start = std::chrono::high_resolution_clock::now();
            merge_sort(copy, 0, static_cast<int>(n) - 1);
            auto end = std::chrono::high_resolution_clock::now();
            m_time += std::chrono::duration<double, std::milli>(end - start).count();
        }
        m_time /= 5.0;

        time_results.emplace_back(n, q_time, m_time);

        cout << "完成\n";

        // 只对 100 和 1000 输出 price 文件
        if (n == 100 || n == 1000) {
            // QuickSort 结果
            {
                auto arr = original;
                Quick_Sort(arr, 0, static_cast<int>(n) - 1);

                string filename = "price_quick_" + to_string(n) + ".txt";
                ofstream out(filename);
                if (!out.is_open()) {
                    cerr << "无法创建文件: " << filename << "\n";
                    continue;
                }
                out << "id price\n";
                for (const auto& s : arr) {
                    out << s.id << " " << s.price << "\n";
                }
                out.close();
                cout << "  已生成: " << filename << "\n";
            }

            // MergeSort 结果
            {
                auto arr = original;
                merge_sort(arr, 0, static_cast<int>(n) - 1);

                string filename = "price_merge_" + to_string(n) + ".txt";
                ofstream out(filename);
                if (!out.is_open()) {
                    cerr << "无法创建文件: " << filename << "\n";
                    continue;
                }
                out << "id price\n";
                for (const auto& s : arr) {
                    out << s.id << " " << s.price << "\n";
                }
                out.close();
                cout << "  已生成: " << filename << "\n";
            }
        }
    }

    // 写入时间对比 CSV
    string time_csv = "sort_time_comparison.csv";
    ofstream csv_out(time_csv);
    if (!csv_out.is_open()) {
        cerr << "无法创建时间 CSV 文件\n";
        return 1;
    }

    csv_out << "scale,QuickSort_ms,MergeSort_ms\n";
    for (const auto& [scale, qt, mt] : time_results) {
        csv_out << scale << ","
                << fixed << setprecision(3) << qt << ","
                << fixed << setprecision(3) << mt << "\n";
    }
    csv_out.close();

    cout << "\n所有测试完成！\n";

    return 0;
}