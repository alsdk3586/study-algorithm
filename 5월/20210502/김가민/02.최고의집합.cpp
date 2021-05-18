#include <string>
#include <vector>

using namespace std;

vector<int> solution(int n, int s) {
    vector<int> answer; 
    int i, div = 0, mok = 0;
    
    if(n > s) 
    {
        answer.push_back(-1);
        return answer; 
    }
    
    div = s/n;
    mok = s%n; 
    
    for(i = 0; i < n; i++)
    {
        if(i >= n-mok) answer.push_back(div+1);
        else answer.push_back(div);
    }
    
    return answer;
}