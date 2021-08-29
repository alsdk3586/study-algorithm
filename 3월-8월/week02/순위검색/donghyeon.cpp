#include <string>
#include <vector>
#include <map>

using namespace std;

// applicants[언어][직군][경력][소울푸드] = {점수1,점수2,점수3...} 형태로 저장
map<string, map<string, map<string, map<string, vector<int>>>>> applicants;

// delimeter 기준으로 문자열 분리
vector<string> split(string info, char delimeter) {
	vector<string> result;
	string tmp = "";

	for (int i = 0; i < info.size(); i++) {
		if (info[i] == delimeter) {
			if (tmp != "and") { // "and" 문자열은 무시함
				result.push_back(tmp);
			}
			tmp = "";
		}
		else {
			tmp += info[i];
		}
	}
	result.push_back(tmp);

	return result;
}

vector<int> solution(vector<string> info, vector<string> query) {
	vector<int> answer;

	for (int i = 0; i < info.size(); i++) {
		vector<string> splitInfo = split(info[i], ' '); // 공백 기준 문자열 분리

		// 명시적으로 알아낸 값 이외에 모든 경우가 가능하게 값을 같이 저장해둠
		// 개발 언어가 cpp인 사람 -> 개발 언어가 '-'로 어떠한 언어도 가능한 사람 점수값에 같이 저장
		applicants[splitInfo[0]][splitInfo[1]][splitInfo[2]][splitInfo[3]].push_back(stoi(splitInfo[4]));
		applicants["-"][splitInfo[1]][splitInfo[2]][splitInfo[3]].push_back(stoi(splitInfo[4]));
		applicants[splitInfo[0]]["-"][splitInfo[2]][splitInfo[3]].push_back(stoi(splitInfo[4]));
		applicants[splitInfo[0]][splitInfo[1]]["-"][splitInfo[3]].push_back(stoi(splitInfo[4]));
		applicants[splitInfo[0]][splitInfo[1]][splitInfo[2]]["-"].push_back(stoi(splitInfo[4]));
		applicants["-"]["-"][splitInfo[2]][splitInfo[3]].push_back(stoi(splitInfo[4]));
		applicants["-"][splitInfo[1]]["-"][splitInfo[3]].push_back(stoi(splitInfo[4]));
		applicants["-"][splitInfo[1]][splitInfo[2]]["-"].push_back(stoi(splitInfo[4]));
		applicants[splitInfo[0]]["-"]["-"][splitInfo[3]].push_back(stoi(splitInfo[4]));
		applicants[splitInfo[0]]["-"][splitInfo[2]]["-"].push_back(stoi(splitInfo[4]));
		applicants[splitInfo[0]][splitInfo[1]]["-"]["-"].push_back(stoi(splitInfo[4]));
		applicants["-"]["-"]["-"][splitInfo[3]].push_back(stoi(splitInfo[4]));
		applicants["-"]["-"][splitInfo[2]]["-"].push_back(stoi(splitInfo[4]));
		applicants["-"][splitInfo[1]]["-"]["-"].push_back(stoi(splitInfo[4]));
		applicants[splitInfo[0]]["-"]["-"]["-"].push_back(stoi(splitInfo[4]));
		applicants["-"]["-"]["-"]["-"].push_back(stoi(splitInfo[4]));
	}

	for (int i = 0; i < query.size(); i++) {
		vector<string> splitQuery = split(query[i], ' ');
		// 알아내려는 지원자의 특성을 가져옴
		vector<int> applicant = applicants[splitQuery[0]][splitQuery[1]][splitQuery[2]][splitQuery[3]];
		// 기준점수를 가져옴
		int X = stoi(splitQuery[4]);
		int cnt = 0;

		// 지원자들 중 기준점수 이상인 사람 count
		for (int j = 0; j < applicant.size(); j++) {
			if (applicant[j] >= X) {
				cnt++;
			}
		}
		answer.push_back(cnt);
	}

	return answer;
}