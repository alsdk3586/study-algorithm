#include <cstring>
#include <vector>
#include<iostream>
using namespace std;
//플로이드 와샬로 최단거리를 구하고 모든 도시의 2개 조합을 통해 왕복거리를 찾는다.
int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cin.tie(NULL);

	int N, M;
	int map[101][101];
	cin >> N >> M;
	//배열 초기화
	memset(&map, 10000, sizeof(map));

	for (int i = 1; i <= M; i++)
	{
		int a, b;
		cin >> a >> b;
		//무방향체크
		map[a][b] = map[b][a] = 1;
	}
	//플로이드 와샬로 최단거리 구하기
	for (int k = 1; k <= N; k++)
	{
		for (int i = 1; i <= N; i++)
		{
			for (int j = 1; j <= N; j++)
			{
				//노드가 같은 경우는 0으로 셋팅
				if (i == j)
					map[i][j] = 0;
				map[i][j] = min(map[i][j], map[i][k] + map[k][j]);
			}
		}
	}
	//모든 도시의 조합을 통해 왕복거리 찾기
	int sum = 0;
	int a, b, c;
	c = 10000;
	for (int i = 1; i < N; i++)
	{
		for (int j = i + 1; j <= N; j++)
		{
			sum = 0;
			for (int k = 1; k <= N; k++)
			{
				//왕복거리
				sum += min(map[k][i], map[k][j]) * 2;
			}
			if (sum <= c)
			{
				//a,b,c값 업데이트 시켜줌
				if ((i <= a && j < b) || (sum < c))
				{
					a = i;
					b = j;
					c = sum;
				}
			}
		}
	}
	cout << a << ' ' << b << ' ' << c;
}