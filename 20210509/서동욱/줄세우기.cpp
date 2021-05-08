// 2631 : 줄세우기
// N은 200이하의 정수
// 첫 자리수부터 우상향 요소들을 찾는 방법의 빅오는 N^2
// 40000이므로 1초 안에 SAFE

#include <iostream>
#include <vector>
#include <algorithm>
#include <array>

std::array<int, 200> arr = {0, };

int main() {
    int N = 0;
    std::cin >> N;

    std::vector<int> line;
    int in;
    for(int i=0; i<N; i++) {
        std::cin >> in;
        line.push_back(in);
    }


    // 우상향 원소의 갯수가 MAX인 순열을 찾기 위해
    // arr 배열을 체워준다. arr[x] -> line[x]가 마지막 요소일 때, line[x]는 몇번 째로 증가된 숫자인가
    for(int pos=0; pos<N; pos++) {
        arr[pos] = 1;

        for(int i=0; i<pos; i++) {
            if(line[pos] > line[i] && arr[i] + 1 > arr[pos])
                arr[pos] = arr[i] + 1;

        }
    }

    // 우상향 원소의 갯수가 MAX인 순열의 원소 갯수를 찾는다.
    int max = 0;
    for(int i=0; i<N; i++) {
        if(arr[i] > max) max = arr[i];
    }

    std::cout << N - max << std::endl;

    return 0;
}