#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <climits>
#include <queue>>

using namespace std;

vector<vector<int>> tmp; // board값 임시저장
vector<int> cardNum; // 카드번호 저장
vector<pair<int, int>> cardPos[7]; // cardPos[n] -> n번 카드의 위치1,2
int cardCnt;
int minCost;
int dr[] = { 1,0,-1,0 };
int dc[] = { 0,1,0,-1 };

// 좌표값이 범위안에 있는지 체크
bool check(int x, int y) {
	if (x >= 0 && y >= 0 && x < 4 && y < 4) {
		return true;
	}
	else {
		return false;
	}
}

// (sr,sc) -> (er, ec)로 가는 최단경로
int bfs(int sr, int sc, int er, int ec) {
	queue<pair<pair<int, int>, int>> q; // {카드 위치, 비용}
	vector<vector<bool>> visited(4, vector<bool>(4, false)); // 위치 방문 체크

	q.push({ make_pair(sr,sc),0 });
	visited[sr][sc] = true;

	while (!q.empty()) {
		int r = q.front().first.first;
		int c = q.front().first.second;
		int cost = q.front().second;
		q.pop();

		for (int i = 0; i < 8; i++) {
			int nr = r;
			int nc = c;

			if (i < 4) { // 상하좌우
				nr += dr[i];
				nc += dc[i];
			}
			else { // ctrl 누른 상태에서 이동
				int j = i - 4;
				while (check(nr + dr[j], nc + dc[j])) {
					nr += dr[j];
					nc += dc[j];
					if (tmp[nr][nc] != 0)
						break;
				}
			}

			// 아직 방문 안한 위치면 큐에 저장
			if (check(nr, nc) && visited[nr][nc] == 0) {
				visited[nr][nc] = 1;
				q.push({ {nr, nc}, cost + 1 });
				if (nr == er && nc == ec) { // 이동한 위치가 도착 위치면 리턴
					return cost + 1;
				}
			}
		}
	}

	return 0;
}

// (r, c)에서 idx번째 카드 지우기
void dfs(int idx, int r, int c, int cost) {
	if (cost > minCost) { // 현재까지 비용이 최저 비용보다 크다면 중단
		return;
	}

	// 모든 카드를 지웠으면 비용 확인
	if (idx == cardCnt) {
		if (minCost > cost) {
			minCost = cost;
		}
		return;
	}

	int num = cardNum[idx]; // 제거해야 할 카드 번호
	pair<int, int> cardA = cardPos[num][0]; // num번 카드 위치1
	pair<int, int> cardB = cardPos[num][1]; // num번 카드 위치2


	// 현재 위치 -> numA -> numB
	int costAB = bfs(r, c, cardA.first, cardA.second)
		+ bfs(cardA.first, cardA.second, cardB.first, cardB.second) + 2;
	// 현재 위치 -> numB -> numA
	int costBA = bfs(r, c, cardB.first, cardB.second)
		+ bfs(cardB.first, cardB.second, cardA.first, cardA.second) + 2;

	// num번 카드를 지웠다고 표시
	tmp[cardA.first][cardA.second] = 0;
	tmp[cardB.first][cardB.second] = 0;

	dfs(idx + 1, cardB.first, cardB.second, cost + costAB); // numA -> numB 순서로 제거
	dfs(idx + 1, cardA.first, cardA.second, cost + costBA); // numB -> numA 순서로 제거

	// 재귀에서 빠져나올 때 다시 카드를 표시
	tmp[cardA.first][cardA.second] = num;
	tmp[cardB.first][cardB.second] = num;

	return;
}

int solution(vector<vector<int>> board, int r, int c) {
	int answer = 0;
	vector<int> numCheck(7, 0);
	minCost = INT_MAX;

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (board[i][j] != 0) {
				if (numCheck[board[i][j]] == 0) { // 새로운 종류의 카드면 카드번호변수에 저장
					cardNum.push_back(board[i][j]);
					numCheck[board[i][j]] = 1;
					cardCnt++;
				}
				cardPos[board[i][j]].push_back(make_pair(i, j)); // 카드 위치 저장
			}
		}
	}

	sort(cardNum.begin(), cardNum.end()); // 카드 번호 정렬

	// 카드를 제거하는 순서의 모든 경우를 구하고 전부 dfs탐색
	do {
		tmp = board; // 카드 위치 갱신
		dfs(0, r, c, 0); // r,c에서 출발
	} while (next_permutation(cardNum.begin(), cardNum.end())); // 모든 순서 경우

	answer = minCost;

	return answer;
}

/*
*{1,2,3} 카드
-1 -> 2 -> 3
-1 -> 3 -> 2
-2 -> 1 -> 3
-2 -> 3 -> 1
-3 -> 1 -> 2
-3 -> 2 -> 1

*카드 위치
-카드1A : (1ar, 1ac)
-카드1B : (1br, 1bc)
-카드2A : (2ar, 2ac)
-카드2B : (2br, 2bc)
-카드3A : (3ar, 3ac)
-카드3B : (3br, 3bc)

*1 -> 2 -> 3 순서
					   [1번 카드]                       [2번 카드]                       [3번 카드]
(r, c) -->	(1ar, 1ac) -> (1br, 1bc) --> (2ar, 2ac) -> (2br, 2bc) --> (3ar, 3ac) -> (3br, 3bc)

																				 --> (3br, 3bc) -> (3ar, 3ac)

											--> (2br, 2bc) -> (2ar, 2ac) --> (3ar, 3ac) -> (3br, 3bc)

																				 --> (3br, 3bc) -> (3ar, 3ac)


	   -->	(1br, 1bc) -> (1ar, 1ac) --> (2ar, 2ac) -> (2br, 2bc) --> (3ar, 3ac) -> (3br, 3bc)

																				 --> (3br, 3bc) -> (3ar, 3ac)

											--> (2br, 2bc) -> (2ar, 2ac) --> (3ar, 3ac) -> (3br, 3bc)

																				--> (3br, 3bc) -> (3ar, 3ac)
*/

