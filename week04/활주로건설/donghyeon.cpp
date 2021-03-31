#include<iostream>
#include <cstdio>
#include <cmath>

using namespace std;

int map[21][21];
bool buildChk[21]; // buildChk[i] = true -> 가로or세로 특정 라인에서 i번째에 활주로가 건설되어있음
int N, X;

// 인덱스 유효범위 체크
bool checkRange(int idx) {
	if (idx < 0 || idx >= N) {
		return false;
	}
	return true;
}

// 두 지형 간 높이 차이를 구하는 함수
int checkHeightDiff(int height1, int height2) {
	if (abs(height1 - height2) >= 2) { // 높이 차이가 2 이상이면 활주로 건설 불가
		return -1;
	}

	if (abs(height1 - height2) == 0) { // 높이가 같다면 넘어감
		return 0;
	}

	if (height1 > height2) { // 왼쪽 지형이 높이가 1만큼 더 큼
		return 1;
	}
	else { // 오른쪽 지형이 높이가 1만큼 더 큼
		return 2;
	}
}

// map[x][y]를 기준으로 왼쪽 가로 방향으로 활주로 건설
bool buildLeft(int x, int y) {
	int height = map[x][y]; // 기준 높이
	buildChk[y] = true; // y번 지형에 활주로 건설

	// (x,y)를 기준으로 왼쪽으로 X만큼 떨어진 곳까지 탐색하며 활주로 건설
	for (int i = 1; i < X; i++) {
		// 건설하려는 위치가 범위에서 벗어나거나, 기준 높이와 높이가 다르거나, 이미 활주로가 건설되어 있다면 
		// return false
		if (checkRange(y - i) == false || map[x][y - i] != height || buildChk[y - i] == true) {
			return false;
		}
		buildChk[y - i] = true;
	}

	return true;
}

// map[x][y]를 기준으로 오른쪽 가로 방향으로 활주로 건설
bool buildRight(int x, int y) {
	int height = map[x][y]; // 기준 높이
	buildChk[y] = true; // y번 지형에 활주로 건설

	// (x,y)를 기준으로 오른쪽으로 X만큼 떨어진 곳까지 탐색하며 활주로 건설
	for (int i = 1; i < X; i++) {
		// 건설하려는 위치가 범위에서 벗어나거나, 기준 높이와 높이가 다르거나, 이미 활주로가 건설되어 있다면 
		// return false
		if (checkRange(y + i) == false || map[x][y + i] != height || buildChk[y + i] == true) {
			return false;
		}
		buildChk[y + i] = true;
	}

	return true;
}

// map[x][y]를 기준으로 위쪽 세로 방향으로 활주로 건설
bool buildUp(int x, int y) {
	int height = map[x][y];
	buildChk[x] = true;

	// (x,y)를 기준으로 위쪽으로 X만큼 떨어진 곳까지 탐색하며 활주로 건설
	for (int i = 1; i < X; i++) {
		// 건설하려는 위치가 범위에서 벗어나거나, 기준 높이와 높이가 다르거나, 이미 활주로가 건설되어 있다면 
		// return false
		if (checkRange(x - i) == false || map[x - i][y] != height || buildChk[x - i] == true) {
			return false;
		}
		buildChk[x - i] = true;
	}

	return true;
}

// map[x][y]를 기준으로 아래쪽 세로 방향으로 활주로 건설
bool buildDown(int x, int y) {
	int height = map[x][y];
	buildChk[x] = true;

	// (x,y)를 기준으로 아래쪽으로 X만큼 떨어진 곳까지 탐색하며 활주로 건설
	for (int i = 1; i < X; i++) {
		// 건설하려는 위치가 범위에서 벗어나거나, 기준 높이와 높이가 다르거나, 이미 활주로가 건설되어 있다면 
		// return false
		if (checkRange(x + i) == false || map[x + i][y] != height || buildChk[x + i] == true) {
			return false;
		}
		buildChk[x + i] = true;
	}

	return true;
}

// 가로 방향 점검 -> 행의 값은 인자값으로 고정
bool checkRow(int x) {
	int flag = true; // 기본값으로 활주로 건설 가능
	int y;

	// 모든 열을 탐색하면서 
	for (int i = 0; i < N; i++) {
		y = i + 1; // 오른쪽 지형의 인덱스 설정
		if (checkRange(y)) { // 유효범위만 점검
			int height_diff = checkHeightDiff(map[x][i], map[x][y]); // 지형간의 높이차를 구함

			if (height_diff < 0) { // 지형 간 높이차가 2이상이면 활주로 건설 불가
				flag = false;
				break;
			}
			else if (height_diff == 1) { // 왼쪽 지형의 높이가 1만큼 더 큰 경우
				if (buildRight(x, y) == false) { // 오른쪽 방향으로 활주로 건설이 불가능하면 false 리턴
					flag = false;
					break;
				}
			}
			else if (height_diff == 2) { // 오른쪽 지형의 높이가 1만큼 더 큰 경우
				if (buildLeft(x, i) == false) { // 왼쪽 방향으로 활주로 건설이 불가능하면 false 리턴
					flag = false;
					break;
				}
			}
		}
	}

	// 활주로 건설 표시 초기화
	for (int i = 0; i < N; i++) {
		buildChk[i] = 0;
	}

	return flag;
}

// 세로 방향 점검 -> 열의 값은 인자값으로 고정
bool checkColumn(int y) {
	int flag = true; // 기본값으로 활주로 건설 가능
	int x;

	// 모든 행을 탐색하면서 
	for (int i = 0; i < N; i++) {
		x = i + 1; // 아래 지형의 인덱스 설정
		if (checkRange(x)) { // 유효범위만 점검
			int height_diff = checkHeightDiff(map[i][y], map[x][y]); // 지형간의 높이차를 구함

			if (height_diff < 0) { // 지형 간 높이차가 2이상이면 활주로 건설 불가
				flag = false;
				break;
			}
			else if (height_diff == 1) { // 위쪽 지형의 높이가 1만큼 더 큰 경우
				if (buildDown(x, y) == false) { // 아래쪽 방향으로 활주로 건설이 불가능하면 false 리턴
					flag = false;
					break;
				}
			}
			else if (height_diff == 2) { // 아래쪽 지형의 높이가 1만큼 더 큰 경우
				if (buildUp(i, y) == false) { // 위쪽 방향으로 활주로 건설이 불가능하면 false 리턴
					flag = false;
					break;
				}
			}
		}
	}

	// 활주로 건설 표시 초기화
	for (int i = 0; i < N; i++) {
		buildChk[i] = 0;
	}

	return flag;
}

int main(int argc, char** argv)
{
	int test_case;
	int T;

	cin >> T;

	for (test_case = 1; test_case <= T; ++test_case)
	{
		int answer = 0;
		cin >> N >> X;

		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				cin >> map[i][j];
			}
		}

		// 0 ~ N-1까지 모든 행과 열을 탐색
		for (int i = 0; i < N; i++) {
			if (checkRow(i)) { // i번 행에 활주로 건설 가능하면 count++
				answer++;
			}
			if (checkColumn(i)) { // i번 열에 활주로 건설 가능하면 count++
				answer++;
			}
		}

		cout << "#" << test_case << " " << answer << endl;
	}

	return 0;
}