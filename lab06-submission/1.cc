#include <iostream>
#include<deque>
#include<string>
using namespace std;

struct Task
{
    string name;
    int time;
};


int main(){
    int N,Q;
    cin>>N>>Q;
    deque<Task> dq(N);
    for(int i=0;i<N;i++){
        cin>>dq[i].name>>dq[i].time;
    }

    int time = 0;
    while(!dq.empty()){
        Task t=dq.front();
        dq.pop_front();
        if(t.time<=Q){
            time+=t.time;
            cout<<t.name<<" "<<time<<endl;
        }else{
            t.time-=Q;
            time+=Q;
            dq.push_back(t);
        }
    }
}