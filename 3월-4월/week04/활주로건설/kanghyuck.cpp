/* 활주로 건설, kang-hyuck */
#include <iostream>
#include <string.h>  // memset()
using namespace std;

// 전역변수
int constructed[25][25][2];  // 0:row, 1:col
int map[25][25];
int T, N, X, ans;

// 함수선언
void Start(void);
int Check(int, int, int, int, int);  // (시작좌표, 끝좌표)
bool CannotPrev(int, int, int);
bool CannotNext(int, int, int);
bool OutOfRange(int, int);

int main()
{
	int i,j,t;

	cin >> T;

	// 테스트 횟수 만큼 실행
	for (t = 1; t <= T; t++)
	{
		// 입력부
		cin >> N >> X;
		for (i = 1; i <= N; i++) for (j = 1; j <= N; j++) cin >> map[i][j];

		// 실행부
		Start();

		// 출력부
		cout << "#" << t << " " << ans << endl;

		// 초기화
		ans = 0;    memset(constructed, 0, sizeof(constructed));
	}

	return 0;
}


void Start()
{
	int i;

	for (i = 1; i <= N; i++) ans += Check(i,1, i,N, 1); // 1행씩 확인
	for (i = 1; i <= N; i++) ans += Check(1,i, N,i, 0); // 1열씩 확인
}

int Check(int yStart, int xStart, int yEnd, int xEnd,  int rowcol)
{
	int i, j, prevVal;

	// 열|행을 끝까지 탐색
	prevVal = map[yStart][xStart];  // 시작 위치 값 저장
	for (i = yStart; i <= yEnd; i++) for (j = xStart; j <= xEnd; j++)
	{
		// 이전 값과 다른 경우 (건설 가능성 확인)
		if (prevVal < map[i][j] && (map[i][j] - prevVal > 1) ) return 0;  // 높이 차이가 1 보다 큰 경우
		if (prevVal > map[i][j] && (prevVal - map[i][j] > 1) ) return 0;  // 높이 차이가 1 보다 큰 경우
		if (prevVal < map[i][j] && (map[i][j]-prevVal==1) && CannotPrev(i, j, rowcol)) return 0;  // 이전 위치에 경사로 건설할 수 없는 경우
		if (prevVal > map[i][j] && (prevVal-map[i][j]==1) && CannotNext(i, j, rowcol)) return 0;  // 다음 위치에 겅사로 건설할 수 없는 경우

		// 현재 위치 값 저장
		prevVal = map[i][j];
	}

	// 활주로 건설 가능한 열|행인 경우
	return 1;
}

bool CannotPrev(int y, int x, int rowcol)
{
	int i, val;

	// 탐색방향 - 행방향
	if (rowcol == 0)
	{
		// 범위를 벗어나는 경우
		if(OutOfRange(y - X, x)) return true;

		// 평평한지 확인
		val = map[y - 1][x];
		for (i = y - X; i <= y - 1; i++)
		{
			if (map[i][x] != val) return true;  // 평평하지 않는 경우
			if (constructed[i][x][rowcol] == 1) return true;  // 이미 경사로가 건설 되어 있는 경우
			constructed[i][x][rowcol] = 1;  // 건설 되었음 표시 (사용중 표시)
		}
	}

	// 탐색방향 - 열방향
	if (rowcol == 1)
	{
		// 범위를 벗어나는 경우
		if (OutOfRange(y, x - X)) return true;

		// 평평하지 않는 경우
		val = map[y][x - 1];
		for (i = x - X; i <= x - 1; i++)
		{
			if (map[y][i] != val) return true;  // 평평하지 않는 경우
			if (constructed[y][i][rowcol] == 1) return true;  // 이미 경사로가 건설 되어 있는 경우
			constructed[y][i][rowcol] = 1;  // 건설 되었음 표시 (사용중 표시)
		}
	}

	// 이전 위치에 건설할 수 있는 경우
	return false;
}

bool CannotNext(int y, int x, int rowcol)
{
	int i, val;

	// 탐색방향 - 행방향
	if (rowcol == 0)
	{
		// 범위를 벗어나는 경우
		if (OutOfRange(y + X -1, x)) return true;

		// 평평한지 확인
		val = map[y][x];
		for (i = y; i <= y+X-1; i++)
		{
			if (map[i][x] != val) return true;  // 평평하지 않는 경우
			if (constructed[i][x][rowcol] == 1) return true;  // 이미 경사로가 건설 되어 있는 경우
			constructed[i][x][rowcol] = 1;  // 건설 되었음 표시 (사용중 표시)
		}
	}

	// 탐색방향 - 열방향
	if (rowcol == 1)
	{
		// 범위를 벗어나는 경우
		if (OutOfRange(y, x + X - 1)) return true;

		// 평평하지 않는 경우
		val = map[y][x];
		for (i = x; i <= x+X-1; i++)
		{
			if (map[y][i] != val) return true;  // 평평하지 않는 경우
			if (constructed[y][i][rowcol] == 1) return true;  // 이미 경사로가 건설 되어 있는 경우
			constructed[y][i][rowcol] = 1;  // 건설 되었음 표시 (사용중 표시)
		}
	}

	// 이전 위치에 건설할 수 있는 경우
	return false;
}
bool OutOfRange(int y, int x) {
	if (y<1 || x<1 || y>N || x>N) return true;  // 맵 범위를 벗어나는 경우
	return false;  // 맵 범위를 벗어나지 않는 경우
}
