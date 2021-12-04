#include<iostream>

using namespace std;
long long tree[1 << 21];
typedef long long ll;
int n, m, k;

void update(int node, int l, int r, ll index, ll num)
{
	if (l == r)
	{
		tree[node] = num;
		return;
	}
	int mid = (l + r) / 2;
	if (index <= mid) update(node * 2, l, mid, index, num);
	else update(node * 2 + 1, mid + 1, r, index, num);

	tree[node] = tree[node * 2] + tree[node * 2 + 1];
}

ll calc(int node, int l, int r, ll start, ll end)
{
	if (start > r || end < l)
		return 0;

	if (start <= l && r <= end)
		return tree[node];

	int mid = (l + r) / 2;
	return calc(node * 2, l, mid, start, end) + calc(node * 2 + 1, mid + 1, r, start, end);
}

int main() 
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	ll num;
	ll a, b, c;

	cin >> n >> m >> k;

	for (ll i = 1; i <= n; i++)
	{
		cin >> num;
		update(1, 1, n, i, num);
	}

	for (int i = 0; i < m + k; i++)
	{
		cin >> a >> b >> c;
		if (a == 1) update(1, 1, n, b, c);

		else cout << calc(1, 1, n, b, c) << "\n";
	}

	return 0;
}