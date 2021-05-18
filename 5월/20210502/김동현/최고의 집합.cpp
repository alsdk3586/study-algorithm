#include <string>
#include <vector>

using namespace std;

vector<int> solution(int n, int s) {
    int quot = s / n;
    int rem = s % n;
    
    if (quot <= 0)
        return vector<int>{ -1 };
    
    vector<int> ret(n, quot);
    for (auto it = ret.rbegin(); rem > 0; it++, rem--)
         (*it)++;
        
    return ret;
}
