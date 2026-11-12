

#include <iostream>
#include <vector>
#include <stack>
#include <deque>
#include <string>
using namespace std;

class Solution{

public:

    // LeetCode 20 有效的括号
    bool isValid(string s){
        stack<char> st;
        for(char ch : s){
            if (ch=='('){
                st.push(')');
            }else if (ch=='{') {
                st.push('}');
            }else if (ch=='['){
                st.push(']');
            }else {
                if(st.empty() || st.top()!=ch) return false;
                st.pop();
            }
        }
        return st.empty();
    }


    // LeetCode 394 字符串解码  -- 队列
    string decodeString(string s){
        deque<string> stk_str;
        deque<int> stk_time;
        string ans;
        int time=0;

        for(char c:s){
            if(isdigit(c)){
                time=time*10+(c-'0');
            }else if(c=='['){
                // 把当前已经拼好的字符串 和 倍数 入队
                stk_str.push_front(ans);
                ans.clear();
                stk_time.push_front(time);
                time=0;
            }else if (c==']'){
                // 出队：倍数、之前保存的前缀字符串
                int cnt=stk_time.front();
                stk_time.pop_front();
                string prev=stk_str.front();
                stk_str.pop_front();
                string temp;
                for(int i=0;i<cnt;i++){
                    temp+=ans;
                }
                ans=prev+temp;
            }else {
                ans.push_back(c);
            }
        }
        return ans;
    }

    // LeetCode 394 字符串解码  -- 栈
    string decodeString1(string s){
        stack<string> stk_str;
        stack<int> stk_time;
        string ans;
        int time=0;

        for(char c:s){
            if(isdigit(c)){
                time=time*10+(c-'0');
            }else if(c=='['){
                // 把当前已经拼好的字符串 和 倍数压入栈  -- 头插
                stk_str.push(ans);
                stk_time.push(time);
                ans.clear();
                time=0;
            }else if(c==']'){
                // 出栈：倍数、之前保存的前缀字符串  -- 头删
                int cnt=stk_time.top();
                string prev=stk_str.top();
                stk_time.pop();
                stk_str.pop();

                string temp;
                for(int i=0;i<cnt;++i){
                    temp+=ans;
                }
                ans=prev+temp;
            }else {
                ans.push_back(c);   // -- 尾插
            }
        }
        return ans;
    }

    // LeetCode739 每日温度 逆序单调栈 deque模拟
    vector<int> dailyTempratures(vector<int>& temperatures){
        int n=temperatures.size();
        vector<int> ans(n,0);
        deque<int> stk; // 单调栈，存下标

        for (int i=n-1;i>=0;i--){
            while(!stk.empty() && temperatures[stk.front()]<=temperatures[i]){
                stk.pop_front();
            }
            if(!stk.empty()) ans[i]=stk.front()-i;  // stk.top()? -- top()是stack的，deque是front()
            stk.push_front(i);
        }
        return ans;
    }

    // LeetCode739 每日温度 逆序单调栈 stack模拟
    vector<int> dailyTempratures1(vector<int>& temperatures){
        int n=temperatures.size();
        vector<int> ans(n,0);
        stack<int> stk; // 单调栈，存下标

        for (int i=n-1;i>=0;i--){
            while(!stk.empty() && temperatures[stk.top()]<=temperatures[i]){
                stk.pop();
            }
            if(!stk.empty()) ans[i]=stk.top()-i;  
            stk.push(i);
        }
        return ans;
    }

    // LeetCode739 每日温度 正向单调栈
    vector<int> dailyTempratures2(vector<int>& temperatures){
        int n=temperatures.size();
        vector<int> ans(n,0);
        stack<int> stk; // 单调栈，存下标

         for(int i=0;i<n;i++){
            while(!stk.empty() && temperatures[stk.top()]<temperatures[i]){
                int index=stk.top();
                stk.pop();
                ans[index]=i-index;
            }
            stk.push(i);
         }
        return ans;
    }



};

int main(){
    Solution sol;
    cout << boolalpha;
    cout << sol.isValid("()") << endl;         // true
    cout << sol.isValid("()[]{}") << endl;     // true
    cout << sol.isValid("(]") << endl;         // false
    cout << sol.isValid("[") << endl;          // false

    cout << sol.decodeString("3[a2[c]]") << endl;      // accaccacc
    cout << sol.decodeString("2[abc]3[cd]ef") << endl; // abcabccdcdcdef

    vector<int> temp = {73,74,75,71,69,72,76,73};
    vector<int> res = sol.dailyTempratures(temp);
    for(int x : res) cout << x << " ";
    cout << endl;
    return 0;
}




















