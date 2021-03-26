#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int solution(string s) {
	int answer = s.length(); // 압축 문자열의 최대 길이 = 원래 문자열 길이
	string s1 = "";
	string s2 = "";

	for (int i = 1; i <= s.length() / 2; i++) { // i = 문자열을 자르는 단위(1개 ~ 문자열길이/2 )
		int idx = 0; // 문자열 index
		int length = 0; // 압축된 문자열의 전체 길이
		int compact = 0; // 압축된 문자열 개수

		while (1) {
			// idx를 기준으로 i개단위로 자른 2개의 문자열을 가져옴
			s1 = s.substr(idx, i);
			s2 = s.substr(idx + i, i);

			if (s1 == s2) { // 두 문자열이 같다면
				compact++; // 압축된 문자열 개수 증가
			}
			else { // 두 문자열이 다를때
				if (compact) { // 이전에 압축된 문자열이 있다면
					// 압축 개수 숫자의 길이를 구한 뒤 결과 문자열 길이에 더해줌
					// 3개 단위 문자열 압축 14개 -> length += 3(개 단위) + 2(14의 길이)
					compact++;
					length += i + to_string(compact).length();
					compact = 0; // 압축 문자 개수 초기화
				}
				else { // 이전에 압축된 문자열이 없다면
					length += i; // 결과 문자열의 길이만 증가
				}
			}

			idx += i; // 문자열 단위만큼 index 증가 

			if (idx + i > s.length()) {
				length += s2.length();
				break;
			}
		}

		answer = min(answer, length);
	}

	return answer;
}