#include <vector>
#include <algorithm>
#include <cstring>
#include <iostream>

using namespace std;

/**
 * 웜홀의 위치 정보와 번호를 나타내기 위한 구조체
 * */
struct Wormhole {
    int y, x, data;
    Wormhole() { y = 0, x = 0, data = 0; }
    Wormhole(int y, int x, int data): y(y), x(x), data(data) {}
};

/**
 * ****** 전역 변수 ******
 * T           - 테스트 케이스 개수
 * N           - 핀볼 게임판의 크기 (N * N, 5 ≤ N ≤ 100)
 * ans         - 게임에서 얻을 수 있는 점수의 최댓값
 * map         - 게임판의 정보 (N * N)
 * wormMap     - 웜홀의 정보. 웜홀은 6 ~ 10 번이며 존재할 경우 반드시 쌍으로 주어지고, 최대 5쌍이 존재함.
 * dy, dx      - 북 동 남 서
 * transDir    - 각 블록을 만났을 때 전환되는 방향
 *               ex) 위로 향하는 핀볼(상 - 0번 방향)이 1번 블록을 만나면 아래(하 - 2번 방향)으로 전환된다.
 * */
int T, N, ans;
int map[101][101];
vector<Wormhole> wormMap;
int dx[] = { 0, 1, 0, -1 }; int dy[] = { -1, 0, 1, 0 };
int transDir[5][4] = { { 2, 3, 1, 0 },    // 1번 블록
                       { 1, 3, 0, 2 },    // 2번 블록
                       { 3, 2, 0, 1 },    // 3번 블록
                       { 2, 0, 3, 1 },    // 4번 블록
                       { 2, 3, 0, 1 } };  // 5번 블록


/**
 * ****** 함수 ******
 * start       - 게임을 시작하는 함수
 * outOfRange  - 공이 맵의 범위를 벗어났을 때 true 반환
 * pinballGame - 게임을 진행하는 함수
 * */
void start();
bool outOfRange(int, int);
int pinballGame(int, int, int);

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

    cin >> T;
    for (int t = 1; t <= T; t++) {
        cin >> N;

        // 초기화
        memset(map, 0, sizeof(map));
        wormMap.clear();
        ans = 0;

        // 맵, 웜홀 설정
        for (int y = 0; y < N; y++)
            for (int x = 0; x < N; x++) {
                cin >> map[y][x];  // 맵 저장
                if (6 <= map[y][x] && map[y][x] <= 10) {
                    Wormhole w = Wormhole(y, x, map[y][x]);
                    wormMap.push_back(w);  // 웜홀 저장
                }
            }

        // 게임 시작
        start();

        // 결과 출력
        cout << "#" << t << " " << ans << endl;
    }
    return 0;
}

/**
 * 맵의 빈공간에서 진행 방향과 출발 지점을 달리 하여 pinballGame 을 시작하고, 점수의 최댓값을 구한다.
 * */
void start() {
    for (int dir = 0; dir < 4; dir++)
        for (int y = 0; y < N; y++)
            for (int x = 0; x < N; x++)
                if (map[y][x] == 0) ans = max(ans, pinballGame(y, x, dir));
}

/**
 * 범위가 벗어나면 true 반환
 * */
bool outOfRange(int y, int x) {
    return y < 0 or x < 0 or y >= N or x >= N;
}


/**
 * 핀볼 게임 진행
 * */
int pinballGame(int y, int x, int d) {
    int ny, nx, score, curBlock;
    score = 0;
    ny = y, nx = x;

    do {
        ny += dy[d], nx += dx[d];  // 이동
        curBlock = map[ny][nx];

        // 벽에 부딪힌 경우, 점수를 증가하고 5번 블록을 만난 것 처럼 방향을 전환한다.
        if (outOfRange(ny, nx)) {
            score++;
            d = transDir[4][d];
        }
        // 블록에 부딪힌 경우, 점수를 증가하고 방향을 전환한다.
        else if (1 <= curBlock && curBlock <= 5) {
            score++;
            d = transDir[curBlock - 1][d];
        }
        // 웜홀을 만난 경우, 동일한 숫자를 가진 반대편 웜홀로 이동한다.
        else if (6 <= curBlock && curBlock <= 10) {
            for (auto& worm : wormMap) {
                if (worm.data == curBlock and (worm.y != ny or worm.x != nx)) {
                    ny = worm.y, nx = worm.x;
                    break;
                }
            }
        }
    } while (!((ny == y and nx == x) or curBlock == -1));  // 종료: 핀볼이 출발 위치로 돌아오거나, 블랙홀에 빠질 때

    return score;
}
