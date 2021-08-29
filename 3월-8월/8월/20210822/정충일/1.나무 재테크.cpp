#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
#define MAX 11

int N, M, K;
int A[MAX][MAX]; //현재 양분
int A_plus[MAX][MAX]; //매년 겨울에 줄 양분
vector<int> arr[MAX][MAX]; 
int dead[MAX][MAX]; //죽은 나무
int dx[] = {0,0,1,-1,1,-1,1,-1};
int dy[] = {1,-1,0,0,1,-1,-1,1};

/*
N*N 땅 크기
M개의 나무 나이 정보
K년 이후
A[r][c] 각 칸에 추가되는 양분

봄
나무가 자신의 나이만큼 양분을 먹고, 나이 1증가 (어린 나이 순서)
양분 못먹으면 사망

여름
사망한 나무 -> 양분으로 변환 (나이/2 -> 양분)

가을
나이가 5의 배수면 인접한 8개 칸에 나이 1인 나무 생성

겨울
양분 추가 ->각 칸에 추가되는 양분의 양은 A[r][c]
*/

void spring() {
    for(int i=1;i<=N;i++) {
        for(int j=1;j<=N;j++) {
            if(!arr[i][j].empty()) {
                sort(arr[i][j].begin(),arr[i][j].end()); //나이순 정렬
                for(int k=0;k<arr[i][j].size();k++) {
                    if(arr[i][j][k]<=A[i][j]) { // 자신의 나이만큼 양분 O
                        A[i][j]-=arr[i][j][k]; //양분 먹고
                        arr[i][j][k]++; //나이 1 증가
                    } else {// 자신의 나이만큼 양분 X
                        dead[i][j]+=arr[i][j][k]/2; //사망, 나이/2 -> 저장
                        arr[i][j].erase(arr[i][j].begin() + k); //삭제
                        k--; //인덱스 줄이기
                    }
                }
            }
        }
    }
}

void summer() {
    for(int i=1;i<=N;i++) {
        for(int j=1;j<=N;j++) {
            A[i][j]+=dead[i][j]; //양분 주기
            dead[i][j]=0; //초기화
        }
    }
}

void fall() {
    for(int i=1;i<=N;i++) {
        for(int j=1;j<=N;j++) {
            for(int k=0;k<arr[i][j].size();k++) {
                if(arr[i][j][k]%5==0 && arr[i][j][k]>=5) { //0이 아닌 5의 배수라면
                    for(int a=0;a<8;a++) {
                        int nx = i + dx[a];
                        int ny = j + dy[a];
                        if(nx>=1 && ny>=1 && nx<=N && ny<=N)
                            arr[nx][ny].push_back(1); // 인접 칸 전부 나무 1 생성
                    }
                }
            }
        }
    }
}

void winter() {
    for(int i=1;i<=N;i++)
        for(int j=1;j<=N;j++)
            A[i][j]+=A_plus[i][j]; //양분 주기
}


int main() {
    cin >> N >> M >> K;

    for(auto i=1;i<=N;i++)
        for(auto j=1;j<=N;j++) {
            cin >> A_plus[i][j]; //겨울마다 줄 양분
            A[i][j]=5; //초기 세팅 (양분 5)
        }

    for(auto i=0;i<M;i++) {
        int x,y,z;
        cin >> x >> y >> z;
        arr[x][y].push_back(z); //나무 입력
    }

    for(int i=0;i<K;i++) { //K년 반복
        spring();
        summer();
        fall();
        winter();
    }

    int result=0;

    for(int i=1;i<=N;i++)
        for(int j=1;j<=N;j++)
            result+=arr[i][j].size(); //나무 개수 세기

    cout << result;
}