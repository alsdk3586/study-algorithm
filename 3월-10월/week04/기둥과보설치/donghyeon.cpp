#include <string>
#include <vector>
#include <algorithm>

using namespace std;

// map[x][y][0] = true -> x,y를 기준으로 위쪽 방향으로 기둥 설치
// map[x][y][1] = true -> x,y를 기준으로 오른쪽 방향으로 보 설치
bool map[101][101][2];
int length; // map의 크기를 저장

// 최종 구조물의 상태를 정렬하는 함수
// [x,y,a]에서 x값, y값, a값 기준으로 오름차정렬
bool cmp(vector<int> a1, vector<int> a2) {
	if (a1[0] != a2[0]) {
		return a1[0] < a2[0];
	}
	else {
		if (a1[1] != a2[1]) {
			return a1[1] < a2[1];
		}
		else {
			return a1[2] < a2[2];
		}
	}
}

// return true -> x,y에 기둥을 설치하는 조건만족
bool check_gidung(int x, int y) {
	if (x == length) { // 바닥이면 무조건 설치 가능
		return true;
	}
	if (map[x + 1][y][0] == true) { // 설치하려는 위치 아래에 기둥이 있으면 설치 가능
		return true;
	}
	// 설치하려는 위치가 보의 끝부분이면 설치 가능
	if (map[x][y][1] == true || (y - 1 >= 0 && map[x][y - 1][1] == true)) {
		return true;
	}

	return false;
}

// return true -> x,y에 보를 설치하는 조건만족
bool check_bo(int x, int y) {
	// 보의 끝부분을 기둥이 받치고 있으면 설치 가능
	if (map[x + 1][y][0] == true || map[x + 1][y + 1][0] == true) {
		return true;
	}
	// 양쪽 끝이 다른 보와 연결되있으면 설치 가능
	if (y - 1 >= 0 && map[x][y - 1][1] == true && y + 1 < length && map[x][y + 1][1] == true) {
		return true;
	}

	return false;
}

// x,y에 a 구조물을 설치하는 함수
// 설치 이전에 해당 위치에 설치 가능한지 확인 작업
void insert_struct(int x, int y, int a) {
	if (a == 0) {
		if (check_gidung(x, y)) {
			map[x][y][0] = true;
		}
	}
	else {
		if (check_bo(x, y)) {
			map[x][y][1] = true;
		}
	}
}

// x,y에 a 구조물을 제거하는 함수
// 제거 이전에 해당 위치에 구조물을 제거할 경우 나머지 구조물들이 조건을 만족하는지 확인
void delete_struct(int x, int y, int a) {
	if (a == 0) { // 기둥을 제거하는 상황
		map[x][y][0] = false; // 우선 기둥을 제거했다고 가정

		if (x - 1 >= 0 && map[x - 1][y][0] == true) { // 제거하려는 위치 위에 기둥이 설치되있다면
			if (check_gidung(x - 1, y) == false) { // 해당 기둥이 조건을 만족하는지 확인 후 조건을 만족못하면
				map[x][y][0] = true; // 기둥을 다시 돌려놓음
				return;
			}
		}
		if (y - 1 >= 0 && map[x - 1][y - 1][1] == true) { // 제거하려는 기둥이 보 오른쪽 끝을 지탱하고 있었다면
			if (check_bo(x - 1, y - 1) == false) { // 해당 보가 조건을 만족하는지 확인 후 조건을 만족못하면
				map[x][y][0] = true; // 기둥을 다시 돌려놓음
				return;
			}
		}
		if (map[x - 1][y][1] == true) { // 제거하려는 기둥이 왼쪽 끝을 지탱하고 있었다면
			if (check_bo(x - 1, y) == false) { // 해당 보가 조건을 만족하는지 확인 후 조건을 만족못하면
				map[x][y][0] = true; // 기둥을 다시 돌려놓음
				return;
			}
		}
	}
	else { // 보를 제거하는 상황
		map[x][y][1] = false; // 우선 보를 제거했다고 가정

		if (y - 1 >= 0 && map[x][y - 1][1] == true) { // 제거하려는 보 왼쪽에 다른 보가 연결되어있다면
			if (check_bo(x, y - 1) == false) { // 해당 보가 조건을 만족하는지 확인 후 조건을 만족못하면
				map[x][y][1] = true; // 보를 다시 돌려놓음
				return;
			}
		}
		if (y + 1 < length && map[x][y + 1][1] == true) { // 제거하려는 보 오른쪽에 다른 보가 연결되어있다면
			if (check_bo(x, y + 1) == false) { // 해당 보가 조건을 만족하는지 확인 후 조건을 만족못하면
				map[x][y][1] = true; // 보를 다시 돌려놓음
				return;
			}
		}
		if (map[x][y][0] == true) { // 제거하려는 보의 왼쪽 끝이 기둥을 받치고 있었다면 
			if (check_gidung(x, y) == false) { // 해당 기둥이 조건을 만족하는지 확인 후 조건을 만족못하면
				map[x][y][1] = true; // 보를 다시 돌려놓음
				return;
			}
		}
		if (y + 1 <= length && map[x][y + 1][0] == true) { // 제거하려는 보의 오른쪽 끝이 기둥을 받치고 있었다면
			if (check_gidung(x, y + 1) == false) { // 해당 기둥이 조건을 만족하는지 확인 후 조건을 만족못하면
				map[x][y][1] = true; // 보를 다시 돌려놓음
				return;
			}
		}
	}
}

vector<vector<int>> solution(int n, vector<vector<int>> build_frame) {
	vector<vector<int>> answer;

	length = n;

	for (int i = 0; i < build_frame.size(); i++) {
		int x = build_frame[i][0];
		int y = build_frame[i][1];
		int a = build_frame[i][2];
		int b = build_frame[i][3];

		// 문제에서의 좌표값을 2차원 배열 인덱스와 맞추기 위한 변환
		// [x,y] -> map[y][n-x]에 구조물을 설치 혹은 제거
		if (b == 0) {
			delete_struct(length - y, x, a);
		}
		else {
			insert_struct(length - y, x, a);
		}
	}

	// 모든 map을 순회하면서 구조물이 설치되어있는 위치를 저장
	// 2차원 배열 인덱스를 문제에서의 좌표값으로 맞추기 위한 변환
	for (int i = 0; i <= length; i++) {
		for (int j = 0; j <= length; j++) {
			if (map[i][j][0]) {
				answer.push_back({ j,n - i,0 });
			}
			if (map[i][j][1]) {
				answer.push_back({ j,n - i,1 });
			}
		}
	}

	sort(answer.begin(), answer.end(), cmp);

	return answer;
}