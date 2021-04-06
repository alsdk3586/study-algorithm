#include <iostream>
#include <vector>

using namespace std;

int mg[4][8]; // mg[i][j] : i번 자석의 j번째 날의 값(N극 - 0, S극 - 1)

// 자석을 회전
void rotate(int num, int d) {
	if (d == 1) { // 시계방향 회전
		// 0 0 0 1 1 0 0 1 -> 1 0 0 0 1 1 0 0
		int last = mg[num][7]; // 마지막 값을 저장해둠

		for (int i = 7; i > 0; i--) { // 모든 값들을 오른쪽으로 이동
			mg[num][i] = mg[num][i - 1];
		}

		mg[num][0] = last; // 첫번째 값에 회전하기 전 마지막 값을 넣음
	}
	else { // 반시계방향 회전
		// 1 0 0 0 1 0 1 0 -> 0 0 0 1 0 1 0 1
		int first = mg[num][0]; // 첫번째 값을 저장해둠

		for (int i = 0; i < 7; i++) { // 모든 값들을 왼쪽으로 이동
			mg[num][i] = mg[num][i + 1];
		}

		mg[num][7] = first; // 마지막 값에 회전하기 전 첫번째 값을 넣음
	}

	return;
}

// 왼쪽 자석과 붙어있는 날의 자성을 구함
int getLeft(int num) {
	return mg[num][6];
}

// 오른쪽 자석과 붙어있는 날의 자성을 구함
int getRight(int num) {
	return mg[num][2];
}

// 4개의 자석이 어떤 방향으로 회전하는지 구함
vector<int> getDir(int num, int d) {
	vector<int> dir(4, 0); // 0으로 초기화 -> 0 : 회전하지 않음
	dir[num] = d; // num번째 자석은 d방향으로 회전

	// num번 자석 왼쪽 자석들의 회전 방향을 구함
	int left = num - 1;
	while (1) {
		// 현재 첫번째 자석이거나 왼쪽 자석과 붙어있는 날의 자성이 같다면 종료
		if (left < 0 || (getRight(left) == getLeft(left + 1))) {
			break;
		}

		// 자성이 다르다면 왼쪽 자석의 회전방향을 현재 자석의 회전방향의 반대방향으로 저장
		if (dir[left + 1] == 1) {
			dir[left] = -1;
		}
		else {
			dir[left] = 1;
		}
		left--; // 왼쪽 자석으로 이동
	}

	// num번 자석 오른쪽 자석들의 회전 방향을 구함
	int right = num + 1;
	while (1) {
		// 현재 마지막 자석이거나 오른쪽 자석과 붙어있는 날의 자성이 같다면 종료
		if (right >= 4 || (getRight(right - 1) == getLeft(right))) {
			break;
		}

		// 자성이 다르다면 오른쪽 자석의 회전방향을 현재 자석의 회전방향의 반대방향으로 저장
		if (dir[right - 1] == 1) {
			dir[right] = -1;
		}
		else {
			dir[right] = 1;
		}
		right++; // 오른쪽 자석으로 이동
	}

	return dir; // 회전방향 배열을 리턴
}

int main(int argc, char** argv)
{
	int test_case;
	int T;

	cin >> T;

	for (test_case = 1; test_case <= T; ++test_case)
	{
		int K;
		int num;
		int d;
		vector<int> dir;

		cin >> K;

		// 자석들의 자성을 저장
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 8; j++) {
				cin >> mg[i][j];
			}
		}

		for (int i = 0; i < K; i++) {
			cin >> num >> d;

			dir = getDir(num - 1, d); // 자석들의 회전방향을 구함

			for (int j = 0; j < 4; j++) { // 자석들을 확인하면서
				if (dir[j] == 0) { // 회전하지 않는 자석들은 넘어감
					continue;
				}
				rotate(j, dir[j]); // j번째 자석을 dir[j]방향으로 회전
			}
		}

		int sum = 0;
		int score = 1;
		for (int i = 0; i < 4; i++) { // 자석들을 확인하면서
			if (mg[i][0] == 1) { // 맨 위 자성이 S극이면 점수획득
				sum += score;
			}
			score *= 2;
		}

		cout << "#" << test_case << " " << sum << endl;
	}

	return 0;
}