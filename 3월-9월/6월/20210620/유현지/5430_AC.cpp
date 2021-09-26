#include <iostream>
#include <string>
#include <queue>

int T, n;
bool reverse, err;
std::deque<int> arr;
std::string p, str, ans;

void init() {
    reverse = err = false;
    arr.clear();
    ans = "error";
}

void input() {
    std::cin >> p >> n >> str;
    str = str.substr(1, str.size() - 2);
    
    std::string s = "";
    for (int i = 0; i < str.size(); ++i) {
        while(i < str.size() && str[i] != ',')
            s += str[i++];
        
        if (!s.empty()) {
            arr.push_back(stoi(s));
            s.clear();
        }
    }
}

void solve() {
    for (int i = 0; i < p.size(); ++i) {
        if (p[i] == 'R') {
            reverse = !reverse;
        }
        else {
            if (arr.empty()) {
                err = true;
                break;
            }
            
            if (reverse)
                arr.pop_back();
            else
                arr.pop_front();
        }
    }
}


void output() {
    
    if (!err) {
        ans = '[';
        
        if (reverse) {
            while (!arr.empty()) {
                ans += std::to_string(arr.back());
                ans += (arr.size() > 1) ? "," : "";
                arr.pop_back();
            }
        }
        else {
            while (!arr.empty()) {
                ans += std::to_string(arr.front());
                ans += (arr.size() > 1) ? "," : "";
                arr.pop_front();
            }
        }
        
        ans += ']';
    }
}


int main (int argc, const char * argv []) {
    std::ios::sync_with_stdio(false);
    
    std::cin >> T;
    for (int i = 0; i < T; ++i) {
        init();
        input();
        solve();
        output();
        
        std::cout << ans << std::endl;
    }

    return 0;
}
