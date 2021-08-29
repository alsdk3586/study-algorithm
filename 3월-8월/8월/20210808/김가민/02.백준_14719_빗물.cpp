#include<iostream>
#include<algorithm>
#include<math.h>
#include<cstring>

using namespace std;
//1.하나의 블럭을 기준으로 양옆을 탐색하면서 가장 긴 블럭을 하나씩 찾는다.
//2.양옆으로 찾은 두개의 블럭중 작은 블럭에서 하나의 블럭을 뺀만큼 빗물을 담을 수 있다.
//투포인터 사용
int arr[501];
int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	int p1, p2, h, w, sum = 0, cnt = 0;
	cin >> h >> w;


	for (int i = 0; i < w; i++)
	{
		cin >> arr[i];
	}

	for (int i = 0; i < w; i++)
	{
		//빗물이 고이려면 양옆 블럭이 길이가 입력받는 블럭의 길이 보다 커야하므로
		//p1, p2에 입력받은 블럭의 길이 넣어줌
		p1 = p2 = arr[i];
		for (int j = 0; j < i; j++)
		{
			p1 = max(p1, arr[j]);
		}
		for (int k = i + 1; k < w; k++)
		{
			p2 = max(p2, arr[k]);
		}

		//양옆블럭 중 작은 블럭에서 입력받은 블럭을 뺀 만큼 빗물을 담을 수 있음
		sum += (min(p1, p2) - arr[i]);

	}
	cout << sum << "\n";
	return 0;
}