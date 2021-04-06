#include <string>
#include <vector>
#include <map>
#include <sstream>

using namespace std;

// 공백을 기준으로 문자열 분리
// result[0] : 명령어, result[1] : 유저 아이디, result[2] : 닉네임
vector<string> splitString(string str) {
	vector<string> result;
	string tmp = "";

	for (int i = 0; i < str.length(); i++) {
		if (str[i] == ' ') {
			result.push_back(tmp);
			tmp = "";
		}
		else {
			tmp += str[i];
		}
	}
	result.push_back(tmp);

	return result;
}

vector<string> solution(vector<string> record) {
	vector<string> answer;
	map<string, string> nicknames; // <유저 아이디, 닉네임>
	vector<pair<string, string>> messages; // <유저 아이디, 메시지>

	for (int i = 0; i < record.size(); i++) {
		vector<string> info = splitString(record[i]);

		// (유저 아이디, 메시지) 형태로 vector에 저장 
		if (info[0] == "Leave") {
			messages.push_back(make_pair(info[1], "님이 나갔습니다."));
		}
		else {
			if (info[0] == "Enter") {
				messages.push_back(make_pair(info[1], "님이 들어왔습니다."));
			}
			nicknames[info[1]] = info[2]; // 새 유저가 들어왔으면 무조건 닉네임 변경
		}
	}

	for (int i = 0; i < messages.size(); i++) { // 메시지 배열 탐색
		string userId = messages[i].first; // 유저 아이디를 가져옴
		// <유저 아이디에 해당하는 닉네임, 메시지> 형태로 다시 저장
		answer.push_back(nicknames[userId] + messages[i].second);
	}

	return answer;
}