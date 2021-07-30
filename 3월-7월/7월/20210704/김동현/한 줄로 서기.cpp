#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main(void)
{
	int N, d;
	cin >> N;

	vector<int> vec(N), ans(N, 0);
	for (int i = 0; i < N; i++)
		cin >> vec[i];

	for (int i = N - 1; i >= 0; i--)
		ans.insert(ans.begin() + vec[i], i + 1);

	for_each(ans.begin(), ans.end(), [](const auto& n) { if (n != 0) cout << n << " "; });

	return 0;
}
