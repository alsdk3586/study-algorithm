#include <string>
#include <vector>
#include <queue>

using namespace std;

struct pos {
    int y[2], x[2], dir[2];
};

int n;  // board 의 크기
// 오른쪽부터 시계방향
int dy[] = { 0, 1, 0, -1 };
int dx[] = { 1, 0, -1, 0 };
bool chk[101][101][4];

bool impossible(int y1, int x1, int y2, int x2, vector<vector<int>> &board) {
    return y1 < 0 or x1 < 0 or y2 < 0 or x2 < 0 or y1 >= n or x1 >= n or y2 >= n or x2 >= n or board[y1][x1] or board[y2][x2];
}

int solution(vector<vector<int>> board) {
    int answer = 0;
    n = board.size();
    queue<pos> q;

    // (0, 0), (0, 1) 에서 출발
    chk[0][0][0] = chk[0][1][2] = true;
    q.push({ 0, 0, 0, 1, 0, 2});

    while (!q.empty()) {
        int s = q.size();
        while (s--) {
            pos cur = q.front();
            q.pop();

            // 목적지에 도달
            if ((cur.y[0] == n - 1 and cur.x[0] == n - 1) or (cur.y[1] == n - 1 and cur.x[1] == n - 1)) return answer;

            // 오른쪽에서 시계방향으로 이동
            for (int dir = 0; dir < 4; dir++) {
                int ny1 = cur.y[0] + dy[dir], nx1 = cur.x[0] + dx[dir];
                int ny2 = cur.y[1] + dy[dir], nx2 = cur.x[1] + dx[dir];
                int dir1 = cur.dir[0], dir2 = cur.dir[1];

                // 진행 불가능한 경우
                if (impossible(ny1, nx1, ny2, nx2, board) or chk[ny1][nx1][dir1] or chk[ny2][nx2][dir2]) continue;
                // 진행 가능한 경우
                chk[ny1][nx1][dir1] = chk[ny2][nx2][dir2] = true;
                q.push({ny1, ny2, nx1, nx2, dir1, dir2});
            }

            // 회전
            int rotate[] = { -1, 1 };
            for (auto& r : rotate) {
                for (int i = 0; i < 2; i++) {
                    int y = cur.y[i], x = cur.x[i];

                    int dir = (cur.dir[i] + r + 4) % 4;
                    int prev_dir = (dir - r + 4) % 4;
                    int oppo_dir = (dir + 2) % 4;

                    int ny1 = y + dy[dir], nx1 = x + dx[dir];
                    int ny2 = y + dy[dir] + dy[prev_dir], nx2 = x + dx[dir] + dx[prev_dir];

                    // 진행 불가능한 경우
                    if (impossible(ny1, nx1, ny2, nx2, board) or chk[y][x][dir] or chk[ny1][nx1][oppo_dir]) continue;
                    // 진행 가능한 경우
                    chk[y][x][dir] = chk[ny1][nx1][oppo_dir] = true;
                    q.push({y, ny1, x, nx1, dir, oppo_dir});
                }
            }
        }
        answer++;
    }


    return answer;
}