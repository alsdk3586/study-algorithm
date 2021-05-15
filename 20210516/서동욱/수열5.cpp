// 14003 : 가장 긴 증가하는 부분 수열 3
// N은 1,000,000 이하의 정수
// 처음부터 끝까지 탐색으로 찾는 방법의 빅오는 N^2
// 1,000,000,000,000이므로 1초 안에 NOT SAFE
// 이분탐색을 사용하면 빅오는 Nlog(N)
// 1,000,000 * 20 = 20,000,000  약 0.2초

#include <iostream>
#include <vector>
#include <algorithm>

// first : 수열 요소
std::vector<std::vector<int>> numbers;

void search_n_push(int lv, int rv, int n) {


    if(lv > rv) {
        // n이 제일 큰 수이면 맨 뒤에 삽입
        if(numbers.size() == lv)
            numbers.push_back({n});
        // 해당 인덱스 요소 갱신
        else
            numbers.at(lv).push_back(n);

        return;
    }


    int mv = (lv + rv) / 2;

    if(numbers[mv].back() == n) return;

    if(numbers[mv].back() > n) {
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

    std::cout << numbers.size() << std::endl;
    
    std::vector<int> answer;


    answer.push_back(numbers.at(numbers.size()-1).front());

    for(int i=numbers.size()-2; i>=0; i--) {
        // answer.back보다 작은 값 중 최대값 push_back
        for(std::vector<int>::iterator itr = numbers.at(i).begin(); itr != numbers.at(i).end(); itr++) {
            if(*itr < answer.back()) {
                answer.push_back(*itr);
                break;
            }
        }
    }

    for(std::vector<int>::reverse_iterator itr = answer.rbegin(); itr != answer.rend() ; itr++) {
        std::cout << *itr << " ";
    }

    return 0;
}