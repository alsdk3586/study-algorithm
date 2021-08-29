#include<iostream>
#include<algorithm>
#include<queue>

using namespace std;
int f, s, g, u, d;
int ch[1000001];
queue<pair<int, int>> Q;
void BFS(int x)
{
	ch[x] = 1;
	Q.push(make_pair(x, 0));

	while (!Q.empty())
	{

		int val = Q.front().first;
		int dep = Q.front().second;
		Q.pop();
		//ch[temp] = 1;
		if (val == g)
		{
			cout << dep << "\n";
			return;
		}

		int up = val + u;
		int down = val - d;
		if (up <= f && ch[up]==0)
		{
			ch[up] = 1;
			Q.push(make_pair(up, dep + 1));
		}
		if (down > 0 && ch[down] == 0)
		{
			ch[down] = 1;
			Q.push(make_pair(down, dep + 1));
		}
	}
	cout << "use the stairs" << "\n";
}
int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	//freopen("input.txt", "rt", stdin);

	cin >> f >> s >> g >> u >> d;

	BFS(s);

	return 0;
}