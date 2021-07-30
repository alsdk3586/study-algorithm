#include <iostream>
#include <algorithm>
#include <vector>
#include<queue>

using namespace std;
//아기상어의 위치가 주어졌을때, 아기상어의 위치를 기준으로
//상하좌우 인접한 영역을 탐색해야하므로 BFS알고리즘을 사용한다. 
#define INF 987654321 
int N;
int map[20][20];
int dr[4] = { -1, 1, 0, 0 };
int ds[4] = { 0, 0, -1, 1 };
//아기상어의 위치와 이동거리를 담을 구조체변수 선언
typedef struct Pos
{
	int sr;
	int sc;
	int dis;
}Pos;

int BFS(int sr, int sc)
{
	//초기변수 셋팅
	int sec=0;
	int weight = 2;
	int cnt = 2;
	Pos minDis = { sr, sc, 0 };

	//최단거리를 구하기 위해 do-while문 사용
	do
	{
		bool checked[20][20] = { false };
		queue<Pos> Q;
		//현재 위치 checked 해준 뒤 Q에 넣기
		checked[minDis.sr][minDis.sc] = true;
		Q.push({ minDis.sr, minDis.sc, 0 });
		//최단거리를 구하기 위해 최댓값 INF을 넣는다.
		minDis.dis = INF;

		while (!Q.empty())
		{
			Pos now = Q.front();
			Q.pop();

			if (now.dis > minDis.dis)
				break;
			if (map[now.sr][now.sc] > weight)
				continue;
			//자신보다 더 작은 물고기를 만난 경우에는 물고기를 먹어야 하므로 
			//minDis값을 now로 업데이트 해준다.
			if (0 < map[now.sr][now.sc] && map[now.sr][now.sc] < weight)
			{
				//현재 거리에 대한 최솟값 업데이트 
				if (now.dis < minDis.dis)
					minDis = now;

				//문제조건
				//거리가 가까운 물고기가 많을때,
				else if(now.dis == minDis.dis)
				{
					//가장 위에 있는 물고기를 먹는다.
					if (now.sr < minDis.sr)
						minDis = now;

					//가장 위에 있는 물고기가 여러마리라면, 가장 왼쪽에 있는 물고기를 먹는다.
					else if (now.sr == minDis.sr && now.sc < minDis.sc)
							minDis = now;
				}
				//그 외의 경우 continue 시킨다.
				continue;
			}
			//현재 위치에서 상하좌우로 이동하면서 Q에 값을 넣는다.
			for (int i = 0; i < 4; i++)
			{
				int rr = now.sr + dr[i];
				int ss = now.sc + ds[i];

				//범위를 벗어나면 continue
				if (rr < 0 || ss < 0 || rr >= N || ss >= N)
					continue;
				//이미 방문한 곳이면 continue
				if(checked[rr][ss])
					continue;

				//그 외의 경우 방문체크를 하고 Q에 값을 넣는다.
				checked[rr][ss] = true;
				Q.push({ rr, ss, now.dis+1 });
			}
		}
		//물고기 잡아 먹은 후 값을 업데이트 해준다.
		//최단거리가 갱신 되었다면
		if (minDis.dis != INF)
		{
			//초를 업데이트 한다.
				sec += minDis.dis;
				//물고기를 먹은 수만큼 cnt를 줄이고, 
				//cnt가 0이 되면 몸무게를 1 늘리고 cnt를 몸무게로 업데이트 한다.
				cnt--;
				if (cnt == 0)
				{
					weight += 1;
					cnt = weight;
				}
				//물고기 먹은 후 좌표 0으로 업데이트 해준다.
				map[minDis.sr][minDis.sc] = 0;
		}
	} while (minDis.dis != INF);
	
	return sec;
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	int row=0, col=0;
	cin >> N;

	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			cin >> map[i][j];
			//아기상어의 위치에 도달했을때 row, col에 해당인덱스를 넣어준다.
			if (map[i][j] == 9)
			{
				map[i][j] = 0;
				row = i;
				col = j;
			}
		}
	}

	cout << BFS(row, col) << "\n";
	return 0;
}