#include <iostream>
#include <cstring>
#include <string>

int N, R;
bool alphabet[26];
std::string str;

bool solve() {
    bool isGroupword = true;
    std::memset(alphabet, false, 26);
    
    std::string s;
    s = str[0];
    for (int i = 1; i < str.size(); ++i)
        if (s.back() != str[i])
            s += str[i];
    
    int i = 0;
    while (i < s.size()) {
        int idx = (int)s[i] - 97;
        if (!alphabet[idx]) {
            alphabet[idx] = true;
        }
        else {
            isGroupword = false;
            break;
        }
        ++i;
    }
    
    return isGroupword;
}

int main (int argc, const char * argv []) {
    
    R = 0;
    std::cin >> N;
    for (int i = 0; i < N; ++i) {
        std:: cin >> str;
        if (solve()) ++R;
    }
    
    std::cout << R;
    
    return 0;
}
