#include<iostream>
#include<string>
#include<list>
#include<unordered_map>

using namespace std;

int main(){
    int n;
    list<int> l;
    cin >> n;
    string s;

    //构建含有迭代器的哈希表，加速插入与查询
    unordered_map<int, list<int>::iterator> pos;
    for(int i=0;i<n;i++){
        cin >> s;
        if(s=="ARRIVE"){
            int x;
            cin >> x;
            l.push_back(x);
            pos[x] = prev(l.end());
        }
        else if(s=="LEAVE"){
            int x;
            cin >> x;
            l.erase(pos[x]);
            pos.erase(x);
        }
        else if(s == "INSERT"){
            int x,y;
            cin >> x >> y;

            //在y前面插入x，返回x的迭代器
            pos[x] = l.insert(pos[y],x);
        }
        else if(s == "SERVE"){
            if(l.empty())
            cout << "EMPTY" << endl;
            else
            {
                int head = l.front();
                cout << head << endl;
                pos.erase(head);
                l.pop_front();
            }
        }
    }

    if (l.empty()) {
        cout << "EMPTY" << endl;
    } else {
        for (auto it = l.begin(); it != l.end(); ++it) {
            cout << *it << (next(it) == l.end() ? "" : " ");
        }
    }

}