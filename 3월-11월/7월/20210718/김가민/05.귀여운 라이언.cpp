#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

vector<int> arr;

//입력받은 인형 중에 라이언 인형이 있는 인덱스를 따로 벡터에 입력시키고,
//슬라이딩 윈도우, 투포인터 알고리즘 사용
int main()
{
	//입출력 속도향상
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	int left, right, N, K, len = 99999999, cnt=0, now;
	cin >> N >> K;
	//left=0, right=K-1로 셋팅
	left = 0;
	right = K-1;
	
	for (int i = 0; i < N; i++)
	{
		cin >> now;
		//입력받은 인형이 라이언 인형이면 arr에 해당인덱스를 넣는다.
		if (now == 1)
			arr.push_back(i);

	}
	//arr의 크기가 K보다 작으면 -1을 출력한다.
	if (arr.size() < K)
	{
		cout << -1 << "\n";
		return 0;
	}
//right값이 arr 크기보다 작을때까지 right와 left를 증가시키면서
//연속된 길이의 최솟값을 구한다.(슬라이딩윈도우, 투포인터)
    while(right<arr.size())
    {
        len = min(len, arr[right++] - arr[left++] + 1);
    }

	cout << len <<"\n";
	return 0;
}