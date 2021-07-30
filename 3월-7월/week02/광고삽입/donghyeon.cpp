#include <string>
#include <vector>
#include <algorithm>

using namespace std;

// delimeter 기준으로 문자열 분리
vector<string> splitStr(string str, char delimeter) {
	vector<string> split_str;
	string tmp = "";

	for (int i = 0; i < str.length(); i++) {
		if (str[i] == delimeter) {
			split_str.push_back(tmp);
			tmp = "";
		}
		else {
			tmp += str[i];
		}
	}
	split_str.push_back(tmp);

	return split_str;
}

// 시간 -> int형 값으로
int getTime(vector<string> time) {
	int hour = stoi(time[0]) * 60 * 60;
	int minute = stoi(time[1]) * 60;
	int second = stoi(time[2]);

	return hour + minute + second;
}

string solution(string play_time, string adv_time, vector<string> logs) {
	string answer = "";
	int end_time = getTime(splitStr(play_time, ':')); // 동영상 재생 시간
	int adv_playing_time = getTime(splitStr(adv_time, ':')); // 광고 재생 시간
	vector<int> cnt(360001, 0); // 0초 ~ 360000초까지 시청자 재생 횟수를 저장
	                            // cnt[i] -> i초에 동영상을 재생한 시청자 수

	// 동영상 재생 시간보다 광고 시간이 길면 광고 시작 시간은 맨 처음이 유일 
	if (end_time <= adv_playing_time) {
		answer = "00:00:00";
		return answer;
	}

	for (int i = 0; i < logs.size(); i++) {
		// 로그 기록 -> 시청자 재생 시작 시간, 끝 시간
		vector<string> splited = splitStr(logs[i], '-');
		int st = getTime(splitStr(splited[0], ':'));
		int et = getTime(splitStr(splited[1], ':'));

		// 시청자 재생 시작 시간 ~ 끝 시간까지 재생 횟수를 증가
		for (int j = st; j < et; j++) {
			cnt[j]++;
		}
	}

	int start_time = 0; // 공익 광고 시작 시간
	long long total_cnt = 0; // 누적 재생 시간
	long long max_total_cnt = 0; // 최대 누적 재생 시간
	for (int i = start_time; i < adv_playing_time; i++) {
		total_cnt += cnt[i]; // 시간 시간부터 광고 재생시간 동안 누적 재생 횟수를 구함
	}
	max_total_cnt = total_cnt;

	int i = start_time;
	while (1) {
		// i ~ (i + adv_playing_time)구간 이후 -> (i + 1) ~ (i + adv_playing_time + 1)구간 누적합 구함
		// (a+1 ~ b+1)구간 누적값 = (a~b)구간의 누적값 - a구간 값 + (b+1)구간 값
		total_cnt -= cnt[i];
		total_cnt += cnt[i + adv_playing_time];
		i++;

		// 부분 누적값이 가장 큰 값을 저장
		if (total_cnt > max_total_cnt) {
			max_total_cnt = total_cnt;
			start_time = i;
		}

		// 동영상 시작시간 + 광고시간 -> 동영상 재생시간보다 크면 종료
		if (i + adv_playing_time > end_time) {
			break;
		}
	}



	// 시작 시간 문자열 -> 시간, 분, 초단위로 나눔
	string hour = to_string(start_time / 3600);
	string minute = to_string((start_time % 3600) / 60);
	string second = to_string(start_time % 60);

	// "X" -> "0X"로 만드는 과정
	if (hour.length() == 1) {
		hour = "0" + hour;
	}
	if (minute.length() == 1) {
		minute = "0" + minute;
	}
	if (second.length() == 1) {
		second = "0" + second;
	}

	answer = hour + ":" + minute + ":" + second;

	return answer;
}