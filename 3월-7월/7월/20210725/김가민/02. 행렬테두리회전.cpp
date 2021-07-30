#include <algorithm>
#include <vector>

using namespace std;

//행렬 테두리의 네변을 각각 4가지 경우로 나눠서 조건식을 만든다.
#define INF 987654321
int map[100][100];
int minVal;

//네변에서 가장 작은 수를 구하기 위한 compare함수 선언
void comp(int val)
{
    minVal = min(minVal, val);
}
vector<int> solution(int rows, int columns, vector<vector<int>> queries) {
    vector<int> answer;
    int num = 0;
    //맵 생성
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            num++;
            map[i][j] = num;
        }
    }
    //query에서 받은 행과 열로 row1, 2, col1, 2 값 저장
    for (int i = 0; i < queries.size(); i++)
    {
        //행과 열은 0부터 시작하므로 1씩 빼줌
        int row1 = queries[i][0]-1;
        int col1 = queries[i][1]-1;
        int row2 = queries[i][2]-1;
        int col2 = queries[i][3]-1;
        //query의 처음 시작 행, 열 값을 temp에 넣어줌 
        //temp 변수 없으면 처음 시작값이 누적됨
        int temp = map[row1][col1];
        //minVal 초기화
        minVal = INF;
        comp(temp);

        //4변의 방향에 따른 조건식 설정-시계 반대방향으로 식 돌리면 됨
            
            //아래->위 인 경우
            for (int i = row1; i < row2; i++)
            {
                map[i][col1] = map[i+1][col1];
                comp(map[i+1][col1]);
            }
            //오른쪽->왼쪽 인 경우
            for (int i = col1; i < col2; i++)
            {
                map[row2][i] = map[row2][i+1];
                comp(map[row2][i + 1]);
            }
            //위->아래 인 경우
            for (int i = row2; i > row1; i--)
            {
                map[i][col2] = map[i-1][col2];
                comp(map[i - 1][col2]);
            }
            //왼쪽->오른쪽 인 경우
            for (int i = col2; i > col1; i--)
            {
                map[row1][i] = map[row1][i-1];
                comp(map[row1][i - 1]);
            }
            //마지막에 시작점의 열+1 위치에 temp값을 넣어준다.(시작점의 열+1 위치의 값은 열+2 값에 영향을 미치기 때문에)
            map[row1][col1 + 1] = temp;
            answer.push_back(minVal);
    }
    return answer;
}