#include <string>
#include <vector>
#include <set>
#include <algorithm>

using namespace std;

// bits 조합이 Unique 조건을 만족하는지 확인
bool checkUnique(vector<vector<string>>& relation, string bits) {
	set<string> set; // 문자열 조합을 저장
	int flag = 1; // 1 : Unique 조건을 만족, 0 : Unique 조건을 만족X

	for (int i = 0; i < relation.size(); i++) {
		string str = "";
		for (int j = 0; j < bits.length(); j++) {
			if (bits[j] == '1') { // 체크되있는 비트의 속성을 추가
				str += relation[i][j];
			}
		}

		if (set.find(str) == set.end()) { // 처음 등장하는 문자열 조합 -> 유일성 만족
			set.insert(str);
		}
		else { // 이미 등장한 문자열 조합 -> 해당 비트 조합은 유일성 만족X
			flag = 0;
			break;
		}
	}

	return flag;
}

// 인자로 들어온 수를 비트로 변환했을 때 1의 개수 count
int count_bit(int n) {
	int ret = 0;

	while (n) {
		if (n & 1) {
			ret++;
		}
		n = n >> 1;
	}

	return ret;
}

// 비트 변환 후 1의 개수에 따라 오름차순 정렬
bool comp(int& a, int& b) {
	return count_bit(a) < count_bit(b);
}

int solution(vector<vector<string>> relation) {
	int answer = 0;
	int n = relation[0].size();
	vector<int> uniqueComb; // 유일성을 만족하는 조합의 수를 저장, 0011 -> 유일성 만족 -> 3 저장

	// 모든 조합의 수를 비트로 표현
	// 0000 ~ 1111
	for (int i = 0; i < (1 << (n)); i++) {
		string bits = "";
		for (int j = 0; j < n; j++) {
			if (i & (1 << j)) {
				bits += "1";
			}
			else {
				bits += "0";
			}
		}

		if (checkUnique(relation, bits)) { // 해당 조합이 유일성을 만족하면 해당 조합을 만드는 수를 저장
			uniqueComb.push_back(i);
		}
	}

	vector<int> checkMinimal(uniqueComb.size(), 1); // 1 : 해당 조합이 최소성을 만족, 0 : 최소성 만족X

	sort(uniqueComb.begin(), uniqueComb.end(), comp);

	for (int i = 0; i < uniqueComb.size() - 1; i++) {
		int n = uniqueComb[i]; // 유일성을 만족시키는 i번째 수를 기준으로

		for (int j = i + 1; j < uniqueComb.size(); j++) { // 이후의 모든 수들과 비교하며 최소성을 만족하는지 확인
			if (checkMinimal[j] == 0) { // 이미 최소성을 만족시키지 못하는 조합은 넘어감
				continue;
			}

			if ((n & uniqueComb[j]) == n) { // 공유하고 있는 비트가 있다면 -> 공통된 속성이 있다면
				checkMinimal[j] = 0; // 해당 조합은 최소성 만족X
			}
		}
	}

	for (int i = 0; i < uniqueComb.size(); i++) { // 유일성을 만족하는 모든 조합 중
		if (checkMinimal[i]) { // 최소성을 만족하는 조합을 count
			answer++;
		}
	}

	return answer;
}