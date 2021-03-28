#include <string>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

map<string, int> menu; // 메뉴,등장횟수
map<int, int> maxCnt; // 메뉴의 길이, 최대등장횟수

// 문자배열 정렬 : CBA -> ABC
bool cmp1(char c1, char c2) {
	return c1 < c2;
}

// 문자열 정렬 : AC,AB -> AB,AC
bool cmp2(string& s1, string& s2) {
	return s1 < s2;
}

// n자리 문자열에서 k개를 뽑는 조합을 구함 
void nck(vector<char> c, string order, int n, int k) {
	if (k == 0) {
		string newMenu = "";

		sort(c.begin(), c.end(), cmp1);

		for (int i = 0; i < c.size(); i++) {
			newMenu += c[i];
		}

		if (menu.find(newMenu) == menu.end()) {
			menu[newMenu] = 1;
		}
		else {
			menu[newMenu]++;
		}

		if (maxCnt.find(newMenu.length()) == maxCnt.end()) {
			maxCnt[newMenu.length()] = 1;
		}
		else {
			maxCnt[newMenu.length()] = max(maxCnt[newMenu.length()], menu[newMenu]);
		}
	}
	else if (n < k) {
		return;
	}
	else {
		c[k - 1] = order[n - 1];
		nck(c, order, n - 1, k - 1);
		nck(c, order, n - 1, k);
	}
}

vector<string> solution(vector<string> orders, vector<int> course) {
	vector<string> answer;

	for (int i = 0; i < orders.size(); i++) {
		for (int j = 0; j < course.size(); j++) {
			if (orders[i].size() >= course[j]) {
				vector<char> c(course[j], 0);
				nck(c, orders[i], orders[i].size(), course[j]);
			}
		}
	}

	map<string, int>::iterator it;

	for (int i = 0; i < course.size(); i++) {
		if (maxCnt[course[i]] <= 1) {
			continue;
		}
		for (it = menu.begin(); it != menu.end(); it++) {
			if (it->first.length() == course[i] && (it->second == maxCnt[course[i]])) {
				answer.push_back(it->first);
			}
		}
	}

	sort(answer.begin(), answer.end(), cmp2);

	return answer;
}