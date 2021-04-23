#include <string>
#include <vector>
#include <queue>
#include <climits>
#include <algorithm>

using namespace std;

// 로봇의 좌표값과 비용을 저장하는 구조체
typedef struct _pos {
	int x1;
	int y1;
	int x2;
	int y2;
	int cost;
}Pos;
queue<Pos> q;
int N;
// dp[x1][y1][x2][y2] -> (x1,y1),(x2,y2)에 걸쳐있는 로봇의 최소 이동경로
// 로봇이 어떠한 방향으로 이동했든지 (x2 >= x1) && (y2 >= y1)로 계산
int dp[101][101][101][101];
int minDp; // 목적지까지의 최소비용

// 새로운 좌표로 이동하는 함수
void check(vector<vector<int>>& board, int nx1, int ny1, int nx2, int ny2, int cost) {
	// 유효범위를 벗어나면 리턴
	if (nx1 < 0 || nx1 >= N || ny1 < 0 || ny1 >= N ||
		nx2 < 0 || nx2 >= N || ny2 < 0 || ny2 >= N) {
		return;
	}

	// 이동하려는 곳이 벽이면 리턴
	if (board[nx1][ny1] == 1 || board[nx2][ny2] == 1) {
		return;
	}

	// 이동하려는 좌표에 처음 도착하거나 기존의 비용보다 적게 이동 가능할 때만 저장
	if (dp[nx1][ny1][nx2][ny2] == 0 || dp[nx1][ny1][nx2][ny2] > cost + 1) {
		q.push({ nx1,ny1,nx2,ny2,cost + 1 });

		dp[nx1][ny1][nx2][ny2] = cost + 1;

		if (nx2 == N - 1 && ny2 == N - 1) { // 두 번째 바퀴가 목적지에 도착했을 때
			minDp = min(minDp, dp[nx1][ny1][nx2][ny2]); // 최소값이면 갱신
		}
	}

	return;
}

// 로봇이 가로로 배치되어있을 때 회전
void rotateRow(vector<vector<int>>& board, int x1, int y1, int x2, int y2, int cost) {
	int nx1;
	int ny1;
	int nx2;
	int ny2;

	// 왼쪽 위 방향으로 회전
	if (x1 != 0 && board[x2 - 1][y2] != 1) { // 오른쪽 위가 벽이 아닐 때만 이동
		nx1 = x1 - 1;
		ny1 = y1;
		nx2 = x1;
		ny2 = y1;
		check(board, nx1, ny1, nx2, ny2, cost);
	}

	// 오른쪽 위 방향으로 회전
	if (x1 != 0 && board[x1 - 1][y1] != 1) { // 왼쪽 위가 벽이 아닐 때만 이동
		nx1 = x2 - 1;
		ny1 = y2;
		nx2 = x2;
		ny2 = y2;
		check(board, nx1, ny1, nx2, ny2, cost);
	}

	// 왼쪽 아래 방향으로 회전
	if (x1 != N - 1 && board[x2 + 1][y2] != 1) { // 오른쪽 아래가 벽이 아닐 때만 이동
		nx1 = x1;
		ny1 = y1;
		nx2 = x1 + 1;
		ny2 = y1;
		check(board, nx1, ny1, nx2, ny2, cost);
	}

	// 오른쪽 아래 방향으로 회전
	if (x1 != N - 1 && board[x1 + 1][y1] != 1) { // 왼쪽 아래가 벽이 아닐 때만 이동
		nx1 = x2;
		ny1 = y2;
		nx2 = x2 + 1;
		ny2 = y2;
		check(board, nx1, ny1, nx2, ny2, cost);
	}
}

// 로봇이 세로로 배치되어있을 때 회전
void rotateColumn(vector<vector<int>>& board, int x1, int y1, int x2, int y2, int cost) {
	int nx1;
	int ny1;
	int nx2;
	int ny2;

	// 왼쪽 위 방향으로 회전
	if (y1 != 0 && board[x2][y2 - 1] != 1) { // 왼쪽 아래가 벽이 아닐 때만 이동
		nx1 = x1;
		ny1 = y1 - 1;
		nx2 = x1;
		ny2 = y1;
		check(board, nx1, ny1, nx2, ny2, cost);
	}

	// 오른쪽 위 방향으로 회전
	if (y1 != N - 1 && board[x2][y2 + 1] != 1) { // 오른쪽 아래가 벽이 아닐 때만 이동
		nx1 = x1;
		ny1 = y1;
		nx2 = x1;
		ny2 = y1 + 1;
		check(board, nx1, ny1, nx2, ny2, cost);
	}

	// 왼쪽 아래 방향으로 회전
	if (y1 != 0 && board[x1][y1 - 1] != 1) { // 왼쪽 위가 벽이 아닐 때만 이동
		nx1 = x2;
		ny1 = y2 - 1;
		nx2 = x2;
		ny2 = y2;
		check(board, nx1, ny1, nx2, ny2, cost);
	}

	// 오른쪽 아래 방향으로 회전
	if (y1 != N - 1 && board[x1][y1 + 1] != 1) { // 오른쪽 위가 벽이 아닐 때만 이동
		nx1 = x2;
		ny1 = y2;
		nx2 = x2;
		ny2 = y2 + 1;
		check(board, nx1, ny1, nx2, ny2, cost);
	}
}

int solution(vector<vector<int>> board) {
	int answer = 0;

	N = board.size();
	minDp = INT_MAX;

	int dx1[] = { -1,1,0,0 };
	int dy1[] = { 0,0,-1,1 };
	int dx2[] = { -1,1,0,0 };
	int dy2[] = { 0,0,-1,1 };

	q.push({ 0,0,0,1,0 }); // 초기값 (0,0),(0,1)에 0의 비용으로 걸쳐있는 상태에서 출발

	while (!q.empty()) {
		int x1 = q.front().x1;
		int y1 = q.front().y1;
		int x2 = q.front().x2;
		int y2 = q.front().y2;
		int cost = q.front().cost;

		q.pop();

		// 상하좌우 이동
		for (int i = 0; i < 4; i++) {
			int nx1 = x1 + dx1[i];
			int ny1 = y1 + dy1[i];
			int nx2 = x2 + dx2[i];
			int ny2 = y2 + dy2[i];

			check(board, nx1, ny1, nx2, ny2, cost);
		}

		// 회전
		if (x1 == x2) { // 로봇이 가로 방향일 때
			rotateRow(board, x1, y1, x2, y2, cost);
		}
		else { // 로봇이 세로 방향일 때
			rotateColumn(board, x1, y1, x2, y2, cost);
		}
	}

	answer = minDp;

	return answer;
}