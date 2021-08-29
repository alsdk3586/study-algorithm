#include <iostream>

using namespace std;
#define MAX 100001

int N, M;
int arr[MAX];

int main() {
    ios_base::sync_with_stdio(0);
	cin.tie(0);

    cin >> N >> M;

    //배열 입력 받기
    for(int i=0;i<N;i++)
        cin >> arr[i];
    
    //배열을 누적합로 변경
    for(int i=1;i<=N;i++)
        arr[i]+=arr[i-1];

    //구간 입력 받고 누적 합 출력
    for(int i=0;i<M;i++) {
        int x, y;
        cin >> x>> y;

        cout << arr[y-1]-arr[x-2] << "\n";
    }
}