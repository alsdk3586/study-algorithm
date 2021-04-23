# 4008. [모의 SW 역량테스트] 숫자 만들기

[
  ](https://swexpertacademy.com/main/solvingProblem/solvingProblem.do#collapseOne)





```c++

#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <string>
using namespace std;


int mins = 100000000;
int maxs = -100000000;

void cal(vector<int> op, vector<int> list) {
	if (list.size() == 1) {
		if (mins > list[0])
			mins = list[0];
		if (maxs < list[0])
			maxs = list[0];
		return;
	}

	int a = list[list.size()-1];
	list.pop_back();
	int b = list[list.size()-1];
	list.pop_back();

	if (op[0] > 0) {
		list.push_back(a + b);
		op[0]--;
		cal(op, list);
		list.pop_back();
		op[0]++;
	}
	if (op[1] > 0) {
		list.push_back(a - b);
		op[1]--;
		cal(op, list);
		list.pop_back();
		op[1]++;
	}
	if (op[2] > 0) {
		list.push_back(a * b);
		op[2]--;
		cal(op, list);
		list.pop_back();
		op[2]++;
	}
	if (op[3] > 0) {
		list.push_back(a / b);
		op[3]--;
		cal(op, list);
		list.pop_back();
		op[3]++;
	}
}
int main() {
	

	int tc = 0;
	cin >> tc;
	for (int p = 1; p <= tc; p++){
		int n = 0;
		cin >> n;
		mins = 100000000;
		maxs = -100000000;
		vector<int> op;
		int b = 0;
		for (int i = 0; i < 4; i++) {
			cin >> b;
			op.push_back(b);
		}

		vector<int> l;
		vector<int> list;
		int box = 0;
		for (int i = 0; i < n; i++) {
			cin >> box;
			l.push_back(box);
		}
		for (int i = 0; i < n; i++) {
			list.push_back(l[l.size() - 1]);
			l.pop_back();
		}
		cal(op, list);
		int answer = maxs - mins;
		cout << "#" << p << " " << answer << endl;
	}

	return 0;
}
```

