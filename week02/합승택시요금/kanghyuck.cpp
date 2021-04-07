/* 합승 택시 요금, kang-hyuck */
#include <vector>
#include <iostream>
using namespace std;

#define INF 87654321  // int 최댓값 20억 -> n*INF이 20억 넘으면 안됨

int N,S,A,B;
int map[210][210];  // map[출발점][도착점] = (비용).  Floyd-Warshall에서 사용
vector<vector<int>> Fares;

void Init(void);
void Floyd_Warshall(void);

int solution(int n, int s, int a, int b, vector<vector<int>> fares) {
    int answer = INF;  // INF값으로 초기화

    // 초기화
    N=n; S=s; A=a; B=b; Fares=fares;  // 전역변수에 저장
    Init();  // map 초기화.

    // 실행부
    Floyd_Warshall();

    // 비용 계산
    answer = map[s][a] + map[s][b];  // 합승하지 않는 경우
    for(int i=1; i<=N; i++) answer = min(answer, map[s][i]+map[i][a]+map[i][b]);  // 합승하는 경우

    // 출력부
    return answer;
}


void Init(){
    // map을 INF로 모두 초기화
    for(int i=1; i<=N; i++) for(int j=1; j<=N; j++) map[i][j] = INF;

    // 연결된 edge 정보를 map에 반영
    for(int i=0; i<(int)Fares.size(); i++){
        map[Fares[i][0]][Fares[i][1]] = Fares[i][2];
        map[Fares[i][1]][Fares[i][0]] = Fares[i][2];
    }
}

void Floyd_Warshall(){
    // map값 계산
    for(int k=1; k<=N; k++) for(int i=1; i<=N; i++) for(int j=1; j<=N; j++)
        map[i][j] = min(map[i][j], map[i][k]+map[k][j]);

    // 자기 자신으로 가는 비용은 0
    for(int i=1,j=1; i<=N&&j<=N; i++,j++) map[i][j] = 0;
}
