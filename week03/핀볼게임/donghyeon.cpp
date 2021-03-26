#include <iostream>
#include <cstring>
#include <vector>
#include <stack>
#include <algorithm>

using namespace std;

int maze[101][101];
vector<pair<int, int>> bh;
vector<pair<int, int>> wh[6]; // 각 번호의 웜홀 위치를 저장
// i방향으로 가던 애가 (j + 1)을 만나면 nextD[i][j] 방향으로 바뀜
int nextD[4][5] = { {1,3,2,1,1},{3,0,0,2,0},{0,1,3,3,3},{2,2,1,0,2} };
int N;
int maxScore;

// return 0 -> 블랙홀 만남, return 1 -> 그 외 
int check(int& x, int& y, int& d, int& score) {
	// 벽을 뚫고 나왔다면 벽에 부딪힌 반대 방향으로 방향을 바꿈
	// 점수 증가
	if (x < 0 || x >= N || y < 0 || y >= N) {
		if (x < 0) {
			d = 1;
		}
		else if (x >= N) {
			d = 0;
		}
		else if (y < 0) {
			d = 3;
		}
		else {
			d = 2;
		}
		score++;

		return 1;
	}

	if (maze[x][y] == -1) { // 블랙홀이면 종료
		return 0;
	}

	if (maze[x][y] >= 1 && maze[x][y] <= 5) { // 블록에 부딪혔으면
		d = nextD[d][maze[x][y] - 1]; // 방향 변경
		score++;
	}
	else if (maze[x][y] >= 6) { // 웜홀을 만났으면
		// 해당 숫자의 웜홀 중 현재 위치가 아닌 다른 위치의 웜홀로 이동
		for (int i = 0; i < 2; i++) {
			if (x == wh[maze[x][y] - 6][i].first && y == wh[maze[x][y] - 6][i].second) {
				continue;
			}
			int nx = wh[maze[x][y] - 6][i].first;
			int ny = wh[maze[x][y] - 6][i].second;
			x = nx;
			y = ny;
			break;
		}
	}

	return 1;
}

void dfs(int x, int y, int d) {
	int sx = x;
	int sy = y;
	int score = 0;

	while (1) {
		// 상하좌우 방향에 따른 좌표 이동
		if (d == 0) {
			x--;
		}
		else if (d == 1) {
			x++;
		}
		else if (d == 2) {
			y--;
		}
		else {
			y++;
		}

		// 이동한 좌표값이 처음 위치나 블랙홀이면 종료
		if ((x == sx && y == sy) || check(x, y, d, score) == 0) {
			maxScore = max(maxScore, score);
			break;
		}
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
		cin >> N;

		// 블랙홀, 웜홀, 최대점수 초기화
		bh.clear();
		for (int i = 0; i < 5; i++) {
			wh[i].clear();
		}
		maxScore = 0;

		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				cin >> maze[i][j];
				if (maze[i][j] == -1) {
					bh.push_back(make_pair(i, j));
				}
				else if (maze[i][j] >= 6) {
					// wh[idx] -> (idx + 6)번 웜홀
					wh[maze[i][j] - 6].push_back(make_pair(i, j));
				}
			}
		}

		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				if (maze[i][j] == 0) {
					for (int k = 0; k < 4; k++) { // 상하좌우 방향마다 계산
						dfs(i, j, k);
					}
				}
			}
		}

		cout << "#" << test_case << " " << maxScore << endl;
	}
	return 0;
}