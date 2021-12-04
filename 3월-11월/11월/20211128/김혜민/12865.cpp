#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;	

struct node {
	int weight;
	int price;
	double value;
};

int main() {

	freopen("inp.inp", "r", stdin);
	freopen("out.out", "w", stdout);

	int cnt, pg;
	int answer = 0;
	cin >> cnt >> pg;

	vector<node> list;
	list.push_back({ 0,0,0 });
	for (int i = 0; i < cnt; i++) {
		int a, b;
		cin >> a >> b;
		list.push_back({ a,b,(double)b / a });
	}

	int map[110][100010] = { 0 };

	for (int i = 1; i < cnt+1 ; i++) {
		for (int j = 1; j < pg + 1; j++) {
			if (list[i].weight > j)
				map[i][j] = map[i - 1][j];
			else
				map[i][j] = max(list[i].price + map[i - 1][j - list[i].weight], map[i - 1][j]);
			if (answer < map[i][j])
				answer = map[i][j];
		}
	}

	cout << answer;
	return 0;
}