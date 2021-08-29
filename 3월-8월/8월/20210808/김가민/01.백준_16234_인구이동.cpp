#include<iostream>
#include<algorithm>
#include<vector>
#include<math.h>
#include<cstring>
#include<fstream>
using namespace std;
//국경선은 상하좌우로 열수 있고 각 나라와의 L, R을 기준으로 연합하기 때문에 
//DFS로 완탐하면서 각 나라와 연합한다.
int N, L, R, cnt = 0, sum = 0;
int map[51][51];	//n*n크기의 땅
vector<pair<int, int>> vec;	//연합 후 인구수 유지를 위해 연합한 나라의 위치를 담을 벡터(행, 열)
bool checked[51][51]; //각 나라의 연합여부 체크할 배열 
//상 하 좌 우
int dr[4] = { 1, -1, 0, 0 };
int dc[4] = { 0, 0, -1, 1 };

void DFS(int row, int col)
{
	//4방향으로 탐색하면서 DFS를 돌림
	for (int i = 0; i < 4; i++)
	{
		int sr = row + dr[i];
		int sc = col + dc[i];

		//해당 위치에 방문하지 않았고 두나라의 인구차이가 L이상 R미만이면
		//sum 에 두나라의 인구수를 더해준 뒤 연합한 나라+1 시킨다.
		//후에 연합한 나라의 인구수를 업데이트 시켜주기 위해 vec에 해당나라의 위치(행, 열)를 넣는다.
		if (!checked[sr][sc])
		{
			if (0 <= sr && sr < N && 0 <= sc && sc < N)
			{
				int val = abs(map[row][col] - map[sr][sc]);
				if (L <= val && val <= R)
				{
					checked[sr][sc] = true;
					sum += map[sr][sc];
					cnt++;
					vec.push_back(make_pair(sr, sc));
					DFS(sr, sc);
				}
			}
		}
	}
}
int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	int ans = 0, avg = 0;
	cin >> N >> L >> R;

	for (int i = 0; i < N; ++i)
	{
		for (int j = 0; j < N; ++j)
		{
			cin >> map[i][j];
		}
	}
	
	while (1)
	{
		//flag, 체크배열 초기화
		bool flag = false;
		memset(checked, false, sizeof(checked));
		for (int i = 0; i < N; ++i)
		{
			for (int j = 0; j < N; ++j)
			{
				//방문하지 않았다면
				if (!checked[i][j])
				{
					//vec, cnt, sum, 체크배열 초기화
					vec.clear();
					cnt = 1;
					sum = map[i][j];
					checked[i][j] = true;
					//인구이동을 위해 처음 입력받은 나라의 위치를 벡터에 넣고 DFS를 돌림
					vec.push_back(make_pair(i, j));
					DFS(i, j);
					//연합한 나라가 2이상이면 avg값을 구하고 연합한 나라의 인구수를 avg로 업데이트시킴
					if (cnt >= 2)
					{
						flag = true;
						avg = sum / cnt;
						for (int k = 0; k < vec.size(); k++)
						{
							map[vec[k].first][vec[k].second] = avg;
						}
					}
				}
			}
		}
		if (!flag)
			break;
		else
			ans++;
	}
	cout << ans << "\n";
	return 0;
}