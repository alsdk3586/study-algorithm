#include <string>
#include <vector>
#include<unordered_map>
#include<sstream>
#include<algorithm>
using namespace std;
//이분탐색, 정렬 사용
unordered_map<string, int> Map;
vector<int> solution(vector<string> info, vector<string> query) {
    vector<int> answer;
    //크기: 4(언어)*3(경력)*3(직군)*3(소울푸드)=108에 대한 4차원 배열 정의
    vector<int> List[4][3][3][3];

    //각각의 경우에 대해 인덱스를 정의해줌
    Map["-"] = 0;
    Map["cpp"] = 1;
    Map["java"] = 2;
    Map["python"] = 3;
    Map["-"] = 0;
    Map["backend"] = 1;
    Map["frontend"] = 2;
    Map["-"] = 0;
    Map["junior"] = 1;
    Map["senior"] = 2;
    Map["-"] = 0;
    Map["chicken"] = 1;
    Map["pizza"] = 2;

    //info 파싱해서 처리
    for (auto str : info)
    {
        //stringstream 이용하여 파싱
        stringstream ss(str);
        string a, b, c, d;
        int score;
        ss >> a >> b >> c >> d >> score;
        //arr배열 선언한 후, 파싱한 값의 인덱스를 넣어주기
        int arr[4] = { Map[a], Map[b], Map[c], Map[d] };

        //모든 경우에 대해서 존재하는 경우와 존재하지 않는 경우(2*2*2*2=16)의 집합 만들기
        for (int i = 0; i < (1 << 4); i++)
        {
            //사용할 인덱스 4개를 0으로 초기화
            int idx[4] = { 0 };
            //j를 돌리면서 각각의 원소가 있는지 확인
            for (int j = 0; j < 4; j++)
            {
	//비트연산 이용해서 값이 존재하는 경우에
                if (i & (1 << j))
                {
                    //idx에 arr값 넣어줌
                    idx[j] = arr[j];
                }
            }
            //해당 인덱스에 score값을 넣어줌
            List[idx[0]][idx[1]][idx[2]][idx[3]].push_back(score);
        }
    }
    //lower_bound를 사용하기 위해 sorting 해줌
    for (int a = 0; a < 4; a++)
    {
        for (int b = 0; b < 3; b++)
        {
            for (int c = 0; c < 3; c++)
            {
                for (int d = 0; d < 3; d++)
                {
                    sort(List[a][b][c][d].begin(), List[a][b][c][d].end());
                }
            }
        }
    }
    //query 파싱
    for (auto str : query)
    {
        stringstream ss(str);
        string a, b, c, d, temp;
        int score;
        ss >> a >> temp >> b >> temp >> c >> temp >> d >> score;
        //List에서 가져와서 slist에 담아줌
        auto& slist = List[Map[a]][Map[b]][Map[c]][Map[d]];
        //low= score보다 큰 값들 중에 가장 낮은 인덱스
        vector<int>::iterator low = lower_bound(slist.begin(), slist.end(), score);
        //answer에 (slist의 끝인덱스-low인덱스= 코테점수를 목표값이상 받은 지원자수)를 넣어줌
        answer.push_back(slist.end() - low);
    }
    return answer;
}