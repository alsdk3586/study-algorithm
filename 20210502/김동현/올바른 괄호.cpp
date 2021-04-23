#include <string>
#include <iostream>
#include <stack>

using namespace std;

bool solution(string s)
{
    stack<char> stk;
    for (char& c : s)
    {
        if (c == '(')
            stk.push(c);
        else
        {
            if (stk.empty())
                return false;
            else
                stk.pop();
        }
    }
    
    return stk.empty();
}
