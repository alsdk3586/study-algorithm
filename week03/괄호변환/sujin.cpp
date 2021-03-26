#include <string>
#include <vector>
#include <algorithm>

using namespace std;

// 올바른 괄호 문자열인지 파악한다.
bool isCorrect(string& w) {
    int k = 0;
    for (auto& c : w) {
        if (c == '(') k++;
        else k--;

        if (k < 0) return false;
    }
    return k == 0;
}


string recursion(string p) {
    // 비어있다면 종료
    if (p == "") return p;

    // 2. 문자열 w를 두 "균형잡힌 괄호 문자열" u, v로 분리
    string u, v;
    int left = 0; int right = 0;
    for (int i = 0; i < p.length(); i++) {
        if (p.at(i) == '(')
            left++;
        else if (p.at(i) == ')')
            right++;
        if (left == right) {
            u = p.substr(0, i + 1);
            v = p.substr(i + 1);
            break;
        }
    }

    // 3. 문자열 u가 "올바른 괄호 문자열" 이라면 문자열 v에 대해 1단계부터 다시 수행합니다. 
    if (isCorrect(u)) return u + recursion(v);

    // 4. 문자열 u가 "올바른 괄호 문자열"이 아니라면
    // 4-1. 빈 문자열에 첫 번째 문자로 '('를 붙인다.
    // 4-2. 문자열 v에 대해 1단계부터 재귀적으로 수행한 결과 문자열을 이어 붙입니다. 
    // 4-3. ')'를 다시 붙입니다.
    string temp = "(" + recursion(v) + ")";
    // 4-4. u의 첫 번째와 마지막 문자를 제거하고, 나머지 문자열의 괄호 방향을 뒤집어서 뒤에 붙입니다. 
    u = u.substr(1, u.length() - 2);
    for (int i = 0; i < u.length(); i++)
        temp = (u[i] == '(') ? temp + ')' : temp + '(';
    // 4-5. 생성된 문자열을 반환합니다.
    return temp;
}

string solution(string p) {
    // 1. 빈 문자열이거나 이미 올바른 문자열이면 p 반환
    if (p.length() == 0 or isCorrect(p)) return p;
    return recursion(p);
}