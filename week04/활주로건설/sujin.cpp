#include <vector>
#include <cstring>
#include <iostream>

using namespace std;

int runway[21][21] = {0};  // 활주로 맵

bool possible(vector<int> &, int, int);

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    // T: 총 테스트 케이스의 개수
    // N: 지도의 한 변의 크기
    // X: 경사로의 길이
    int T, N, X, ans;

    // 입력
    cin >> T;
    for (int t = 1; t <= T; t++) {
        cin >> N >> X;

        // 초기화
        vector<int> arr(N, 0);
        memset(runway, 0, sizeof(runway));
        ans = 0;

        // 활주로 맵 설정
        for (int i = 0; i < N; i++)
            for (int j = 0; j < N; j++)
                cin >> runway[i][j];

        // 활주로를 건설할 수 있는 경우의 수 계산
        for (int i = 0; i < N; i++) {
            // 가로
            for (int j = 0; j < N; j++) {
                arr[j] = runway[i][j];
            }
            ans += possible(arr, N, X);
            arr.clear();
            // 세로
            for (int j = 0; j < N; j++) {
                arr[j] = runway[j][i];
            }
            ans += possible(arr, N, X);
            arr.clear();
        }

        // 결과 출력
        cout << "#" << t << " " << ans << endl;
    }
}

// 활주로를 건설할 수 있는지 여부를 반환한다.
// arr: 검사해야 하는 지형, n: 지도 한 변의 크기, x: 경사로의 길이
bool possible(vector<int> &arr, int n, int x) {
    int cnt = 1;
    int prev = arr[0];

    for (int i = 1; i < n; i++) {
        // 오르막일 때
        // cnt 값이 활주로 길이 x 이상이면 통과, 그렇지 않으면 false
        if (arr[i] > prev) {
            if (arr[i] - prev > 1) return false; // 높이가 1보다 큰 경우
            if (cnt >= x) cnt = 1;
            else return false;
        }
        // 내리막일 때
        // arr[i : i + x] 가 모두 같은 높이여야 한다.
        // arr[i + x - 1] 에서 cnt 가 내려가기 전 cnt 의 값을 갖기 위해, cnt 를 -x + 1 로 설정
        else if (arr[i] < prev) {
            if (prev - arr[i] > 1) return false;  // 높이가 1보다 큰 경우
            if (i + x > n) return false;  // 경사로를 지형 밖까지 설치해야 하는 경우
            for (int j = i; j < i + x; j++)
                if (arr[i] != arr[j]) return false;
            cnt = -x + 1;
        }
        // 평지일 때
        else cnt++;
        prev = arr[i];
    }
    return true;
}
