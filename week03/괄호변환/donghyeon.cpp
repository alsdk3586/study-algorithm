#include <string>
#include <vector>
#include <stack>

using namespace std;

// 올바른 문자열인지 체크
bool checkRightStr(string u) {
	if (u.length() == 0) {
		return true;
	}

	// 스택 -> 짝이 맞는지 확인
	stack<char> s;
	s.push(u[0]);

	for (int i = 1; i < u.length(); i++) {
		if (u[i] == '(') {
			s.push(u[i]);
		}
		else {
			if (s.top() == '(') {
				s.pop();
			}
			else {
				s.push(u[i]);
			}
		}
	}

	if (!s.empty()) {
		return false;
	}
	return true;
}

// 올바른 문자열을 만듦
string makeRightStr(string w) {
	// 1단계 : 빈 문자열 -> 반환
	if (w.length() == 0) {
		return "";
	}

	string u = "";
	string v = "";
	string rightStr = ""; // 결과 문자열
	int cnt1 = 0; // 문자 '('의 개수
	int cnt2 = 0; // 문자 ')'의 개수

	// 2단계 : 문자열 w를 균형잡힌 문자열 u, v로 분리
	for (int i = 0; i < w.length(); i++) {
		// 문자 '('와 ')'의 개수를 카운트
		if (w[i] == '(') {
			cnt1++;
		}
		else {
			cnt2++;
		}
		u += w[i];

		if (cnt1 == cnt2) { // 문자 '('와 ')'의 개수가 같은 순간 u는 균형잡힌 문자열 확정
			for (int j = i + 1; j < w.length(); j++) { // 나머지 문자열은 v에 
				v += w[j];
			}
			break;
		}
	}

	if (checkRightStr(u)) { // 3단계 : u가 올바른 문자열이라면 v에 대해 1단계 다시 수행
		rightStr = u + makeRightStr(v); // 3-1단계 : 수행한 결과 문자열에 u를 이어붙이고 반환
	}
	else { // 4단계 : u가 올바른 문자열이 아니면
		rightStr += '('; // 4-1단계 : 첫 문자로 '(' 붙임
		rightStr += makeRightStr(v); // 4-2단계 : 문자열 v에 대해 1단계부터 재귀적으로 수행한 결과를 붙임
		rightStr += ')'; // 4-3단계 : ')'를 다시 붙임

		// 4-4단계 : 두 번째부터 마지막-1 문자열까지 괄호 방향을 뒤집어서 붙임 
		for (int i = 1; i < u.length() - 1; i++) {
			if (u[i] == '(') {
				rightStr += ')';
			}
			else {
				rightStr += '(';
			}
		}
	}

	return rightStr; // 최종 결과 문자열을 반환
}

string solution(string p) {
	string answer = "";

	return makeRightStr(p);
}