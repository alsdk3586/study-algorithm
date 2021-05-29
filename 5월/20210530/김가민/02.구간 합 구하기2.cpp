#include <iostream>
#include <cstdio>
#include <cmath>
#include <vector>

using namespace std;
typedef long long ll;

ll init(vector<ll>& arr, vector<ll>& tree, int node, int l, int r)
{
	if (l == r)
		return tree[node] = arr[l];
	int mid = (l + r) / 2;
	return tree[node] = init(arr, tree, node * 2, l, mid) + init(arr, tree, node * 2 + 1, mid + 1, r);
}

void updateLazy(vector<ll>& tree, vector<ll>& lazy, int node, int l, int r)
{
	if (lazy[node] == 0)
		return;

	//자식노드가 있는 수 만큼 lazy값에 곱하여 더함.
	tree[node] += (r - l + 1) * lazy[node];

	//leaf가 아니면 자식에게 lazy를 물려줌
	if (l != r)
	{
		lazy[node * 2] += lazy[node];
		lazy[node * 2 + 1] += lazy[node];
	}

	//물려준 후 lazy값 초기화
	lazy[node] = 0;
}

void update(vector<ll>& tree, vector<ll>& lazy, int node, int l, int r, int start, int end, ll val)
{
	//lazy있는지 확인후 lazy가 있으면 업데이트
	updateLazy(tree, lazy, node, l, r);

	//1. 범위내에 속하지 않는다면 return
	if (start > r || end < l)
		return;
	//2. 범위내에 속하는 경우 
	if (start <= l && r <= end)
	{
		//부모노드를 자식노드가 있는 수만큼 val을 곱해서 더해줌
		tree[node] += (r - l + 1) * val;

		//범위내에 속하지만 l과 r이 다른 경우
		if (l != r)
		{
			//lazy값에 val을 더해줌(lazy값 업데이트)
			lazy[node * 2] += val;
			lazy[node * 2 + 1] += val;
		}
		return;
	}
	//3. 범위에 걸쳐저 있는경우 mid값 계산하여 쪼갬
	int mid = (l + r) / 2;
	update(tree, lazy, node * 2, l, mid, start, end, val);
	update(tree, lazy, node * 2 + 1, mid + 1, r, start, end, val);
	//부모노드 업데이트
	tree[node] = tree[node * 2] + tree[node * 2 + 1];
}

ll sum(vector<ll>& tree, vector<ll>& lazy, int node, int l, int r, int start, int end)
{
	//update 이후 lazy값 분배(lazy 물려줌)
	updateLazy(tree, lazy, node, l, r);

	if (start > r || end < l)
		return 0;
	if (start <= l && r <= end)
		return tree[node];
	int mid = (l + r) / 2;
	return sum(tree, lazy, node * 2, l, mid, start, end) + sum(tree, lazy, node * 2 + 1, mid + 1, r, start, end);
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	int n, m, k;
	cin >> n >> m >> k;

	int h = (int)ceil(log2(n));
	int tree_size = (1 << (1 + h));
	vector<ll> arr(n);
	vector<ll> tree(tree_size);
	vector<ll> lazy(tree_size);

	for (int i = 0; i < n; i++)
	{
		cin >> arr[i];
	}

	init(arr, tree, 1, 0, n - 1);
	for (int i = 0; i < m + k; i++)
	{
		int num;
		cin >> num;
		if (num == 1)
		{
			int start, end;
			ll val;
			cin >> start >> end >> val;
			update(tree, lazy, 1, 0, n - 1, start - 1, end - 1, val);
		}
		else if (num == 2)
		{
			int start, end;
			cin >> start >> end;
			cout << sum(tree, lazy, 1, 0, n - 1, start - 1, end - 1) << "\n";
		}
	}
	return 0;
}