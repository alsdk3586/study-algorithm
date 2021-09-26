#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> v;
int N;

int main() {
    cin >> N;

    //값 입력받기
    for(int i=0;i<N;i++) {
        int x;
        cin >> x;
        v.push_back(x);
    }

    int start = 0;
    int end = 2;
    int cnt=0;

    while(start<=end-2 && end<N) {
        for(int i=start+1;i<end;i++) {
            if(v[start]+v[end]+v[i] == 0) { // 합이 0이면 cnt up
                cnt++;
            }
        }
        end++; // end point 이동
        if(end == N-1) { // 만약 끝이라면
            start++;
            end = start+2;
        }
    }
    cout << cnt;
}