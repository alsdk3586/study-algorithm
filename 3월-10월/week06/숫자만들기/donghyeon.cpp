#include <iostream>
#include <climits>
#include <algorithm>

using namespace std;

int N;
int nums[13]; // 숫자 배열 저장
int opCnt[4]; // 각 연산자의 개수
int maxSum; // 연산 결과의 최대값
int minSum; // 연산 결과의 최소값

// 연산자가 있다면 연산의 결과를 매개변수로 재귀
void dfs(int depth, int sum) {
	if (depth == N) { // 모든 계산을 끝냈다면 최대값, 최소값 갱신
		maxSum = max(maxSum, sum);
		minSum = min(minSum, sum);
		return;
	}

	if (opCnt[0]) { // '+'가 있다면 '+'개수 감소 후 숫자를 더한 값으로 이어나감
		opCnt[0]--;
		dfs(depth + 1, sum + nums[depth]);
		opCnt[0]++; // 재귀를 빠져나간 후엔 '+' 개수 다시 증가
	}
	if (opCnt[1]) { // '-'가 있다면 '-'개수 감소 후 숫자를 뺀 값으로 이어나감
		opCnt[1]--;
		dfs(depth + 1, sum - nums[depth]);
		opCnt[1]++; // 재귀를 빠져나간 후엔 '-' 개수 다시 증가
	}
	if (opCnt[2]) { // '*'가 있다면 '*'개수 감소 후 숫자를 뺀 값으로 이어나감
		opCnt[2]--;
		dfs(depth + 1, sum * nums[depth]);
		opCnt[2]++; // 재귀를 빠져나간 후엔 '*' 개수 다시 증가
	}
	if (opCnt[3]) { // '/'가 있다면 '/'개수 감소 후 숫자를 뺀 값으로 이어나감
		opCnt[3]--;
		dfs(depth + 1, sum / nums[depth]);
		opCnt[3]++; // 재귀를 빠져나간 후엔 '/' 개수 다시 증가
	}

	return;
}

int main(int argc, char** argv)
{
	int test_case;
	int T;

	cin >> T;

	for (test_case = 1; test_case <= T; ++test_case)
	{
		// 초기화
		cin >> N;
		maxSum = INT_MIN;
		minSum = INT_MAX;

		for (int i = 0; i < 4; i++) {
			cin >> opCnt[i];
		}
		for (int i = 0; i < N; i++) {
			cin >> nums[i];
		}

		// 초기값은 고정이므로 합계는 첫번째 값, 두번째 원소부터 계산
		dfs(1, nums[0]);

		cout << "#" << test_case << " " << maxSum - minSum << endl;

	}
	return 0;
}