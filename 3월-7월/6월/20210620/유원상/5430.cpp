#include <iostream>
#include <cctype>
#include <vector>
#include <string>

std::vector<int> calc_offset(std::string& str) {
    std::vector<int> offset;
    
    if (str == "[]")
        return offset;
    
    str.pop_back();
    int strlen = (int)str.length();
    
    for (int i = 0; i != strlen; ++i) {
        if (std::isdigit(str[i]))
            continue;
        
        offset.push_back(i + 1);
        str[i] = 0;
    }
    
    return offset;
}

std::string get_result(std::string x, int it, int end) {
    if (it == end)
        return std::string("");
    
    auto raw = x.data();
    auto offset = calc_offset(x);
    std::string ret;
    
    while (it != end) {
        auto num = std::string(raw + offset[it]);
        ret += (num + ",");
        
        if (it < end)
            ++it;
        else
            --it;
    }
    
    ret.pop_back();
    
    return ret;
};

int main(int argc, const char* argv[]) {
    std::ios::sync_with_stdio(false);
    
    int T;
    std::cin >> T;
    
    while (T--) {
        int n;
        std::string p;
        std::cin >> p >> n;
        
        int valid, it, end;
        {
            bool forward = true;
            valid = true;
            it = 0;
            end = n;
            
            for (auto comm : p) {
                if (comm == 'R') {
                    forward ^= 0b1;
                    continue;
                }
                        
                if (it == end) {
                    valid = false;
                    break;
                }
                
                if (forward)
                    ++it;
                else
                    --end;
            }
            
            if (!forward)
                std::swap(--it, --end);
        }
        
        std::string x, R;
        std::cin >> x;
        
        if (!valid)
            R = "error";
        else {
            R = "[" + get_result(x, it, end) + "]";
        }
        
        std::cout << R << "\n";
    }
    
    return 0;
}
