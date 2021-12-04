#include <iostream>

using namespace std;

int T,indx,check;
string s1,s2;

int main() {
    ios_base::sync_with_stdio(0);
	cin.tie(0);

    cin>> T;

    while(T--) {
        check=0; indx=0; //초기화
        cin >> s1; //값 입력받기
        s2=s1; //복사본 생성
        
        for(int i=0;i<s1.length()/2;i++) { // 검사
            if(s1[i] != s1[s1.length() -i -1]) {
                check=2; indx=i; // 대칭이 아니면 해당 인덱스를 저장하고 체크표시
                break;
            }
        }

        if(!check) cout << "0\n"; // 체크 표시가 안 되어 있다면 회문
        else {
            check=0; //초기화
            int check1=0,check2=0;
            int indx2=s1.length() -indx -1; // 해당 인덱스의 반대편 인덱스 위치 저장
            s1.erase(indx,1); s2.erase(indx2,1); // 대칭이 아닌 요소 지우기

            for(int i=0;i<s2.length()/2;i++) { // 검사
                if(s2[i] != s2[s2.length() -i -1])
                    check1=2;
                if(s1[i] != s1[s1.length() -i -1])
                    check2=2;
            }
            if(check1+check2==4) check=2;

            if(!check) cout << "1\n"; // 체크 표시가 안 되어 있다면 유사회문
            else cout << "2\n";  // 그 외
        }
    }
}