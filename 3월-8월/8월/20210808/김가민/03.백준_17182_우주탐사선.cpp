#include<iostream>
#include<algorithm>
#include<math.h>
#include<cstring>
#include<fstream>
#define MAX 987654321
using namespace std;
int map[10][10];
bool checked[10];
int ans = MAX, node, pos;
//플로이드 와샬 알고리즘을 이용하여 미리 최소값을 업데이트 시킨다.
//이후 DFS 사용하여 행성 1에서 2까지 최단거리를 구한다.

void DFS(int idx, int cnt, int dis)
{
	//ans가 최솟값이면 return
	if (ans < dis)
		return;
	//행성탐사갯수가 입력받은node와 같으면 ans에 최솟값을 업데이트하고 return
	if (cnt == node)
	{
		ans = min(ans, dis);
		return;
	}
	//입력받은 행성의 개수만큼 돌면서 행성의 인덱스, 탐사한 행성수, 걸리는 시간을 DFS로 돌린다.
	//checked 방문여부 확인(이미 플로이드 와샬 사용하여 최단거리 업뎃해줬기 때문에)
	for (int i = 0; i < node; i++)
	{
		if (checked[i])
			continue;
		checked[i] = true;
		DFS(i, cnt + 1, dis + map[idx][i]);
		checked[i] = false;
	}
}
int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	//체크배열 초기화
	memset(checked, false, sizeof(checked));
	cin >> node >> pos;

	for (int i = 0; i < node; i++)
	{
		for (int j = 0; j < node; j++)
		{
			cin >> map[i][j];
		}
	}
	//발사되는 행성 위치 방문체크
	checked[pos] = true;
	//플로이드 와샬로 최단거리 미리 세팅해준다.
	for (int k = 0; k < node; k++)
	{
		for (int i = 0; i < node; i++)
		{
			for (int j = 0; j < node; j++)
			{
				if (map[i][k] + map[k][j] < map[i][j])
					map[i][j] = map[i][k] + map[k][j];
			}
		}
	}
	//DFS에는 발사되는 행성위치, 행성탐사갯수, 걸리는 시간 매개변수로 넘겨준다.
	DFS(pos, 1, 0);
	cout << ans << "\n";
	return 0;
}