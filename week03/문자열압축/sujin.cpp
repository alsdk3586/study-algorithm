#include <string>
#include <vector>

using namespace std;

int solution(string s) {
    int answer = s.size();  // 1개 단위로 압축했을 때의 길이
    int unit = 1;  // 문자열을 압축하는 단위
    string compressedString = "";  // 압축된 s

    // 최대 s의 길이의 반까지 압축 가능함
    while (unit <= s.size() / 2) {
        int commonCnt = 1;  // 압축된 수
        int cursor = 0;
        while (cursor + unit <= s.size()) {
            // 압축 가능한 경우
            // commonCnt 를 늘린다.
            if (s.substr(cursor, unit) == s.substr(cursor + unit, unit)) {
                commonCnt++;
            }
                // 압축 불가능한 경우
                // 이미 반복된 적이 있으면 compressedString에 압축된 string을 추가하고 commonCnt를 초기화 한다.
            else if (commonCnt >= 2) {
                compressedString += to_string(commonCnt) + s.substr(cursor, unit);
                commonCnt = 1;
            }
                // 반복된 적이 없는 경우 문자열을 추가한다.
            else {
                compressedString += s.substr(cursor, unit);
            }
            // unit 만큼 cursor를 이동한다.
            cursor += unit;
        }
        // 문자열 끝까지 추가
        compressedString += s.substr(cursor, s.size() - cursor);
        answer = (compressedString.size() < answer) ? compressedString.size() : answer;
        compressedString = "";
        unit++;
    }

    return answer;
}