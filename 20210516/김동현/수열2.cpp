#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main(void)
{
	int N, d;
	cin >> N;

	vector<int> v;
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
		if (v.empty() || v.back() < d)
			v.push_back(d);
		else
			v[bs(d)] = d;
	}

	cout << v.size() << endl;
}
