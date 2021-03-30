/* 무선 충전, kang-hyuck */
#include <iostream>
#include <vector>
#include <algorithm>  // max()
using namespace std;

typedef struct BCInfo{
	int y,x, c,p;
}BCInfo;

// 전역변수
BCInfo BC[10];
int dx[5] = { 0, 0, 1, 0, -1 };  int dy[5] = { 0,-1, 0, 1,  0 };
int path[110][2];  // 0:A, 1:B
int T, M,A, ans;

// 함수선언
void Start(void);
int Charge(int,int, int,int);
vector<int> FindBC(int, int);


int main()
{
	ios_base::sync_with_stdio(0);  cin.tie(0);  cout.tie(0);
	int i,j, t;

	cin >> T;

	// 테스트 횟수 만큼 실행
	for (t = 1; t <= T; t++)
	{
		// 입력부
		cin >> M >> A; // 이동 시간(M), BC 갯수(A)
		for (i = 0; i < 2; i++) for (j = 1; j <=M; j++) cin >> path[j][i];  // A,B 경로 저장
		for (i = 1; i<= A; i++) cin >> BC[i].x >> BC[i].y >> BC[i].c >> BC[i].p;  // BC 정보 저장

		// 실행부
		Start();

		// 출력부
		cout << "#" << t << " " << ans << endl;

		// 초기화
		ans = 0;
	}

	return 0;
}


void Start()
{
	int i, Ay, Ax, By, Bx, a, b;

	// 초기화
	Ay = 1; Ax = 1;  By = 10; Bx = 10;  // 처음 위치

	// 실행부
	for (i = 0; i <= M; i++)
	{
		// 위치 이동
		a = path[i][0];   b = path[i][1];
		Ay = Ay + dy[a];  Ax = Ax + dx[a];
		By = By + dy[b];  Bx = Bx + dx[b];

		// 충전
		ans += Charge(Ay, Ax, By, Bx);
	}
}

int Charge(int Ay, int Ax, int By, int Bx)
{
	int i, j, ret=0;
	vector<int> aBC, bBC;

	// A,B 가능한 비콘번호 저장
	aBC = FindBC(Ay, Ax);  bBC = FindBC(By, Bx);

	// 최대 충전 가능한 값 찾기 (A,B 서로 BC 충전값 비교)
	for (i = 0; i < (int)aBC.size(); i++) for (j = 0; j < (int)bBC.size(); j++)
		if (aBC[i] == bBC[j]) ret = max(ret, BC[aBC[i]].p);  // A,B 비콘이 같은 경우
		else   ret = max(ret, BC[aBC[i]].p + BC[bBC[j]].p);  // A,B 비콘이 다른 경우

	// 종료부
	return ret;  // 최대 충전 가능한 값 반환
}

vector<int> FindBC(int y, int x)
{
	int i;
	vector<int> ret;

	// BC 갯수만큼 확인
	for (i = 1; i <= A; i++) if (abs(y - BC[i].y) + abs(x - BC[i].x) <= BC[i].c) ret.push_back(i);  // 충전 범위 내에 위치한 경우, BC 번호 넣는다

	// 종료부
	if ((int)ret.size() == 0) { ret.push_back(0); return ret; }  // BC 범위 내에 위치하지 않은 경우. 0번 넣는다 (P값 0)
	return ret;  // (y,x,가) BC 범위 내에 위치한 경우. BC 번호 담긴 벡터 반환.
}
