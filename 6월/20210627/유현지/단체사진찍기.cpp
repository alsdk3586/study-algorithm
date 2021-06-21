#include <string>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

bool condition(vector<char> v, vector<string> data, int n) {
    
    bool flag;
    
    for (int i = 0; i < n; ++i) {
        
        flag = false;
        
        for (int j = 0; j < 8; ++j) {
            
            for (int k = j + 1; k < 8; ++k) {
            
                if ((data[i][0] == v[j] && data[i][2] == v[k]) ||
                    (data[i][0] == v[k] && data[i][2] == v[j])) {
                    
                    switch(data[i][3]) {
                        case '=':
                            if (abs(j - k) == (data[i][4] - '0') + 1) {
                                flag = true;
                                break;
                                
                            } else {
                                return false;
                            }
                            
                        case '<':
                            if (abs(j - k) < (data[i][4] - '0') + 1) {
                                flag = true;
                                break;
                                
                            } else {
                                return false;
                            }
                            
                            
                        case '>':
                            if (abs(j - k) > (data[i][4] - '0') + 1) {
                                flag = true;
                                break;
                                
                            } else {
                                return false;
                            }
                    }
                }
            
                if (flag) break;
            }
        
            if (flag) break;
        }
    }
    
    return true;
}



int solution(int n, vector<string> data) {
    int answer = 0;
    vector<char> v = { 'A', 'C', 'F', 'J', 'M', 'N', 'R', 'T' };
    
    do {
        if (condition(v, data, n))
            ++answer;
    
    } while ( next_permutation(v.begin(), v.end()) );
    
    
    return answer;
}
