#include<algorithm>
#include<iostream>

using namespace std;

const int MAX = 3000000;

int arr[MAX];
int dish[3001];
//회전초밥 벨트에 놓인 접시를 오른쪽으로 한칸씩 이동하면서 초밥종류를 세어야 하므로
//투포인터 && 슬라이딩 윈도우 알고리즘을 이용한다
int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	int N, d, k, c, left, right, cnt = 0, result = 0;
	cin >> N >> d >> k >> c;

	//투포인터 알고리즘 사용을 위한 변수 초기화
	left = 0, right = k - 1;

	for (int i = 0; i < N; i++)
	{
		//arr 에 N까지 종류 입력받음
		cin >> arr[i];
	}

	for (int j = 0; j < k; j++)
	{
		//k개까지 입력받으면서 해당스시의 개수 dish에 입력 시킴
		dish[arr[j]]++;

		//k개까지의 스시 종류 count
		if (dish[arr[j]] == 1)
			cnt++;
	}

	//보너스 스시 계산
	dish[c]++;
	if (dish[c] == 1)
		cnt++;

	//left가 N보다 작을 때까지만 반복
	while (left < N)
	{
		//출력값은 가짓수의 최댓값이므로 max계산
		result = max(result, cnt);
		//left를 한칸 늘리면서 현재위치의 초밥종류를 --시킨다.
		//만약 제거한 초밥이 현재 하나도 없으면 cnt를 1줄임.
		if (--dish[arr[left++]] == 0)
			cnt--;
		//right는 N보다 크면 안되고, 사이클을 형성 해야하므로,
		//right는 right+1을 N으로 나눈 나머지
		right = (right + 1) % N;

		//right를 한칸 늘린후 추가 된 초밥종류를 ++시킨다.
		//추가된 초밥이 새로운 종류라면(즉 dish[]==1) cnt를 1증가시킴.
		if (++dish[arr[right]] == 1)
			cnt++;
	}

	cout << result << "\n";
	return 0;
}
//deque 사용
#include <iostream>
#include <algorithm>
#include <deque>
using namespace std;

const int MAX = 3000000;
int N, d, k, c;
int arr[MAX];
int dish[3001] = { 0 };
deque<int> dq;

int main()
{

	//cin, cout 속도향상
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	int cnt = 0, result = 0;
	cin >> N >> d >> k >> c;

	for (int i = 0; i < N; i++)
	{
		cin >> arr[i];	//N까지 돌면서 arr[i]에 값 입력받기
	}

	//첫번째 스시부터 k번째까지 덱에 넣고 스시의 종류를 센다
	for (int i = 0; i < k; i++)
	{
		dq.push_back(arr[i]);
		if (!dish[arr[i]]++)
		{
			cnt++;
		}
		result = max(result, cnt);
	}

	//슬라이딩 윈도우 사용
	for (int i = 0; i < N - 1; i++)
	{
		dq.pop_front();
		//해당 (dq에서 뺀) 스시의 종류가 없을 경우(즉 0이면) cnt를 뺀다
		if (!--dish[arr[i]])
			cnt--;

		//다음 스시((i+k)를 N으로 나눈 나머지)를 덱에 넣음
		dq.push_back(arr[(i + k) % N]);

		//새로운 종류의 스시라면(즉 1이면) cnt를 더해준다
		if (!(dish[arr[(i + k) % N]])++)
			cnt++;

		//덱에 쿠폰스시가 없다면
		if (!dish[c])
		{
			result = max(result, cnt + 1);
		}
		//덱에 쿠폰스시가 있다면
		else
			result = max(result, cnt);
	}

	cout << result << "\n";
	return 0;

}
