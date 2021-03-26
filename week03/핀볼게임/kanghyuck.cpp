/* 핀볼 게임, kang-hyuck */
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

typedef struct Node {
	int y, x, dir;
}Node;

// 전역 변수
int T, N,  ans, score;
int map[110][110];
int dx[4] = { 1, 0, -1, 0 };  int dy[4] = { 0, 1, 0, -1 };   // 이렇게 구성하면 dir=(dir+2)%4 로 반대반향 구현 가능
Node start;
vector<Node> whole[15];  // 웜홀 저장용도, [웜홀번호]

// 함수 선언
void Start(void);
void Simulation(int,int, int);    // (y,x,방향), 점수값 반환
bool OutOfRange(int, int);
Node MoveWall(Node);
Node MoveWhole(Node);
bool Finish(Node);

int main()
{
	ios_base::sync_with_stdio(0);  cin.tie(0);  cout.tie(0);
	int i, j, t;

	cin >> T;
	for(t=1; t<=T; t++)
	{
		// 입력부
		cin >> N;
		for (i = 0; i < N; i++)
			for (j = 0; j < N; j++){
				cin >> map[i][j];  // 맵 입력
				if (map[i][j] >= 6) whole[map[i][j]].push_back({i,j, 0});  // 웜홀일 경우. 해당 번호에 위치하는 벡터에 위치 저장
			}

		// 실행부
		Start();

		// 출력부
		cout<<"#"<<t<<" "<<ans<<endl;

		// 초기화
		ans = 0;   for (i = 0; i < 15; i++) whole[i].clear();  // 정답, 웜홀 비워줌
	}

	return 0;
}


void Start(void)
{
	int i, j, dir;

	// 모든 위치에서, 4방향으로 시뮬레이션 확인 (맵에서 0인 곳만 확인)
	for (i = 0; i < N; i++)
		for (j = 0; j < N; j++)
			for (dir = 0; dir < 4; dir++)
				if (map[i][j] == 0){
					start.y=i;  start.x=j;
					Simulation(i, j, dir);
					ans = max(ans, score);
				}
}

void Simulation(int y, int x, int dir)
{
	// 초기화
	score = 0;  // 시작전, 점수 초기화

	// 실행부
	while (1)
	{
		// 이동
		y = y + dy[dir];  x = x + dx[dir];

		// 벽을 만난 경우 (점수 증가하는 경우)
		while (OutOfRange(y,x) || (map[y][x]>0 && map[y][x]<6))   // 맵을 벗어나거나 || 또 다른 벽을 만날 경우 (웜홀 제외)
		{
			// 점수 증가
			score++;  // 벽을 부딪힐 때 마다 1 증가

			// 벽에 따른 이동
			Node node = MoveWall({ y,x, dir });
			y=node.y;  x=node.x;  dir=node.dir;

			// 종료 조건 확인
			if (OutOfRange(y, x)==false && Finish({y, x, dir})) return;  // 맵 안벗어나고 && 종료조건일 경우
		}

		// 웜홀 만난 경우 (점수 증가하지 않는 경우)
		if (map[y][x] >= 6) {
			Node node = MoveWhole({ y,x, dir });
			y=node.y;  x=node.x;  dir=node.dir;
		}

		// 종료 조건 확인
		if (Finish({ y, x, dir })) return;
	}
}

Node MoveWall(Node node)
{
	int y, x, dir;
	y=node.y;  x=node.x;  dir=node.dir;

	// 1.맵을 벗어나는 경우
	if (OutOfRange(y,x)){
		y = y - dy[dir];  x = x - dx[dir];  dir = (dir + 2) % 4;
		return { y,x,dir };   // 구조체 이런식으로 반환 가능하다!?
	}

	// 2.맵을 벗어나지 않는 경우
	// 2-1 웜홀인 경우
	if (map[y][x] >= 6) {
		return { y,x,dir };  // 여기서 웜홀 안탈 것임. 위치 그대로 종료한다.
	}
	// 2-2 블록인 경우 (모양에 따른 방향 전환)
	if      (map[y][x] == 1 && (dir == 2 || dir == 1)) { dir = (dir == 2) ? 3 : 0;  y = y + dy[dir];  x = x + dx[dir];}
	else if (map[y][x] == 2 && (dir == 2 || dir == 3)) { dir = (dir == 2) ? 1 : 0;  y = y + dy[dir];  x = x + dx[dir]; }
	else if (map[y][x] == 3 && (dir == 0 || dir == 3)) { dir = (dir == 0) ? 1 : 2;  y = y + dy[dir];  x = x + dx[dir]; }
	else if (map[y][x] == 4 && (dir == 0 || dir == 1)) { dir = (dir == 0) ? 3 : 2;  y = y + dy[dir];  x = x + dx[dir]; }
	//     반대 방향전환
	else    { y = y - dy[dir];  x = x - dx[dir];  dir = (dir + 2) % 4; }

	return { y,x,dir };
}

Node MoveWhole(Node node) {
	int y, x, dir;
	y=node.y;  x=node.x;  dir=node.dir;

	for (auto a : whole[map[y][x]]) if (a.y != y || a.x != x) { y = a.y; x = a.x; break; }  // (같은번호,다른위치 웜홀) 찾아서 y,x,에 넣는다,  break으로 빠져나와야함 ㅠ.ㅠ 여기서 디버깅함
	return { y,x,dir };  // 방향은 그대로 유지.
}

bool OutOfRange(int y, int x){
	if (y < 0 || x < 0 || y >= N || x >= N) return true;  //  범위 벗어나는 경우
	return false; // 범위 안에 있는 경우
}

bool Finish(Node node){
	int y, x, dir;
	y=node.y;  x=node.x;  dir=node.dir;

	// 종료 조건인 경우
	if (y == start.y && x == start.x) return true;  // 시작 위치 같은 경우
	if (map[y][x] == -1) return true;  // 블랙홀 만난 경우

	// 종료 조건 아닌 경우
	return false;
}
