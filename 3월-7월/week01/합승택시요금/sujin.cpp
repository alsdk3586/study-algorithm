#include <cstring>
#include <vector>
#include <algorithm>
#define MAX_N 201
#define INF 987654321

using namespace std;

void initialize(int n, vector<vector<int> > & fares, vector<vector<int> > &adj) {
    // 양방향으로 택시 요금을 저장한다.
    for (auto& fare : fares) {
        adj[fare[0]][fare[1]] = fare[2];
        adj[fare[1]][fare[0]] = fare[2];
    }
    // 자기 자신까지의 요금은 0
    for (int i = 1; i <= n; i++) adj[i][i] = 0;
}

void floyd(int n, vector<vector<int> > &adj) {
    for (int k = 1; k <= n; k++) {
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                adj[i][j] = min(adj[i][j], adj[i][k] + adj[k][j]);
            }
        }
    }
}

int solution(int n, int s, int a, int b, vector<vector<int>> fares) {
    int answer;
    vector<vector<int> > adj(n + 1, vector<int>(n + 1, INF));  // adj[u][v] = u -> v 로 가는 최단 거리
    initialize(n, fares, adj);
    floyd(n, adj);

    answer = adj[s][a] + adj[s][b];

    // 간선 계산
    for (int k = 1; k <= n; k++) {
        if (adj[s][k] != INF && adj[k][a] != INF && adj[k][b] != INF)
            answer = min(answer, adj[s][k] + adj[k][a] + adj[k][b]);
    }
    return answer;
}