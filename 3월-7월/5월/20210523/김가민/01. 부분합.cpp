#include<algorithm>
#include<iostream>

using namespace std;

int arr[100001];

int main()
{
	int length = 9999999, N=0, S=0, i, p1, p2, sum=0;

	p1 = p2 = 0;
	cin >> N >> S;
	for (i = 0; i < N; i++)
	{
		cin >> arr[i];
	}
	sum = arr[0];
	while (p2 < N && p1 <= p2)
	{
		
		if (sum < S)
		{
			sum += arr[++p2];
		}
		else if (sum == S)
		{
			length = min(length, p2 - p1 + 1);
			sum += arr[++p2];
		}
		else if (sum > S)
		{
			length = min(length, p2 - p1 + 1);
			sum -= arr[p1];
			p1++;
		}
		
	}
	if (length == 9999999)
	{
		cout << 0;
	}
	else
	{
		cout << length;
	}
	return 0;

}