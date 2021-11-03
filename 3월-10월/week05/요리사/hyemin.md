```c++
#include <iostream>
#include <vector>
#include <queue>
#include <map>
using namespace std;


vector<vector<int>> list;
int answer = 10000;
void cal(vector<int> a, vector<int>b, int map[][20]) {
	int at = 0;
	for(int i=0;i<a.size();i++){
		for (int j = 0; j < a.size(); j++) {
			at += map[a[i]][a[j]];
		}
	}
	int bt = 0;
	for (int i = 0; i < b.size(); i++) {
		for (int j = 0; j < b.size(); j++) {
			bt += map[b[i]][b[j]];
		}
	}
	int v = at - bt;
	if (v < 0)
		v = -v;
	if (v < answer)
		answer = v;
}
void pick(int n, int i, vector<int> a, vector<int> b, int map[][20]) {

	if (a.size() == n / 2 && b.size() == n / 2) {
		cal(a, b,map);
		return;
	}
	if (a.size() == n / 2+1 || b.size() == n / 2+1)
		return;
	
	a.push_back(i);
	pick(n, i + 1, a, b,map);
	a.pop_back();
	b.push_back(i);
	pick(n, i + 1, a, b,map);
}

int main() {
	
	freopen("inp.inp", "r", stdin);
	freopen("out.out", "w", stdout);


	int tc = 0;
	cin >> tc;
	for (int p = 1; p <= tc; p++) {
		int N = 0;
		answer = 10000;
		cin >> N;
		int map[20][20] = { 0 };
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				cin >> map[i][j];
			}
		}
		vector<int> l;
		vector<int> ll;
		pick(N, 0, l,ll,map);
	
		cout << answer<<endl;
	}

	return 0;
}
```

