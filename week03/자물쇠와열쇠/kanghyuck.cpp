/* 자물쇠와 열쇠, kang-hyuck */
#include <string>
#include <vector>
#include <iostream>
using namespace std;

// 전역 변수
bool answer;
int StartIndex, EndIndex;
vector<vector<int>> Lock,Key;
vector<vector<int>> PaddingLock(300, vector<int>(300,0));  // PaddingLock[300][300] = {0, };

// 함수 선언
void DFS(int, vector<vector<int>>);
vector<vector<int>> Rotate(vector<vector<int>>);
int CheckMatch(vector<vector<int>>);
int Try(int, int, vector<vector<int>>);


bool solution(vector<vector<int>> key, vector<vector<int>> lock){

    // 초기화
    answer = false;  Key=key;  Lock=lock;
    for(int i=0; i<(int)Lock.size(); i++)
        for(int j=0; j<(int)Lock.size(); j++)
            PaddingLock[100+i][100+j] = Lock[i][j];  // PaddingLock은 100,100 인덱스부터. Lock은 0,0 인덱스부터.
    StartIndex = 100 - Key.size() + 1;
    EndIndex = 100 + Key.size() + Lock.size() - 2;

    // 실행부
    DFS(0, key);

    // 출력부
    return answer;
}

void DFS(int cnt, vector<vector<int>> originalMap)
{
    vector<vector<int>> rotateMap;

    // 종료조건
    if(cnt>3) return;  // 3번 초과해서 회전 했으면 종료
    if( 1 == CheckMatch(originalMap) ){answer=true; return;}

    // 실행부
    rotateMap = Rotate(originalMap);

    // 자식 노드 호출 ('시계 방향으로만 회전' 하는 경우만 있음 -> DFS 1번만 호출.)
    DFS(cnt+1, rotateMap);

    return;
}

vector<vector<int>> Rotate(vector<vector<int>> map)
{
    // 초기화
    int i,j, N=(int)map.size();  vector<vector<int>> ret;
    ret = map;  // map크기 만큼 ret크기 잡기 위해서.

    // 실행부 (회전)
    for(i=0; i<N; i++) for(j=0; j<N; j++)  ret[j][N-1-i] = map[i][j];  // (-1은 크기 -> 인덱스)

    // 종료부
    return ret;
}

int CheckMatch(vector<vector<int>> key)
{
    // 실행부 (key에서 1인 부분만 tempLock 위에 그린다)
    for(int i=StartIndex; i<=EndIndex; i++)
        for(int j=StartIndex; j<=EndIndex; j++)
            if( 1 == Try(i,j, key) ) return 1;

    // 종료부
    return -1;  // 못여는 경우
}

int Try(int yy, int xx, vector<vector<int>> key)
{
    int i,j, M=(int)Key.size(), N=(int)Lock.size();
    vector<vector<int>> tempLock = PaddingLock;

    // 자물 쇠 위에 key 그리기
    for(i=0; i<M; i++)
        for(j=0; j<M; j++)
            tempLock[yy+i][xx+j] = tempLock[yy+i][xx+j] ^ key[i][j]; // 자물쇠부분이 1인데, Key도 1이면 key 못꽂음

    // 열수 있는지 확인  (100,100 인덱스부터 Lock 크기만큼 0이 다 덮여졌는지 확인)
    for(i=0; i<N; i++)
        for(j=0; j<N; j++)
            if(0 == tempLock[100+i][100+j]) return -1;

    // 종료부
    return 1;  // 맞는 경우
}
