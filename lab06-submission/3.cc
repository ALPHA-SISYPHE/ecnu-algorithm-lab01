#include<iostream>
#include<list>
#include<vector>

using namespace std;

void inverse_partition(list<int>& L,list<int>::iterator low,list<int>::iterator high){
    if(low==high||low == L.end()) return;

    high = prev(high);
    while (low!=high)
    {
        list<int>::iterator next_high = prev(high);

        L.splice(low, L, high);

        high = next_high;
    }
    
}

int main(){
    int N,K;
    cin >> N >> K;
    list<int> L;
    vector<list<int>::iterator> iterators(N/K+1);
    for(int i=0;i<N;i++){
        int num;
        cin >> num;
        L.push_back(num);
        if(i % K == 0){
            iterators[i/K] = prev(L.end());
        }
    }
    if (N % K == 0) {
        iterators[N/K] = L.end();
    }

    for(int i=0;i<N/K;i++){
        inverse_partition(L,iterators[i],iterators[i+1]);
    }

    for (int num : L) {
        cout << num << " ";
    }
    
}