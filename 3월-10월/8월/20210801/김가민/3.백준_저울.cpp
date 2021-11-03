#include <algorithm>
#include <iostream>
#include <fstream>
using namespace std;
//2차원 배열을 사용해야하므로 floyd-warshall 알고리즘 사용
//플로이드 와샬 알고리즘은 기본적으로 삼중 for문을 돌리므로 O(N^3)의 시간복잡도를 가진다.
//여기서는 시간제한이 1초인데 N값이 최대 100이므로 1000000, 즉 100만이 되어 1억을 넘지 않는다.
//따라서 1초이내로 구현이 가능하다.
int map[101][101];

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	int N, M, a, b, ans; 

	cin >> N;
	cin >> M;

//두개의 정수를 입력받을 때, 앞의 정수가 뒤의 정수보다 더 크므로 2차원배열을 선언하고 앞의 정수가 더 크다면 1, 작다면 -1로 선언해준다.
	for (int i = 0; i < M; i++)
	{
		cin >> a >> b;
		map[a][b] = 1;
		map[b][a] = -1;
	}
// 노드를 추가로 생성하여 삼중 for문을 돌리면서 거쳐가는 노드에 해당하는 값이 찾고자하는 물건의 무게와 같은 경우, 그리고 0이 아닌 경우에 해당 값을 업데이트 해준다.
	for (int k = 1; k <= N; k++)
	{
		for (int i = 1; i <= N; i++)
		{
			for (int j = 1; j <= N; j++)
			{
				if (map[i][k] == map[k][j] && map[i][k] != 0)
					map[i][j] = map[i][k];
 			}
		}
	}

	//출력을 위해 이중 for문을 돌리면서 ans값에는 본인을 제외한 값을 초기값으로 셋팅해주고 0이 아닌 경우(비교결과를 알 수 있는 경우)에 ans를 하나씩 줄인다.	//i번째 물건과 비교결과를 알 수 없는 물건의 개수를 출력한다.
	for (int i = 1; i <= N; i++)
	{
		ans = N - 1;
		for (int j = 1; j <= N; j++)
		{
			if (map[i][j] != 0)
				ans--;
		}
		cout << ans << "\n";
	}
	return 0;
}