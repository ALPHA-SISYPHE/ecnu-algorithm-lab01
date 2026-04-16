#include<iostream>
#include<vector>
#include<utility>
#include<string>
using namespace std;

void construct_longest_valid(vector<int> &longest_valid,string &s){
    vector<int> stack;//索引栈,储存括号的索引，栈顶为最新等待匹配的左括号索引

    for(int i = 0;i<s.size();i++){
        if(s[i]=='(' || s[i]=='{' || s[i]=='['){
            stack.push_back(i);
        }
        //处理右括号
        else{
            if(!stack.empty()){
                char left = s[stack.back()];
                if((s[i]==')' && left=='(') || (s[i]=='}' && left=='{') || (s[i]==']' && left=='[')){
                    longest_valid[stack.back()] = i;
                    stack.pop_back();
                }
                else{
                    //右括号不匹配，清空栈
                    stack.clear();
                }
            }
            else{
                continue;//栈空遇到了右括号，说明这个右括号无效，继续处理下一个字符
            }
        }
    }
}

int caculate_query(vector<int> &longest_valid,int a,int b){
    int res = 0;//有效括号长度总和
    for(int i = a;i<=b;i++){
        //如果这个位置的最长有效括号的配对位置是-1，说明这个位置的括号无效，继续处理下一个位置
        if(longest_valid[i]==-1){
            continue;
        }
        //有效
        else{
            //检查右边边界
            if(longest_valid[i]>b){
                continue;
            }
            //右边边界在范围内，累加res
            else{
                res += longest_valid[i] - i + 1;
                //累加过后，跳过这个有效括号的范围，继续处理下一个位置
                i = longest_valid[i];
            }
        }
    }
    return res;
}
    

int main(){
    string s;
    cin >> s;
    int queries;
    cin >> queries;

    //构造一个vector，每个元素是int,存储的是它配对的位置
    vector<int> longest_valid(s.size(),-1);
    construct_longest_valid(longest_valid,s);

    for(int i =0;i<queries;i++){
        int a,b;
        cin >> a >> b;
        cout << caculate_query(longest_valid,a-1,b-1) << endl;  
    }

}