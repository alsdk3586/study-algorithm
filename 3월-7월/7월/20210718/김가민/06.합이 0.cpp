#include <iostream>
#include <algorithm>

using namespace std;
//이분탐색, 정렬 사용
//배열을 입력받아 오름차순으로 정렬해준 뒤에 맨앞의 두수를 선택하고 두수의 합을 구한다.
//합이 0이 되려면 구한 두수의 합에 -1을 해준 후 해당값의 lower, upper bound를 구해주고 두 결과의 차를 구해주면 된다.
int num[10001];

int main()
{
	//cin, cout 속도 향상
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	int N, temp; 
	//**cnt자료형에 주의
   	long long cnt=0;
	cin >> N;

	for (int i = 0; i < N; i++)
	{
		cin >> num[i];
	}
	//받은 배열을 오름차순으로 정렬
	sort(num, num+N);
	//맨앞의 두개의 수를 선택해야 하므로 for문을 두번 돌림
	for (int i = 0; i < N - 2; i++)
	{
		for (int j = i + 1; j < N-1; j++)
		{
			//temp에 맨앞 두수의 합에 -1을 한 값을 넣어줌
			temp = (-1)*(num[i] + num[j]);
			//선택한 두 수의 바로 뒤 인덱스부터 배열의 끝까지 temp값의 lower bound의 인덱스를 찾아준다.
			int idx = lower_bound(num +j+1, num +N, temp) - num;
			//선택한 두 수의 바로 뒤 인덱스부터 배열의 끝까지 temp값의 upper bound의 인덱스를 찾아준다.
			int idx2 = upper_bound(num + j + 1, num + N, temp) - num;
			//cnt에 각각의 결과값을 뺀 값을 담아준다.
			cnt += idx2 - idx;
		}
	}

	cout << cnt << "\n";
	return 0;
}