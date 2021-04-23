#include <vector>
#include <queue>
#include <limits.h>
#include <cstdio>

using namespace std;

vector<pair<int, int>> adj[201]; // adj[i][j] -> i에서 j까지 비용

// num위치를 기준으로 각 지점들 사이의 최단거리 배열 vector<int> dist를 반환
vector<int> dijkstra(int num, int V) {
	vector<int> dist(V + 1, INT_MAX); // dist[i] -> x지점에서 i지점 사이의 최소비용
	priority_queue<pair<int, int> > pq;

	dist[num] = 0;
	pq.push(make_pair(0, num));

	// 우선순위 큐 -> 다익스트라
	while (!pq.empty()) {
		int cost = -pq.top().first; 
		int near = pq.top().second;

		pq.pop();

		if (dist[near] < cost)
			continue;

		for (int i = 0; i < adj[near].size(); i++) {
			int nextNum = adj[near][i].first;
			int nextDist = cost + adj[near][i].second;

			if (dist[nextNum] > nextDist) {
				dist[nextNum] = nextDist;
				pq.push(make_pair(-nextDist, nextNum)); // 비용을 기준으로 오름차순 정렬을 위해 -를 붙임
			}
		}
	}

	return dist;
}

int solution(int n, int s, int a, int b, vector<vector<int>> fares) {
	int answer = 0;

	for (int i = 0; i < fares.size(); i++) {
		int a = fares[i][0];
		int b = fares[i][1];
		int w = fares[i][2];

		adj[a].push_back(make_pair(b, w));
		adj[b].push_back(make_pair(a, w));
	}

	vector<int> distS = dijkstra(s, n); // 출발지점 s에서 각 지점 사이의 최단 거리
	vector<int> distA = dijkstra(a, n); // 도착지점 a에서 각 지점 사이의 최단 거리
	vector<int> distB = dijkstra(b, n); // 도착지점 b에서 각 지점 사이의 최단 거리

	answer = INT_MAX;
	for (int i = 1; i <= n; i++) { // 모든 노드를 기준으로
		if (answer > distS[i] + distA[i] + distB[i]) { // (s지점 -> i지점 -> a,b지점 비용합)의 최소값
			answer = distS[i] + distA[i] + distB[i];  
		}
	}

	return answer;
}