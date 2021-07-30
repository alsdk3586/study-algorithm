#include <algorithm>
#include <vector>
#include <iostream>
#include <set>
#include <cstring>
#include <fstream>
using namespace std;
//길을 건너지 않으면 만날 수 없는 소를 출력한다 = 길을 이용해야만하는 소들을 출력한다.
//목초지의 끝까지 완전탐색하면서 방문체크를 해야하므로 DFS알고리즘을 이용한다.

vector<pair<int, int>> pos;	//소의 위치
set<pair<int, int>> map[101][101];	//받은 길의 위치
bool checked[101][101];	//목초지 방문 체크할 변수
int N, K, R;
//상 하 좌 우
int dr[4] = { 0, 0, -1, 1 };
int dc[4] = { -1, 1, 0, 0 };

void DFS(int r, int c)
{
	//범위 벗어난 경우 return 
	if (r<0 || c<0 || r>N || c>N)
		return;
	//방문 체크
	checked[r][c] = true;
	//상 하 좌 우 돌면서 방문하지 않은 경우&&두 목초지 사이에 길이 없는 경우에만 DFS 돌린다.
	for (int i = 0; i < 4; i++)
	{
		int row = r + dr[i];
		int col = c + dc[i];

		if (checked[row][col] || map[r][c].count({ row, col }))
			continue;

		DFS(row, col);
	}
}
int main()
{
	cin >> N >> K >> R;
	int r, c, r1, c1, a, b, answer=0;
	for (int i = 0; i < R; i++)
	{
		//입력받은 후 map에 양방향으로 넣어줌
		cin >> r >> c >> r1 >> c1;
		map[r][c].insert({ r1, c1 });
		map[r1][c1].insert({ r, c });

	}

	//K 까지 돌면서 소의 위치 입력받음
	for (int i = 0; i < K; i++)
	{
		cin >> a >> b;
		pos.push_back({ a, b });
	}

	//입력받은 소의 마리 만큼 돌면서 소1과 소2가 길을 이용하지 않고 방문할 수 있는지 체크한다.

	for (int i = 0; i < pos.size(); i++)
	{
		//방문 체크 변수 초기화
		memset(&checked, false, sizeof(checked));
		//DFS이용하여 정사각형 목초지 완탐하면서 길을 이용하지 않고 목초지를 방문할 수 있는지 체크
		DFS(pos[i].first, pos[i].second);
		for (int j = i + 1; j < pos.size(); j++)
		{
			//소2가 방문체크 되지 않은 경우는 길을 이용해야하므로 answer++해준다.
			if (!checked[pos[j].first][pos[j].second])
				answer++;
		}
	}
	cout << answer << "\n";
	return 0;
}