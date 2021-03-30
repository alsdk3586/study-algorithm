#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;

typedef struct _bc {
	int x;
	int y;
	int c;
	int p;
}BC;
BC bcList[10];

int aPath[101]; // a의 경로를 저장
int bPath[101]; // b의 경로를 저장
int dx[] = { 0,0,1,0,-1 };
int dy[] = { 0,-1,0,1,0 };

int M, A;

// 접속한 BC들의 번호를 가져옴
vector<int> checkBC(int x, int y) {
	vector<int> bc;

	for (int i = 0; i < A; i++) {
		if (abs(x - bcList[i].x) + abs(y - bcList[i].y) <= bcList[i].c) { // 충전 범위안에 있다면
			bc.push_back(i); // 해당 BC의 번호를 넣음
		}
	}

	return bc;
}

int main(int argc, char** argv)
{
	int test_case;
	int T;

	cin >> T;

	for (test_case = 1; test_case <= T; ++test_case)
	{
		// 초기화
		pair<int, int> aPos = { 1,1 };
		pair<int, int> bPos = { 10,10 };
		int totalP = 0;

		cin >> M >> A;

		for (int i = 0; i < M; i++) {
			cin >> aPath[i];
		}
		for (int i = 0; i < M; i++) {
			cin >> bPath[i];
		}
		for (int i = 0; i < A; i++) {
			cin >> bcList[i].x >> bcList[i].y >> bcList[i].c >> bcList[i].p;
		}

		for (int i = -1; i < M; i++) {
			if (i >= 0) { // a와 b의 다음 위치를 구함(맨 처음엔 위치를 갱신x)
				aPos.first += dx[aPath[i]];
				aPos.second += dy[aPath[i]];
				bPos.first += dx[bPath[i]];
				bPos.second += dy[bPath[i]];
			}

			// 접속한 BC를 가져옴
			vector<int> aBC = checkBC(aPos.first, aPos.second);
			vector<int> bBC = checkBC(bPos.first, bPos.second);

			if (aBC.size() == 0 && bBC.size() == 0) { // 접속한 BC가 없다면 넘어감
				continue;
			}
			else if (aBC.size() == 0) { // a만 접속한 BC가 없다면
				int maxP = 0;
				for (int j = 0; j < bBC.size(); j++) { // b가 접속한 BC 중에 최대량을 충전
					maxP = max(maxP, bcList[bBC[j]].p);
				}
				totalP += maxP;
			}
			else if (bBC.size() == 0) { // b만 접속한 BC가 없다면
				int maxP = 0;
				for (int j = 0; j < aBC.size(); j++) { // a가 접속한 BC 중에 최대량을 충전
					maxP = max(maxP, bcList[aBC[j]].p);
				}
				totalP += maxP;
			}
			else { // 둘 다 접속한 BC가 있다면
				int maxP = 0;
				// a와 b가 접속한 BC 조합 중 
				for (int j = 0; j < aBC.size(); j++) {
					for (int k = 0; k < bBC.size(); k++) {
						int sumP;
						if (aBC[j] == bBC[k]) { // 같은 BC에 접속했다면
							sumP = bcList[aBC[j]].p; // 균등량을 분배하므로 전체 충전량은 해당 BC의 충전량
						}
						else { // 다른 BC에 각각 접속했다면
							sumP = bcList[aBC[j]].p + bcList[bBC[k]].p; // 전체 충전량은 각각의 충전량의 합산
						}
						maxP = max(maxP, sumP); // 가장 최대량을 얻는 조합을 고름
					}
				}
				totalP += maxP;
			}
		}

		cout << "#" << test_case << " " << totalP << endl;
	}
	return 0;
}