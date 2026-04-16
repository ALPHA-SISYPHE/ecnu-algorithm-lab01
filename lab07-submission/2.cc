#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;
int main()
{
    int res = 0;//最长有效括号的长度
    vector<int> idx;//索引栈，最后两个元素是左右括号的索引
    string brackets;
    cin >> brackets;

    int start = -1;

    for (int i = 0; i < brackets.size(); i++){
        //左括号入栈
        if (brackets[i] == '(' || brackets[i] == '{' || brackets[i] == '[')
        {
            idx.emplace_back(i);
        }
        //右边括号处理
        else{
            if(!idx.empty()){
                char left = brackets[idx.back()];
                if((brackets[i] == ')' && left == '(') || (brackets[i] == '}' && left == '{') || (brackets[i] == ']' && left == '[')){
                    idx.pop_back();
                    //如果栈空了，说明从start到i都是有效括号
                    if(idx.empty()){
                        res = max(res, i - start);
                    }
                    //如果栈不空了，说明从idx.back()到i都是有效括号
                    else{
                        res = max(res, i - idx.back());
                    }
                }
                else{
                    //右边括号不匹配，清空栈，并更新start
                    idx.clear();
                    start = i;
                }
            }
            else{
                //栈空遇到了右边括号，说明从start到i都是无效括号，更新start
                start = i;
            }
        }
    }
    cout << res ;
}