// 2096 : 부분합
// 제한시간 0.5초인데 입력 수열은 100,000,000
// O(N)으로 풀면 시간제한 걸리려나..?

#include <iostream>
#include <vector>
#include <limits>


int main() {

    int N = 0;
    int S = 0;
    std::cin >> N >> S;

    std::vector<int> arr(N);
    for(int i=0; i<N; i++)
        std::cin >> arr[i];

    int sum = 0;
    int start_p = 0;
    int end_p = 0;
    int len = std::numeric_limits<int>::max();

    sum = arr[end_p];
    int renew = 0;

    while(true) {
        if(sum >= S) {
            // len는 최소값으로 매번 갱신
            len = std::min(len, end_p - start_p + 1);
            
            // sum >= S : start_p++
            renew -= arr[start_p];
            start_p++;
            
        } else {
            // sum < S : end_p++
            end_p++;
            renew += arr[end_p];

        }

        if(start_p > end_p || end_p > N - 1)
            break;
        
        // sum 갱신
        sum += renew;
        renew = 0;
    }

    if(len == std::numeric_limits<int>::max()) len = 0;

    std::cout << len << std::endl;

    return 0;

}