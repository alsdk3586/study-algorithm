#include<vector>
#include<iostream>
#include<algorithm>
#include<cmath>
#include<cstdio>


using namespace std;

int unf[200001];

struct City
{
	int x;
	int y;
	int z;
	int num;
	bool operator<(const City& edge)const {
		return z < edge.z;
	}

};

City city[200001];
bool compValue(const City& val1, const City& val2)
{
	return val1.z < val2.z;
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

	while (1)
	{	
		city[200001] = { 0, };
		int cost = 0;
		int n, m, total = 0;
		cin >> n >> m;

		if (n == 0 && m == 0)
			break;
		for (int i = 0; i < n; i++)
		{
			unf[i] = i;
		}
		for (int i = 0; i < m; i++)
		{
			cin >> city[i].x >> city[i].y >> city[i].z;
			total += city[i].z;
			city[i].num = i;
		}
		sort(city, city + m, compValue);
		for (int i = 0; i < m; i++)
		{
			int fs = Find(city[i].x);
			int fe = Find(city[i].y);
			if (fs != fe)
			{
				cost += city[i].z;
				Union(city[i].x, city[i].y);
			}
		}		

		cout << total - cost << "\n";
	}
	return 0;
}