#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <string>
#include <map>
using namespace std;	


string makeLarge(string a) {
	string answer = "";

	for (int i = 0; i < a.length(); i++) {
		if (a[i] >= 'a'&&a[i] <= 'z')
			answer += (a[i] + 'A' - 'a');
		else if (a[i] >= 'A'&&a[i] <= 'Z')
			answer += a[i];
		else
			return "";
	}
	return answer;
}

int solution(string str1, string str2) {
	double answer = 0;
	
	if (str1.length() == 0 && str2.length() == 0)
		return 65536;

	int all = 0;
	map<string, int> m;
	for (int i = 1; i < str1.length(); i++) {
		string box = "";
		box += str1[i - 1];
		box += str1[i];
		box=makeLarge(box);
		if (box == "")
			continue;
		all++;
		if (m.find(box) == m.end())m[box] = 1;
		else m[box]++;
	}

	int same = 0;
	map<string, int> m1;
	for (int i = 1; i < str2.length(); i++) {
		string box = "";
		box += str2[i - 1];
		box += str2[i];
		box = makeLarge(box);
		if (box == "")
			continue;
		if (m.find(box) != m.end()) { 
			if(m1.find(box)==m1.end()||m1.find(box)->second<m.find(box)->second)
				same++; 
			else all++;
			if (m1.find(box) == m1.end())
				m1[box] = 1;
			else
				m1[box]++;
		}
		else all++;
	}
	if (all == 0)
		return 65536;
	answer =(double) same / all;
	return answer*65536;
}


int main() {

	freopen("inp.inp", "r", stdin);
	freopen("out.out", "w", stdout);


	cout<<solution("aa1+aa2", "AAAA12");
	return 0;
}