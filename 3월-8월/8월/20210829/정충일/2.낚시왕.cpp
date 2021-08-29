//https://jooyoung1121.github.io/boj/%EB%82%9A%EC%8B%9C%EC%99%95/

#include <iostream>
#include <vector>
#include <queue>
#include <deque>
#include <algorithm>
#include <set>
using namespace std;

int R, C, M, Answer = 0;
struct info {
	int s, d, z; // s 속력, d 이동방향, z 크기
};

struct pos {
	int x, y;
};
// 속력 : 0 up 1 down 2 right 3 left

bool com(info a,info b) {
	return a.z > b.z;
}

int dx[4] = {-1,1,0,0};
int dy[4] = {0,0,1,-1};

vector<pos> Shark_Pos;
deque<info> Shark[101][101];

void solve() {

	for (int i = 1; i <= C; i++) { // 사람 위치

		for (int j = 1; j <= R; j++) {
			if (Shark[j][i].size() > 0) {
				Answer += Shark[j][i].front().z;
				Shark[j][i].pop_front();

				vector<pos>::iterator iter;
				for (iter = Shark_Pos.begin(); iter != Shark_Pos.end(); iter++) {
					if (iter->x == j && iter->y == i)
					{
						Shark_Pos.erase(iter);
						break;
					}
				}
				break;
			}
		}

		// 상어 이동
		set<pair<int, int>> Temp;

		for(int j=0;j<Shark_Pos.size();j++){
			int x = Shark_Pos[j].x;
			int y = Shark_Pos[j].y;
			int dir = Shark[x][y].front().d;
			int Speed = Shark[x][y].front().s;
			int tmp_speed = Speed;
			int Shark_Size = Shark[x][y].front().z;
			Shark[x][y].pop_front();
			if (dir == 0 || dir == 1) {
				if ((R - 1) * 2 <= Speed) Speed = Speed % ((R - 1) * 2);
			}
			else {
				if ((C - 1) * 2 <= Speed) Speed = Speed % ((C - 1) * 2);
			}

			for (int s = 1; s <= Speed; s++) {
				int nx = x + dx[dir];
				int ny = y + dy[dir];
				if (nx <= 0 || nx > R || ny <= 0 || ny > C) {
					if (dir == 0) dir = 1;
					else if (dir == 1)dir = 0;
					else if (dir == 2)dir = 3;
					else if (dir == 3) dir = 2;
					nx = x + dx[dir];
					ny = y + dy[dir];
				}
				x = nx;
				y = ny;
			}
			Shark[x][y].push_back({ tmp_speed,dir,Shark_Size });
			
			pos tmp;
			tmp.x = x;
			tmp.y = y;
			Shark_Pos[j] = tmp;
			Temp.insert({ x,y });
		}

		
		Shark_Pos.clear();

		set<pair<int, int>>::iterator iter2;

		for (iter2 = Temp.begin(); iter2 != Temp.end(); iter2++) {
			Shark_Pos.push_back({ iter2->first,iter2->second });
		}
		// 상어 잡아먹기


		for (int j = 0; j < Shark_Pos.size();j++) {
			int x = Shark_Pos[j].x;
			int y = Shark_Pos[j].y;

			sort(Shark[x][y].begin(), Shark[x][y].end(), com);

			int Size = Shark[x][y].size();

			for (int m = 1; m < Size; m++) {
				Shark[x][y].pop_back();
			}
		}
	}


}

int main() {
	cin >> R >> C >> M;

	int r, c, s, d, z;


	for (int i = 0; i < M; i++) {
		cin >> r >> c >> s >> d >> z;
		Shark[r][c].push_back({ s,--d,z });
		Shark_Pos.push_back({ r,c });
	}

	solve();

	cout << Answer;

	system("pause");
	return 0;
}