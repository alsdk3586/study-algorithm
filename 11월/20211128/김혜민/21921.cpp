#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;	


int main() {

	freopen("inp.inp", "r", stdin);
	freopen("out.out", "w", stdout);

	int n, x;
	cin >> n >> x;

	vector<long long> list;
	long long max=0;
	int maxCnt = 0;
	long long value = 0;
	int laterPoint = 0;
	for (int i = 0; i < n; i++) {
		int box = 0;
		cin >> box;

		if (i < x) {
			value += box;
			max = value;
			maxCnt = 1;
		}
		else {
			value -= list[laterPoint++];
			value += box;

			if (value == max) {
				maxCnt++;
			}
			else if (value > max) {
				maxCnt = 1;
				max = value;
			}
		}
		list.push_back(box);
	}
	if (x >= n) {
		max = value;
		maxCnt = 1;
	}
	if (max == 0)
		cout << "SAD" << endl;
	else {
		cout << max << endl;
		cout << maxCnt;
	}
	return 0;
}