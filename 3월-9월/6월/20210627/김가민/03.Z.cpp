#include<iostream>
#include<algorithm>

using namespace std;
int n, r, c, answer;
void solve(int n, int x, int y)
{
	if (x == r && y == c)
	{
		cout << answer << "\n";
		return;
	}
	if (r < x + n && r >= x && c < y + n && c >= y)
	{
		solve(n / 2, x, y);
		solve(n / 2, x, y + n / 2);
		solve(n / 2, x + n / 2, y);
		solve(n / 2, x + n / 2, y + n / 2);
	}
	else
		answer += n * n;
}
int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> n >> r >> c;
	solve((1<<n), 0, 0);

	return 0;
}