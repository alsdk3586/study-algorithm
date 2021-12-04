// 2096 : 내려가기
// DP를 사용한다면, 연산 횟수 20만(첫 번째 선택) + 30만(두 번째) + 20만(세 번째) = 약 70만
// 제한시간은 1초이므로 충분하다.

#include <iostream>
#include <vector>
#include <algorithm>


std::vector<std::vector<int>> arr_max;
std::vector<std::vector<int>> arr_min;

int main() {

    int answer_max =0;
    int answer_min =0;

    int N = 0;
    std::cin >> N;

    int elem01;
    int elem02;
    int elem03;

    std::vector<int> max_vec = {};
    std::vector<int> min_vec = {};

    for(int h=0; h<N; h++) {
        std::cin >> elem01 >> elem02 >> elem03;

        if(max_vec.empty()) {
            max_vec.push_back(elem01);
            max_vec.push_back(elem02);
            max_vec.push_back(elem03);

            min_vec.push_back(elem01);
            min_vec.push_back(elem02);
            min_vec.push_back(elem03);
            continue;
        }

        // max_vec가 가장 큰 수가 되도록 업데이트 해준다.
        auto max01 = *(std::max_element(max_vec.begin(), max_vec.end()-1)) + elem01;
        auto max02 = *(std::max_element(max_vec.begin(), max_vec.end())) + elem02;
        auto max03 = *(std::max_element(max_vec.begin()+1, max_vec.end())) + elem03;

        max_vec[0] = max01;
        max_vec[1] = max02;
        max_vec[2] = max03;

         // min_vec가 가장 작은 수가 되도록 업데이트 해준다.
        auto min01 = *(std::min_element(min_vec.begin(), min_vec.end()-1)) + elem01;
        auto min02 = *(std::min_element(min_vec.begin(), min_vec.end())) + elem02;
        auto min03 = *(std::min_element(min_vec.begin()+1, min_vec.end())) + elem03;

        min_vec[0] = min01;
        min_vec[1] = min02;
        min_vec[2] = min03;       
    }

    answer_max = *(std::max_element(max_vec.begin(), max_vec.end()));
    answer_min = *(std::min_element(min_vec.begin(), min_vec.end()));

    std::cout << answer_max << " " << answer_min << std::endl;
    return 0;
}