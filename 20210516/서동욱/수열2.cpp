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
std::vector<int> numbers;

void search_n_push(int lv, int rv, int n) {


    if(lv > rv) {
        // n이 제일 큰 수이면 맨 뒤에 삽입
        if(numbers.size() == lv)
            numbers.push_back(n);
        // 해당 인덱스 요소 갱신
        else
            numbers.at(lv) = n;

        return;
    }


    int mv = (lv + rv) / 2;

    if(numbers[mv] == n) return;

    if(numbers[mv] > n) {
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

    return 0;
}