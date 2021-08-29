//
// Created by Sujin Kim on 21. 3. 15..
//

#include <string>
#include <vector>

using namespace std;

string solution(string new_id) {
    string answer = "";

    // 1단계: 대문자 -> 소문자
    for (char& c:new_id) {
        c = tolower(c);
    }

    // 2단계: 알파벳 소문자, 숫자, 빼기(-), 밑줄(_), 마침표(.)를 제외한 모든 문자를 제거
    for (char& c:new_id) {
        if (('a' <= c && c <= 'z') || ('0' <= c && c <= '9') || c == '-' || c == '_' || c == '.')
            answer += c;
    }

    // 3단계 : 마침표(.)가 2번 이상 연속된 부분을 하나의 마침표(.)로 치환
    string::size_type pos = 0;
    string pattern = "..";
    while ((pos = answer.find(pattern)) != std::string::npos)
        answer.replace(pos, pattern.size(), ".");

    // 4단계: 마침표(.)가 처음이나 끝에 위치한다면 제거
    if (answer[0] == '.')
        answer = answer.substr(1, answer.size() - 1);
    if (answer.size() > 0 && answer[answer.size() - 1] == '.')
        answer = answer.substr(0, answer.size() - 1);

    // 5단계: 빈 문자열이라면, new_id에 "a"를 대입
    if (answer.empty())
        answer += "a";

    // 6단계: new_id의 길이가 16자 이상이면, new_id의 첫 15개의 문자를 제외한 나머지 문자들을 모두 제거
    //      만약 제거 후 마침표(.)가 new_id의 끝에 위치한다면 끝에 위치한 마침표(.) 문자를 제거
    if (answer.size() >= 16) {
        answer = answer.substr(0, 15);
        if (answer.size() > 0 && answer[answer.size() - 1] == '.')
            answer = answer.substr(0, answer.size() - 1);
    }

    // 7단계: new_id의 길이가 2자 이하라면, new_id의 마지막 문자를 new_id의 길이가 3이 될 때까지 반복해서 끝에 붙임
    while (answer.size() < 3) {
        answer += answer[answer.size() - 1];
    }


    return answer;
}