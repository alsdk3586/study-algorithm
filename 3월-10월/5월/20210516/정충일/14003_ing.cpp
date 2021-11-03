//https://cocoon1787.tistory.com/457

#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

int N, cnt;
int A[1000001], dp[1000001];
vector<int> v, ans;

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	cin >> N;

	for (int i = 1; i <= N; i++)
		cin >> A[i];
		
	v.push_back(A[1]);

	for (int i = 2; i <= N; i++) {
		if (v[cnt] < A[i]) {
			v.push_back(A[i]);
			cnt++;
			dp[i] = cnt;
		}
		else {
			int pos = lower_bound(v.begin(), v.end(), A[i]) - v.begin();
			v[pos] = A[i];
			dp[i] = pos;
		}
	}

	int LIS_size = cnt;

	for (int i = N; i >= 0; i--) {
		if (dp[i] == LIS_size) {
			ans.push_back(A[i]);
			LIS_size--;
		}
	}

	int size = ans.size();
	cout << size << '\n';
	for (int i = 0; i < size; i++) {
		cout << ans.back() << " ";
		ans.pop_back();
	}
	
}