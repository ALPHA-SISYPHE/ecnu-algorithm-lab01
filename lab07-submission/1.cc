#include<iostream>
#include<deque>
#include<string>
using namespace std;

void IN(deque<int> &q, int x){
    q.push_back(x);
}

int CALL(deque<int> &q){
    if(q.empty()) return -1;
    int x = q.front();
    q.pop_front();
    return x;
}

int QUERY(deque<int> &q){
    if(q.empty()) return -1;
    return q.front();
}

int COUNT(deque<int> &q){
    return q.size();
}

int main(){
    int n;
    cin >> n;
    deque<int> q;

    for(int i = 0; i < n; i++){
        string s;
        cin >> s;
        if(s == "IN"){
            int x;
            cin >> x;
            IN(q, x);
        }
        else if(s == "CALL"){
            if(q.empty()) cout << "EMPTY" << endl;
            else cout << CALL(q) << endl;
        }
        else if(s == "QUERY"){
            if(q.empty()) cout << "EMPTY" << endl;
            else cout << QUERY(q) << endl;
        }
        else if(s == "COUNT"){
            cout << COUNT(q) << endl;
        } 
    }
    
}