#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int N;
int cnt =0;
string word;
vector<char> temp;
bool flag=false;

void reset() {
    temp.clear();
    flag=false;
}

int main() {
    cin >> N;

    for(int i=0;i<N;i++) {
        cin >> word;
        for(int j=0;j<word.size();j++) {
            if(find(temp.begin(),temp.end(),word[j]) != temp.end()) {
                if(temp.back() != word[j]) {
                    flag=true;
                    break;
                }
            } else {
                char x = word[j];
                temp.push_back(x);
            }
        }
        if(!flag) cnt++;
        reset();
    }
    cout << cnt;
}