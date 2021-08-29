#include <string>
#include <vector>
#include <algorithm>
using namespace std;


int solution(vector<string> words) {
    int ans=1, pre=0;

    sort(words.begin(), words.end());

    string pre_word=words[0]; //정렬된 첫번째 단어

    for (int cur=1;cur<words.size();cur++) {//단어 개수만큼 반복
        int idx = 0;

        for (;idx<=words[cur].size();idx++) { //입력된 단어 순서대로
            if (idx>=pre_word.size()) { //현재 idx가 이전 단어보다 크다면
                ans+=pre_word.size()-pre-1;
                ans+=idx+1;
                break;
            }
            if(words[cur][idx] != pre_word[idx]) { //현재 단어랑 이전 단어 스펠링이 다르다면
                if (idx>pre) ans+=idx-pre;
                ans+=idx+1;
                break;
            }
        }

        pre=idx;
        pre_word=words[cur];
    }
    return ans;
}