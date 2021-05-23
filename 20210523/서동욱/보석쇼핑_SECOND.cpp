#include <string>
#include <vector>


#include <set>
#include <map>
#include <iostream>
#include <limits>
#include <algorithm>

using namespace std;



vector<int> solution(vector<string> gems) {
    vector<int> answer(2);

    // 보석 종류 
    set<string> gem_names;
    for(auto gem : gems)
        gem_names.emplace(gem);

    int gem_size = gem_names.size();
    int len = std::numeric_limits<int>::max();

    map<string, int> gem_map;
    for(int i=0; i<gems.size(); i++) {
        // gem_map.emplace(gems[i], i+1);
        gem_map[gems[i]] = i+1;

        if(gem_map.size() == gem_size) {
            // answer인지 판단
            auto min = std::min_element(gem_map.begin(), gem_map.end(), [](const pair<string,int>& lv, const pair<string,int>& rv){
                return lv.second < rv.second;
            });
            
            auto max = std::max_element(gem_map.begin(), gem_map.end(), [](const pair<string,int>& lv, const pair<string,int>& rv){
                return lv.second < rv.second;
            });
            
            // std::cout << "min : " << min->second << " " << "max : " << max->second << std::endl;

            if(len > max->second - min->second + 1) {
                len = max->second - min->second + 1;
                answer[0] = min->second;
                answer[1] = max->second;
            }
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