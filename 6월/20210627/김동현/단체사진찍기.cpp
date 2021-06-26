#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <map>
#include <bitset>

using namespace std;

map<pair <char, char>, bitset<8>> valid_conditions(vector<string>& cond)
{
	map<pair<char, char>, bitset<8>> adj;
	for (auto& s : cond)
    {
		if (s[0] > s[2])
			swap(s[0], s[2]);
        
		auto p = make_pair(s[0], s[2]);
        int w = s[4] - '0';
		int u = s[3] == '=' ? w : (s[3] == '>' ? w + 1 : 0);
		int v = s[3] == '=' ? w : (s[3] == '>' ? 6 : w - 1);
		bitset<8> bit;
		for (int i = u; i <= v; i++)
			bit.set(i);

		adj[p] = adj[p] == bitset<8>().reset() ? bit : adj[p] & bit;
	}

	return adj;
}

int solution(int n, vector<string> data)
{
	auto adj = valid_conditions(data);
	if (adj.size() <= 0)
		return 0;

	int mapper[26];
    const string friends = "ACFJMNRT";
	for_each(friends.begin(), friends.end(), [&, i = 0](const auto& c) mutable { mapper[c - 'A'] = i++; });

	vector<int> p { 0, 1, 2, 3, 4, 5, 6, 7 };
	int answer = 0;
	do {
		bool passed = true;
		for (const auto& kv : adj)
		{
			char from, target;
			tie(from, target) = kv.first;
			int g = abs(p[mapper[from - 'A']] - p[mapper[target - 'A']]) - 1;
			if (!kv.second[g])
			{
				passed = false;
				break;
			}
		}
		if (passed)
			answer++;
	} while (next_permutation(p.begin(), p.end()));
    
    return answer;
}
