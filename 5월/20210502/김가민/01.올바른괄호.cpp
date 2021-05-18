#include<string>
#include <iostream>

using namespace std;

bool solution(string s)
{
    bool answer = true;
    int sum = 0, i;
    
    for(i = 0; s[i] != '\0'; i++)
    {
        if(s[i] == '(') sum++;
        else if(s[i] == ')') sum--;
        
        if(sum < 0) break;
    }
    
    if(sum == 0) answer = true;
    else answer = false;
    
    return answer;

  
}