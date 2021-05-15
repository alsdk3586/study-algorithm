// 12015 : 가장 긴 증가하는 부분 수열 3
// N은 1,000,000 이하의 정수
// 처음부터 끝까지 탐색으로 찾는 방법의 빅오는 N^2
// 1,000,000,000,000이므로 1초 안에 NOT SAFE
// 이분탐색을 사용하면 빅오는 Nlog(N)
// 1,000,000 * 20 = 20,000,000  약 0.2초

#include <iostream>
#include <vector>
#include <algorithm>

// first : 수열 요소
// second : numbers[x]가 마지막 요소일 때, 해당 요소는 몇번 째로 증가된 요소인지
// std::vector<std::pair<int,int>> numbers;
std::vector<std::pair<int,int>> numbers;

void search_n_push(int lv, int rv, int n) {

    if(lv > rv) {
        // index lv에 삽입한다.
        
        // 제일 작은 요소면,
        if(rv == -1) {
            numbers.insert(numbers.begin()+lv, std::make_pair(n, 1));
            return;
        }

        // 앞의 요소들 중에 second값이 제일 큰 것 (+ 1)
        auto max = *std::max_element(numbers.begin(), numbers.begin() + lv, [](std::pair<int,int> lv, std::pair<int,int> rv){
            return lv.second < rv.second;
        });


        int curr_order = (max.first == n ? max.second : max.second + 1);

        // 새롭게 추가한 요소 뒤의 요소들 중에 더 적은 second 값이 있다면 삭제해준다.
        for(std::vector<std::pair<int,int>>::iterator itr = numbers.begin()+lv; itr != numbers.end(); ) {
            if(curr_order >= itr->second) {
                numbers.erase(itr);
            } else {
                itr++;
            }
        }

        // if(curr_order >= (numbers.begin()+lv)->second)
        //     numbers.erase(numbers.begin()+lv, numbers.end());

        numbers.insert(numbers.begin()+lv, std::make_pair(n, curr_order));


        return;
    }

    int mv = (lv + rv) / 2;

    if(numbers[mv].first > n) {
        search_n_push(lv, mv-1, n);
    } else {
        search_n_push(mv+1, rv, n);
    }
}


int main() {
    int N = 0;
    std::cin >> N;

    int in = 0;
    for(int i=0; i<N; i++) {
        std::cin >> in;

        // binary search & push
        search_n_push(0, numbers.size()-1, in);
    }

    auto max = *std::max_element(numbers.begin(), numbers.end(), [](std::pair<int,int> lv, std::pair<int,int> rv){
        return lv.second < rv.second;
    });

    // for(int i=0; i<numbers.size(); i++) {
    //     std::cout << numbers.at(i).first << ", " << numbers.at(i).second << std::endl;

    // }

    std::cout << max.second << std::endl;

    return 0;
}