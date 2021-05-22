#include <string>
#include <vector>


#include <set>
#include <map>
#include <iostream>
#include <limits>

using namespace std;


map<string, int> gem_map;


bool is_full() {
    for(auto gem : gem_map)
        if(gem.second == 0) return false;

    return true;
}

void remove_gem(string gem) {
    auto itr = gem_map.find(gem);
    
    if(itr != gem_map.end()) itr->second--;
}

void add_gem(string gem) {
    auto itr = gem_map.find(gem);
    
    if(itr != gem_map.end()) itr->second++;
}


vector<int> solution(vector<string> gems) {
    vector<int> answer(2);

    // 보석 종류 
    set<string> gem_names;
    for(auto gem : gems)
        gem_names.emplace(gem);

    
    for(auto name : gem_names)
        gem_map.insert(std::make_pair(name, 0));


    int start_p = 0;
    int end_p = 0;
    int len = std::numeric_limits<int>::max();

    add_gem(gems[start_p]);

    while(true) {
        if(is_full()) {
            // answer renew
            if(end_p - start_p + 1 < len) {
                len = end_p - start_p + 1;
                answer[0] = start_p + 1;
                answer[1] = end_p + 1;
            }

            if(start_p == end_p) break;
            
            remove_gem(gems[start_p]);
            start_p++;

        } else {
            if(end_p == gems.size() - 1) break;

            end_p++;
            add_gem(gems[end_p]);
        }

    }
    
    return answer;
}

int main() {
    vector<string> gems = {"DIA", "RUBY", "RUBY", "DIA", "DIA", "EMERALD", "SAPPHIRE", "DIA"};
    auto res = solution(gems);

    std::cout << res.at(0) << " " << res.at(1) << std::endl;

    return 0;
}