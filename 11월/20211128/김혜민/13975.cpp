#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;	


int main() {

	freopen("inp.inp", "r", stdin);
	freopen("out.out", "w", stdout);

	int tc = 0;
	cin >> tc;
	for (int q = 0; q < tc; q++) {
	
		int n = 0;
		cin >> n;
		
		priority_queue<long long,vector<long long>,greater<long long>> pq;
		for (int i = 0; i < n; i++) {
			int box;
			cin >> box;
			pq.push(box);
		}

		long long answer = 0;
		while (pq.size()>1) {
			long long v1 = pq.top();
			pq.pop();
			long long v2 = pq.top();
			pq.pop();
			answer += (v1 + v2);
			pq.push(v1 + v2);
		}
		cout << answer<<endl;
	}

	return 0;
}