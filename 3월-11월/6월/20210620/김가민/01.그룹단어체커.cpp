#include<iostream>
#include<algorithm>

using namespace std;

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	int n, cnt = 0;
	string str;
	bool flag;
	cin >> n;

	for (int i = 0; i < n; i++)
	{
		cin >> str;
		flag = true;
		for (int j = 0; j < str.size(); j++)
		{
			for (int k = 0; k < j; k++)
			{
				if (str[j] != str[j - 1] && str[j] == str[k])
				{
					flag = false;
					break;
				}
			}
		}
		if (flag)
			cnt++;
	}
	cout << cnt << "\n";
	return 0;
}