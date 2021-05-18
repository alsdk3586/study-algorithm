#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <algorithm>
#include <tuple>

using namespace std;

bool trim(vector<string>& v)
{
	bool is_empty = true;
	for (auto& s : v)
	{
		s.erase(remove(s.begin(), s.end(), '0'), s.end());
		is_empty &= s.empty();
	}
	return is_empty;
}

tuple<int, int, int, int> get_boundary(int x, int y, int w, int h, int cost)
{
	int left = max(0, x - cost);
	int right = min(w, x + cost);
	int up = max(0, y - cost);
	int down = min(h, y + cost);

	return make_tuple(left, right, up, down);
}

int explosion(vector<string>& v, int index)
{
	int x = index;
	int y = v[index].length() - 1;
	int cost = v[x][y] - '1';

	queue<tuple<int, int, int>> q;
	q.push(make_tuple(x, y, cost));

	bool visited[12][15] = { false, };

	visited[x][y] = true;
	v[x][y] = '0';
	int ret = 1;

	while (!q.empty())
	{
		tie(x, y, cost) = q.front();
		q.pop();

		int left, right, up, down;
		tie(left, right, up, down) = get_boundary(x, y, v.size() - 1, v[x].length() - 1, cost);

		for (int i = left; i <= right; i++)
		{
			if (!visited[i][y] && (int)v[i].length() - 1 >= y)
			{
				if (v[i][y] - '1' > 0)
					q.push(make_tuple(i, y, v[i][y] - '1'));

				visited[i][y] = true;
				v[i][y] = '0';
				ret++;
			}
		}

		for (int i = up; i <= down; i++)
		{
			if (!visited[x][i])
			{
				if (v[x][i] - '1' > 0)
					q.push(make_tuple(x, i, v[x][i] - '1'));

				visited[x][i] = true;
				v[x][i] = '0';
				ret++;
			}
		}
	}

	return ret;
}

int solve(vector<string>& v, int N, int W, int H, int depth, int sum)
{
	if (depth >= N || trim(v))
		return sum;

	int ret = 0;
	for (int i = 0; i < W; i++)
	{
		if (v[i].length() > 0)
		{
			vector<string> snapshot(v);
			int erased = explosion(snapshot, i);
			ret = max(ret, solve(snapshot, N, W, H, depth + 1, sum + erased));
		}
	}

	return ret;
}

int main(int argc, char** argv)
{
	int T;
	cin >> T;

	for (int t = 1; t <= T; t++)
	{
		int N, W, H;
		cin >> N >> W >> H;

		int block_num = 0;
		vector<string> v(W, string(H, '0'));
		for (int i = 0; i < H; i++)
		{
			for (int j = 0; j < W; j++)
			{
				cin >> v[j][H - i - 1];
				block_num += (v[j][H - i - 1] != '0');
			}
		}

		cout << "#" << t << " " << block_num - solve(v, N, W, H, 0, 0) << endl;
	}

	return 0;
}
