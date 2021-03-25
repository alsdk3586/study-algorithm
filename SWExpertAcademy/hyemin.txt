#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <queue>
#include <map>
#include <sstream>
#include <cctype>
using namespace std;

typedef struct node {
	int i;
	int j;
};

int dx[] = { 1,0,-1,0 };
int dy[] = { 0,-1,0,1 };

int dir[][4] = { {0,0,0,0}, {3,2,0,1},{2,0,3,1},{2,3,1,0},{1,3,0,2},{2,3,0,1} };

vector<vector<node>> list;

int n = 0;
int search(int map[110][110], int si, int sj,int d) {
	int i = si;
	int j = sj;
	int cost = 0;

	while (1) {
		i += dx[d];
		j += dy[d];
		
		
		if (map[i][j] == -1) {
			return cost;
		}
		if (i == si && j == sj) {
			return cost;
		}
		
		if (i < 0 || i >= n || j < 0 || j >= n) {
			d = dir[5][d];
			cost++;
		}
		else if (map[i][j] >= 6 && map[i][j] <= 10) {
			if (list[map[i][j] - 6][0].i == i && list[map[i][j] - 6][0].j == j) {
				int box = map[i][j];
				i = list[box - 6][1].i;
				j = list[box - 6][1].j;
			}
			else if (list[map[i][j] - 6][1].i == i && list[map[i][j] - 6][1].j == j) {
				int box = map[i][j];
				i = list[box - 6][0].i;
				j = list[box - 6][0].j;
			}
		}
		else if (map[i][j] != 0) {
			cost++;
			d = dir[map[i][j]][d];
		}

	}
}


int main(void) {

	int tc = 0;
	cin >> tc;
	for (int q = 0; q < tc; q++) {
		
		int map[110][110] = { 0 };
		list.clear();
		
		for (int i = 0; i < 5; i++) {
			vector<node> a;
			list.push_back(a);
		}

		cin >> n;

		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				cin >> map[i][j];
				if (map[i][j] >= 6 && map[i][j] <= 10) {
					list[map[i][j] - 6].push_back({ i,j });
				}
			}
		}

		int max = 0;
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				for (int k = 0; k < 4; k++) {
					if (map[i][j] == 0) {
							int cost = search(map, i, j, k);
						if (cost > max)
							max = cost;
					}
				}
			}
		
		}
		cout << "#" << q + 1 << " " << max << endl;

	}


	return 0;
}