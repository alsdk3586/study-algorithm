#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main(void)
{
	int N, d;
	cin >> N;

	vector<int> org, v, vi;
	auto bs = [&](int key) -> int {
		int low = 0, high = v.size() - 1, mid;
		while (high > low)
		{
			mid = (low + high) / 2;
			if (v[mid] >= key)
				high = mid;
			else
				low = mid + 1;
		}
		return high;
	};

	while (N--)
	{
		cin >> d;
		org.push_back(d);
		if (v.empty() || v.back() < d)
		{
			v.push_back(d);
			vi.push_back(v.size() - 1);
		}
		else
		{
			auto idx = bs(d);
			v[idx] = d;
			vi.push_back(idx);
		}
	}

	cout << v.size() << endl;
	int t = v.size() - 1;
	vector<int> correct;
	for (int i = vi.size() - 1; i >= 0; i--)
	{
		if (vi[i] == t)
		{
			t--;
			correct.push_back(org[i]);
		}
	}

	for (int i = correct.size() - 1; i >= 0; i--)
		cout << correct[i] << " ";
	cout << endl;
}
