#include <iostream>
#include <string>

using namespace std;

bool is_group_word(const string& s)
{
	char cur = s.front();
	bool chk[26] = { false, };
	for (const auto& c : s)
	{
		if (cur != c && chk[c - 'a'])
			return false;

		chk[c - 'a'] = true;
		cur = c;
	}
	return true;
}

int main(void)
{
	int N, answer = 0;
	cin >> N;
	cin.ignore();

	while (N--)
	{
		string s;
		getline(cin, s);
		answer += is_group_word(s);
	}

	cout << answer << endl;

	return 0;
}
