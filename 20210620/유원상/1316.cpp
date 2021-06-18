#include <iostream>
#include <string>

int N, R, C[26];
std::string S;

int main() {
    std::cin >> N;
    
    R = N;
    
    while (N--) {
        std::cin >> S;
        
        std::fill_n(C, 26, 0);
        
        char before = S[0];
        
        for (auto curr : S) {
            if (before == curr)
                continue;
            
            if (!C[curr - 'a']) {
                C[before - 'a'] = true;
                before = curr;
                continue;
            }
            
            --R;
            break;
        }
    }
    
    std::cout << R;
    
    return 0;
}
