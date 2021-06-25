#include<iostream>
#include<algorithm>
#include<string>
#include<deque>
#include<cstring>

using namespace std;

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	int n, count, num;
	string AC;
	deque<int> dq;
	string arr, temp;

	cin >> n;
	while (n--)
	{
		cin >> AC;
		cin >> count;
		cin >> arr;
		num = 0;

		for (int i = 0; i < arr.size(); i++)
		{
			if (arr[i] == '[')
				continue;
			else if ('0' <= arr[i] && arr[i] <= '9')
			{
				temp += arr[i];
			}
			else if (arr[i] == ',' || arr[i] == ']')
			{
				if (!temp.empty())
				{
					dq.push_back(stoi(temp));
					temp.clear();
				}
			}
		}
		bool print = true;
		bool reverse = false;

		for (int k = 0; k < AC.length(); k++)
		{
			if (AC[k] == 'R')
			{
				reverse = !reverse;	//
			}
			else if (AC[k] == 'D')
			{
				if (dq.empty())
				{
					cout << "error" << "\n";
					print = false;
					break;
				}
				else
				{
					if (!reverse)
						dq.pop_front();
					else
						dq.pop_back();
				}
			}
		}

		if (print)
		{
			if (!reverse)
			{
				cout << "[";
				while (!dq.empty())
				{
					cout << dq.front();
					dq.pop_front();
					if (!dq.empty())
						cout << ",";
				}
				cout << "]" << "\n";
			}
			else
			{
				cout << "[";
				while (!dq.empty())
				{
					cout << dq.back();
					dq.pop_back();
					if (!dq.empty())
						cout << ",";
				}
				cout << "]" << "\n";
			}
		}
	}
	return 0;
}
