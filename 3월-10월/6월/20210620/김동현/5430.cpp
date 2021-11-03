#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <sstream>

using namespace std;

void solution(const string& s, int start, int end, bool r)
{
	stringstream ss(s);
	string token;
	vector<string> v;

	for (int i = 0; getline(ss, token, ','); i++)
	{
		if (i >= start && i < end)
			v.push_back(token + ',');
	}

	cout << "[";
	for (int i = 0; i < (int)v.size(); i++)
	{
		int idx = r ? (int)v.size() - i - 1 : i;
		if (i == v.size() - 1)
			v[idx].pop_back();
		cout << v[idx];
	}
	cout << "]" << endl;
}

int main(void)
{
	int T, N;
	cin >> T;
	cin.ignore();

	while (T--)
	{
		string cmd, s;
		getline(cin, cmd);
		cin >> N;
		cin.ignore();
		getline(cin, s);

		bool r = false;
		int rng[2] = { 0, };
		for (const auto& c : cmd)
		{
			if (c == 'R')
				r = !r;
			else
				rng[r]++;
		}

		if (rng[0] + rng[1] > N)
			cout << "error" << endl;
		else
			solution(string(s.begin() + 1, s.end() - 1), rng[0], N - rng[1], r);
	}

	return 0;
}
