#include <iostream>
#include <cstring>
#include <cmath>

using namespace std;

typedef struct _atom {
	double x;
	double y;
	int d;
	int energy;
}Atom;
Atom atoms[1001]; // 원자들의 정보를 담은 배열
int map[4002][4002]; // 특정 위치의 원자 개수를 담은 배열
bool outed[1001]; // 원자가 소멸되었는지를 표시

// 원자 위치의 유효범위 검사
bool check(double x, double y) {
	if (abs(x) > 1000 || abs(y) > 1000) {
		return false;
	}
	return true;
}

int main(int argc, char** argv)
{
	int test_case;
	int T;
	int N;
	int totalEnergy;
	int outCnt; // 소멸된 원자 개수
	// 0.5초 후 원자의 위치를 조정하기 위한 배열
	double dx[] = { 0.0,0.0,-0.5,0.5 };
	double dy[] = { 0.5,-0.5,0.0,0.0 };

	cin >> T;

	for (test_case = 1; test_case <= T; ++test_case)
	{
		// 초기화
		totalEnergy = 0;
		outCnt = 0;
		memset(outed, false, sizeof(outed));
		cin >> N;

		for (int i = 0; i < N; i++) {
			cin >> atoms[i].x >> atoms[i].y >> atoms[i].d >> atoms[i].energy;
		}

		// 모든 원자가 범위밖으로 나가는 최대시간 = 대략 2001초
		// 0.5초 단위로 원자의 움직임을 수정하므로 최대 2001 x 2 = 4002번 수행
		for (int i = 0; i <= 4002; i++) {
			for (int j = 0; j < N; j++) {
				if (outed[j] == true) { // 소멸된 원자는 무시
					continue;
				}
				// 움직이는 방향에 따라 0.5초 후의 위치로 갱신
				atoms[j].x += dx[atoms[j].d];
				atoms[j].y += dy[atoms[j].d];

				// 원자의 위치가 유효범위 값 초과 -> 절대 다른 원자와 만날일이 없으므로 소멸되었다고 가정
				if (check(atoms[j].x, atoms[j].y) == false) {
					outed[j] = true;
					outCnt++;
					continue;
				}

				// 원자의 위치를 map상에 표시하기 위한 변환
				int mx = (atoms[j].x + 1000) * 2;
				int my = (atoms[j].y + 1000) * 2;
				map[mx][my]++; // (mx,my) 위치의 원자 개수를 늘림
			}

			for (int j = 0; j < N; j++) {
				int mx = (atoms[j].x + 1000) * 2;
				int my = (atoms[j].y + 1000) * 2;

				if (map[mx][my] >= 2) { // 같은 위치의 원자의 개수가 2개 이상 -> 충돌
					for (int k = 0; k < N; k++) {
						// 아직 소멸되지 않은 원자들에 대해 에너지를 더한 뒤 소멸 표시
						if (outed[k] == false && atoms[j].x == atoms[k].x && atoms[j].y == atoms[k].y) {
							totalEnergy += atoms[k].energy;
							outed[k] = true;
							outCnt++;
						}
					}
				}
				map[mx][my] = 0; // 특정 위치 검사 종료 후 다시 0으로 초기화
			}

			if (outCnt == N) { // 소멸된 원자 개수가 전체 원자 수와 같다면 종료
				break;
			}

		}

		cout << "#" << test_case << " " << totalEnergy << endl;
	}

	return 0;
}