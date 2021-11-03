#define _CRT_SECURE_NO_WARNINGS
#include <string>
#include <queue>
#include <string.h>
#include <string>
#include <iostream>
using namespace std;

//cost가 없는 최단경로 문제이므로 BFS알고리즘을 사용한다.
//**벽을 부순적이 있는지 체크해야하므로 checked배열에 breakingWall을 추가하여 3차원 배열을 생성한다.
int map[1001][1001];
int checked[1001][1001][2];
int N, M;
//방향 :상 하 좌 우
int dx[4] = { 0, 0, -1, 1 };
int dy[4] = { 1, -1, 0, 0 };
//큐에서 구조체 형태로 입력받기 위해 구조체 선언.
typedef struct pos
{
	//**순서주의
	int yy;
	int xx;
	int breakingWall;
}pos;

int BFS(void)
{
	queue<pos> Q;
	//처음 입력받은 값 setting
	Q.push({ 1, 1, 0 });
	checked[1][1][0] = 1;

	while (!Q.empty())
	{
		pos now = Q.front();
		Q.pop();
		//끝에 도달하면 출력
		if (now.yy == N && now.xx == M)
			return checked[now.yy][now.xx][now.breakingWall];

		// 상하좌우까지 돌면서 next에 값 넣어주기
		for (int i = 0; i < 4; i++)
		{
			//next값 초기화
			pos next;
			next.yy = now.yy + dy[i];
			next.xx = now.xx + dx[i];
			next.breakingWall = now.breakingWall;

			//범위를 벗어나는 경우 continue
			if (next.yy > N || next.xx > M || next.yy <= 0 || next.xx <= 0)
				continue;
			//checked배열에 0제외한 값이 있는 경우 continue
			if (checked[next.yy][next.xx][now.breakingWall])
				continue;
			//next값이 0인 경우
			if (map[next.yy][next.xx] == 0)
			{
				//next checked배열에 now checked배열 +1 해주면서 카운팅
				checked[next.yy][next.xx][next.breakingWall] = checked[now.yy][now.xx][now.breakingWall] + 1;
				//Q에 next값 넣어줌
				//**세번째인자값은 현재까지 벽을 부순적이 있는지 없는지를 담아야 하므로 now.breakingWall을 넣어줌
				Q.push({ next.yy, next.xx, now.breakingWall });
			}
			//next값이 1이고, 현재까지 벽을 부순 적이 없는 경우
			if (map[next.yy][next.xx] == 1 && now.breakingWall = 0)
			{
				//next값이 1이므로 벽을 부숨 -> breakingWall을 1로 셋팅
				next.breakingWall = 1;
				//next checked배열에 now checked배열 + 1 해주면서 카운팅
				checked[next.yy][next.xx][1] = checked[now.yy][now.xx][0] + 1;
				//Q에 next값 넣어줌
				//여기서는 이미 세번째 인자값을 1로 셋팅해주었기 때문에 그냥 next값을 넣어주면 됨
				Q.push(next);
			}

		}
	}
	return -1;
}
int main()
{
	cin >> N >> M;
	for (int i = 1; i <= N; i++)
	{
		for (int j = 1; j <= M; j++)
		{
			//cin >> map[i][j];
			//하나씩 입력받기 위해 scanf로 받아준다.
			scanf("%1d", &map[i][j]);
		}
	}
	cout << BFS();
	return 0;
}
