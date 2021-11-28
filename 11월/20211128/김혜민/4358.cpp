#include <iostream>
#include <map>
#include <algorithm>
#include <string>
using namespace std;


int main() {

	freopen("inp.inp", "r", stdin);
	freopen("out.out", "w", stdout);
	map<string, int> m;
	int count = 0;
	while (1) {
		string box;
		getline(cin, box);
		if (box == "" || box == "\0")
			break;
		if (m.find(box) == m.end())
			m[box] = 1;
		else
			m[box]++;
		count++;
	}

	cout << fixed;
	cout.precision(4);
	for (auto point = m.begin(); point != m.end(); point++) {
		double a = (double)(((double)point->second / count) * 100);
		cout << point->first << " " << a << endl;
	}

	return 0;
}