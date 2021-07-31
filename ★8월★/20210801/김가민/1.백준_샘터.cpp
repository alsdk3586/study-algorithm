#include <algorithm>
#include <iostream>
#include <queue>
#include <cstring>
#include <unordered_set>
//불행도의 합이 최소가 되려면 샘터를 기준으로 집이 1, -1씩 떨어져 있는 경우 최소가 된다
//최단거리를 구해야 하므로 BFS알고리즘을 사용한다.
using namespace std;
typedef long long ll;
int N, K;
queue<int> Q;
unordered_set<int> S;	//집 위치, 정렬과는 상관없고 unordered set이 속도가 더 빠르므로 unordered set 사용
int dirHouse[2] = { 1, -1 };
//**type 주의
ll BFS()
{
	ll ans = 0, dis = 1;
    
		while (!Q.empty())
		{
			int size = Q.size();
			//큐의 size만큼 돌린후 dis를 하나씩 증가시켜야하므로 while문 한번 돌려야 함
			while (size--)
			{

				int housePos = Q.front();
				Q.pop();

				for (int i = 0; i < 2; i++)
				{
					int hPos = housePos + dirHouse[i];
					//한좌표에는 하나의 집만 있을 수 있으므로 해당 좌표에 집이 없는 경우에 집을 세운다.
					if (!(S.count(hPos) >= 1))
					{
						K--;
						//answer에 거리만큼 더해준다.
						ans += dis;
						S.insert(hPos);
						Q.push(hPos);
						//K만큼의 집이 세워졌으면 answer를 리턴한다.
						if (K == 0)
							return ans;
					}
				}
			}
		dis++;
	}
	return ans;
}
int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	int a;
	cin >> N >> K;
	for (int i = 0; i < N; i++)
	{
		cin >> a;
		Q.push(a);
		S.insert(a);
	}
	cout << BFS() << "\n";
	return 0;
}