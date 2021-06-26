#include <iostream>
#include <algorithm>
#include <vector>
#include <string>

std::string name = "ACFJMNRT";
int diff[26][26];
int cond[26][26];

std::vector<int> comb;

bool verify(std::string name) {
    
    for (int i = 0; i < 8; ++i) {
        for (int j = i + 1; j < 8; ++j) {
            int abs = j - i - 1;
            int expect = diff[name[j]][name[i]];
            
            bool valid;
            
            if (cond[j][i] == '>')
                valid = (abs > expect);
            else if (cond[j][i] == '<')
                valid = (abs < expect);
            else
                valid = (abs == expect);
            
            if (!valid)
                return false;
        }
    }
    
    return true;
}

int solution(int n, std::vector<std::string> data) {
    int result = 0;
    
    for (int i = 0; i < 26; ++i) {
        for (int j = 0; j < 26; ++j) {
            diff[i][j] = diff[j][i] = -1;
            cond[i][j] = cond[j][i] = '>';
        }
    }
    
    for (auto& c : name)
        c -= 'A';
    
    for (auto str : data) {
        int idx1 = str[0] - 'A';
        int idx2 = str[2] - 'A';
        diff[idx1][idx2] = diff[idx2][idx1] = str[4] - '0';
        cond[idx1][idx2] = cond[idx1][idx2] = str[3];
    }
    
    do {
        if (verify(name))
            ++result;
    } while (std::next_permutation(name.begin(), name.end()));
        
    return result;
}

int main(int argc, const char* argv[]) {
    
    std::vector<std::string> data = {
        "N~F=0", "R~T>2"
    };
    
    std::cout << solution(2, data);
    
    
    return 0;
}
