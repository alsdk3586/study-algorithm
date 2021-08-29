#include <iostream>
#include <algorithm>
using namespace std;
int line[10];
int main()
{
	int n, num;
	cin >> n;
	for (int i = 0; i < n; i++)
	{
		cin >> num;
		for (int j = 0; j < n; j++)
		{
			if (num == 0 && line[j] == 0)
			{
				line[j] = i + 1;
				break;
			}
			else if (line[j] == 0)
				num--;

		}
	}
	for (int i = 0; i < n; i++)
	{
		cout << line[i] << " ";
	}
	return 0;
}