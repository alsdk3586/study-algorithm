#include <string>
#include <vector>
#include <cctype>
#include <algorithm>

using namespace std;

typedef struct _pageInfo { // page의 정보를 담은 구조체
	int index; // page의 index
	string content; // page의 content
	vector<string> links; // page의 외부링크들의 content
	int baseScore; // page의 기본점수
	double machingScore = 0.0L; // page의 매칭점수
}PageInfo;
vector<PageInfo> pageInfoArr; // 페이지별 정보들을 저장하는 배열

// 정렬 기준 : 매칭점수 내림차순 -> 인덱스 오름차순
bool compare(PageInfo p1, PageInfo p2) {
	return p1.machingScore != p2.machingScore ? p1.machingScore > p2.machingScore : p1.index < p2.index;
}

// 웹페이지에서 content를 가져오는 함수
string getContent(string pages) {
	string content = "";
	string pattern = "<meta property=\"og:url\" content="; // 찾아야하는 정규표현식 패턴
	int index = pages.find(pattern); // 해당 패턴의 위치를 찾음

	index += pattern.length() + 1; // content 정보 시작 위치 = 패턴 위치 + 패턴 길이 + 1

	// " " 안에 있는 content 정보를 가져옴
	for (int i = index; i < pages.length(); i++) {
		if (pages[i] == '\"') {
			break;
		}
		content += pages[i];
	}

	return content;
}

// 기본 점수를 구하는 함수
int getBaseScore(string word, string pages) {
	string pattern = "<body>\n"; // 찾아야하는 정규표현식 패턴
	int index = pages.find(pattern); // 해당 패턴의 위치를 찾음
	index += pattern.length(); // 외부링크 정보 시작 위치 = 패턴 위치 + 패턴 길이

	string tmp = ""; // body 태크의 단어들 임시저장
	int baseScore = 0; // 기본점수

	for (int i = index; i < pages.length(); i++) {
		if (isalpha(pages[i])) { // 알파벳인 경우에만 저장
			tmp += tolower(pages[i]);
		}
		else { // 알파벳이 아니면
			if (tmp == word) { // 현재까지 저장한 단어가 word와 일치하는지 확인
				baseScore++;
			}
			tmp = ""; // 임시저장 단어 초기화
		}
	}

	return baseScore;
}

// 외부링크 주소들을 가져오는 함수
vector<string> getLinks(string pages) {
	vector<string> links; // 외부링크 주소를 저장
	string pattern = "<a href="; // 찾아야하는 패턴
	int index = 0;

	// index 위치부터 패턴을 계속 발견할 때까지 반복
	while ((index = pages.find("<a href=", index)) != string::npos) {
		string link = "";
		index += pattern.length() + 1; // 외부링크 주소 정보 시작 위치 = 패턴 위치 + 패턴 길이 + 1
		for (int i = index; i < pages.length(); i++) { // " " 안에 있은 외부링크의 주소 정보를 가져옴
			if (pages[i] == '\"') {
				break;
			}
			link += pages[i];
		}
		links.push_back(link);
	}

	return links;
}

// page -> 각각 필요한 정보를 취합해서 PageInfo 형태로 리턴
PageInfo getPageInfo(string word, string page, int index) {
	PageInfo pageInfo;
	pageInfo.index = index;
	pageInfo.content = getContent(page);
	pageInfo.baseScore = getBaseScore(word, page);
	pageInfo.links = getLinks(page);

	return pageInfo;
}

int solution(string word, vector<string> pages) {
	int answer = 0;

	transform(word.begin(), word.end(), word.begin(), ::tolower); // 검색어를 소문자로만 변경

	for (int i = 0; i < pages.size(); i++) {
		PageInfo pageInfo = getPageInfo(word, pages[i], i); // i번째 페이지에 대한 정보를 가져와서	
		pageInfoArr.push_back(pageInfo); // 페이지 정보들을 저장하는 배열에 넣음
	}

	// 각 페이지의 매칭점수를 구함
	for (int i = 0; i < pageInfoArr.size(); i++) {
		string content = pageInfoArr[i].content;
		pageInfoArr[i].machingScore += (double)pageInfoArr[i].baseScore; // 우선 기본점수를 더해줌
		for (int j = 0; j < pageInfoArr.size(); j++) { // 다른 페이지들을 점검
			if (i != j) {
				for (int k = 0; k < pageInfoArr[j].links.size(); k++) { // 다른 페이지들의 외부링크 점검
					// 만약 다른 페이지의 외부링크에 현재 점검하는 페이지 주소가 포함되어있다면
					if (content == pageInfoArr[j].links[k]) {
						// 현재 페이지 매칭점수에 참조하는 페이지의 링크점수를 더해줌
						pageInfoArr[i].machingScore +=
							(double)pageInfoArr[j].baseScore / pageInfoArr[j].links.size();
						break;
					}
				}
			}
		}
	}

	// 정렬 후 첫 번째 페이지의 인덱스를 구함
	sort(pageInfoArr.begin(), pageInfoArr.end(), compare);
	answer = pageInfoArr[0].index;

	return answer;
}