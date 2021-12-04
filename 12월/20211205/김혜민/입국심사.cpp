#include <string>
#include <vector>
#include <queue>
#include <algorithm>
#include <iostream>
using namespace std;
long long solution(int n, vector<int> times) {
	long long answer = 0;

	sort(times.begin(), times.end());
	long long start = 0;
	long long end = (long long)times[times.size()-1]*n;
	
	while (start <= end) {
		long long point = (start + end) / 2;

		long long count = 0;
		for (int i = 0; i < times.size(); i++) {
			count += point / times[i];
		}
		if (count < n) {
			start = point + 1;
		}
		else {
			if (point <= end)
				answer = point;
	
		    end = point - 1;
        }
	}


	return answer;
}



int main() {

	freopen("inp.inp", "r", stdin);
	freopen("out.out", "w", stdout);

	vector<int> a = { 7,10 };
	cout<<solution(6, a);
	return 0;
}