#include <iostream>
#include <algorithm>
#include <vector>
#include <string>

std::string name = "ACFJMNRT";
std::vector<int> diff[26][26];
std::vector<int> cond[26][26];

bool verify(std::string& name) {
    
    for (int i = 0; i < 8; ++i) {
        for (int j = i + 1; j < 8; ++j) {
            int abs = std::abs(i - j) - 1;
            
            int idx1 = name[i];
            int idx2 = name[j];
            
            if (idx1 > idx2)
                std::swap(idx1, idx2);
            
            auto& ed = diff[idx1][idx2];
            auto& ec = cond[idx1][idx2];
            
            int count = ed.size();
            for (int k = 0; k < count; ++k) {
                bool valid = true;
                
                int expect = ed[k];
                int cond = ec[k];
                
                if (cond == '>')
                    valid = abs > expect;
                else if (cond == '<')
                    valid = abs < expect;
                else if (cond == '=')
                    valid = abs == expect;
                
                if (!valid)
                    return false;
            }
        }
    }
    
    return true;
}

int solution(int n, std::vector<std::string> data) {
    int result = 0;
    
    for (auto& c : name)
        c -= 'A';
    
    for (auto str : data) {
        int idx1 = str[0] - 'A';
        int idx2 = str[2] - 'A';
        
        if (idx1 > idx2)
            std::swap(idx1, idx2);
        
        diff[idx1][idx2].push_back(str[4] - '0');
        cond[idx1][idx2].push_back(str[3]);
    }
    
    do {
        if (verify(name))
            ++result;
    } while (std::next_permutation(name.begin(), name.end()));
        
    return result;
}
