# 외벽 점검

### 문제설명

- 내부 공사를 하는 도중에 주기적으로 외벽의 상태를 점검해야할 필요 있음.
- 레스토랑의 구조는 완전히 동그란 모양이다.
- 외벽의 총 둘레는 n미터이다.
- 외벽의 몇몇 지점은 추위가 심할 경우 손상될 수 도 있는 최약한 지점들이 있습니다.
- 따라서 내부 공사 도중에는 외벽의 취약 지점들이 손상되지 않았는지, 주기적으로 친구들을 보내서 점검하기로 하였다.
- 단, 빠른 공사 진행을 위해 점검 시간을 1시간으로 제한하였다. 
- 1시간동안 이동할 수 잇는 거리는 제각각이다.
- 최소한의 친구들을 투입하여 취약 지점을 점검하고 나머지 친구들은 내부 공사를 돕도록 한다.
- 레스트랑의 정복 방향 지점을 0으로 나타낸다. 
- 취약 지점의 위치는 정복 방향 지점으로부터 시계 방향으로 떨어진 거리를 나타낸다.
- 친구들은 출발 지점부터 시계, 혹은 반시계방향으로 외벽을 따라서 이동한다. 



### Input

외벽의 길이 : n

취약 지점의 위치가 담긴 배열 : weak

각 친구가 1시간 동안 이동할 수 있는 거리가 담긴 배열 :dist



### Output

취약 지점을 점검하기 위해 보내야 하는 친구 수의 최솟값



### 제한사항

1<= n <=200

1<= weak.length() <=15

weak 위치는 오름차순으로 정렬되어 주어진다. 

0<= weak 원소 <= n-1

1<= dist.length() <= 100

친구들을 모두 투입해도 취약 지점을 전부 점검할 수 없는 경우 -1를 reture



### Solution

> 친구의 수를 적게 사용할려면 동일한 방향으로 탐색하지 못한 다음 취약 지점부터 다른 친구를 보내주어야 한다. 
>
>  직선화시키자





```c++
#include <string>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

int solution(int n, vector<int> weak, vector<int> dist) {
	int answer = -1;

	sort(dist.begin(), dist.end());

	queue<int> qu;
	for (int i = 0; i < weak.size(); i++) {
		qu.push(weak[i]);
	}
    
	for (int i = 0; i < weak.size(); i++) {
		int box = qu.front();
		if (box < qu.back())
			box += n;
		qu.pop();
		qu.push(box);

		do {
			int weak_index = 0;
			int dist_index = 0;

			for (dist_index = 0; dist_index < dist.size(); dist_index++) {
				int point = weak[weak_index] + dist[dist_index];

				while (point >= weak[weak_index]) {
					weak_index++;
					if (weak_index == weak.size())
						break;
				}
				if (weak_index == weak.size())
					break;
			}
			if (weak_index == weak.size()){
                if(answer > dist_index+1||answer==-1){
				    answer = dist_index+1;
                }
            }
		} while (next_permutation(dist.begin(), dist.end()));
	}


	return answer;
}
```



















https://programmers.co.kr/learn/courses/30/lessons/60062

