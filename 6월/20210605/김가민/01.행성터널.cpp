#include<vector>
#include<iostream>
#include<algorithm>
#include<cmath>
#include<stdio.h>

typedef long long ll;

using namespace std;

int unf[100001];
int n;


struct Planet
{
	int x;
	int y;
	int z;
	int num;

};
Planet pl[100001];
struct Edge
{
	int value;
	int start;
	int end;
	Edge(int v, int s, int e)
	{
		value = v;
		start = s;
		end = e;
	}
	bool operator<(const Edge& edge)const {
		return value < edge.value;
	}

};
vector<Edge> Ed;
bool compX(const Planet& p1, const Planet& p2)
{
	return p1.x < p2.x;
}
bool compY(const Planet& p1, const Planet& p2)
{
	return p1.y < p2.y;
}
bool compZ(const Planet& p1, const Planet& p2)
{
	return p1.z < p2.z;
}
int Find(int v)
{
	if (v == unf[v])
		return v;
	else
		return unf[v] = Find(unf[v]);
}

void Union(int s, int e)
{
	s = Find(s);
	e = Find(e);
	if (s != e)
		unf[s] = e;
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	//freopen("input.txt", "rt", stdin);


	int res = 0;
	cin >> n;
	for (int i = 1; i <= n; i++)
	{
		cin >> pl[i].x >> pl[i].y >> pl[i].z;
		pl[i].num = i;
		unf[i] = i;
	}

	sort(pl + 1, pl + n + 1, compX);
	for (int i = 1; i <= n - 1; i++)
	{
		Ed.push_back({abs(pl[i].x - pl[i + 1].x), pl[i].num, pl[i + 1].num });
	}
	sort(pl + 1, pl + n + 1, compY);
	for (int i = 1; i <= n - 1; i++)
	{
		Ed.push_back({ abs(pl[i].y - pl[i + 1].y), pl[i].num, pl[i + 1].num });
	}
	sort(pl + 1, pl + n + 1, compZ);

	for (int i = 1; i <= n - 1; i++)
	{
		Ed.push_back({ abs(pl[i].z - pl[i + 1].z), pl[i].num, pl[i + 1].num });
	}

	sort(Ed.begin(), Ed.end());

	for (int i = 0; i < Ed.size(); i++)
	{
		int fs = Find(Ed[i].start);
		int fe = Find(Ed[i].end);
		if (fs != fe)
		{
			res += Ed[i].value;
			Union(Ed[i].start, Ed[i].end);
		}
	}
	cout << res << "\n";

	return 0;
}