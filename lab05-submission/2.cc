#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main() {
    int n;
    vector<int> orders;
    cin >> n ;

    for (int i = 0; i < n; i++) {
        string s;
        cin >> s;
        if (s == "ADD") {
            int x;
            cin >> x;
            orders.push_back(x);
        } 
        else if (s == "CANCEL") {
            if (!orders.empty()) {
                orders.pop_back();
            }
        } 
        else if (s == "QUERY") {
            if (orders.empty()) {
                cout << "EMPTY"<<endl;
            } 
            else {
                cout << orders.back() << endl;
            }
        }
    } 
    
    return 0;
} 