#include<stdio.h>
#include<algorithm>
#include<math.h>
#include<string.h>
#include<stdlib.h>
#include<iostream>
#include<vector>
using namespace std;
vector<int> v;
int main()
{
	int n,x;
	
	scanf("%d", &n);
	for (int i = 0; i < n; i++)
	{
		scanf("%d", &x);
		if (v.empty() || v.back() < x)
		{
			v.push_back(x);
		}
		else
		{
			auto iter = lower_bound(v.begin(), v.end(), x);
			*iter = x;
		}
	}
	printf("%d", int(v.size()));
	return 0;

}