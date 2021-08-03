#include<iostream>
#include<queue>

using namespace std;
#define MAX 51

int N, L, R, arr[MAX][MAX];
bool visited[MAX][MAX];
int dx[] = {0, 0, 1, -1};
int dy[] = {1, -1, 0, 0};

queue<pair<int, int>> q;
vector<pair<int, int>> v;

bool flag = true; //연합여부
int sum = 0; //평균을 구하기 위한 변수

void bfs(pair<int, int> start) { //bfs
	q.push(start);
	visited[start.first][start.second] = true;

	while (!q.empty()) {
		pair<int, int> temp = q.front();
		q.pop();
		
		for (int i = 0; i < 4; i++) {
			int na = temp.first + dx[i];
			int nb = temp.second + dy[i];

            //범위 안에 있고 인구 차이가 L 이상, R 이하 여부 체킹
			if (na >= 0 && nb >= 0 && na < N && nb < N && !visited[na][nb]) {
                if (abs(arr[na][nb] - arr[temp.first][temp.second]) >= L &&
				    abs(arr[na][nb] - arr[temp.first][temp.second]) <= R) {
				        q.push({ na, nb });
				        visited[na][nb] = true;

				        v.push_back({ na, nb });
				        sum += arr[na][nb]; //평균을 구하기 위해
			    }
            }
		}
	}
}

void clear() { //방문 초기화
	for (int i = 0; i < N; i++) 
		for (int j = 0; j < N; j++) 
			visited[i][j] = false;
}

int main() {
    int days = 0; //결과 초기화

	cin >> N >> L >> R;

	for (int i = 0; i < N; i++) //값 입력받기
		for (int j = 0; j < N; j++)
			cin >> arr[i][j];

	while (flag) { //연합이 일어나면 계속 반복
		flag = false; //연합 여부 초기화
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				if (!visited[i][j]) { //방문을 안 했다면
					v.clear();
					v.push_back({ i,j }); 
					sum = arr[i][j];
					bfs({ i, j });
				}

                //연합 여부
				if (v.size() >= 2) {
					flag = true; //연합 체크
					for (int i = 0; i < v.size(); i++) {
						arr[v[i].first][v[i].second] = sum / v.size(); //평균 갱신
					}
				}
			}
		}
		if (flag) days++; //한바퀴

		clear(); //초기화
	}
	cout << days; //결과
}