#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int N,K;
vector<int> v;

int main() {
    cin >> N >> K; // N, K 입력받기

    for(int i=0;i<N;i++) { //라이언이라면 인덱스 저장
        int x;
        cin >> x;
        if(x==1) v.push_back(i);
    }

    int result=987654321;

    if(v.size()<K) cout << "-1"; //라이언이 K보다 적으면 -1 출력
    else {
        for(int i=0;i<=v.size()-K;i++) 
            result=min(result,v[i+K-1]-v[i]+1);
        cout << result; // 아니라면 가장 작은 인덱스 차이 출력
    }
}