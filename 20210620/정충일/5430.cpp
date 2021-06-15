#include <iostream>
#include <deque>
#include <algorithm>

using namespace std;

int T,N;
int inx=0;
bool flag=false;
bool rev=false;
string p;
string arr;
string temp;
deque<string> dq;


void order() {
    if(N==0) {
        if(p[0]=='D') {
            flag=true;
        }
    }
    for(int i=0;i<p.length();i++) {
        if(flag) break;
        if(p[i]=='R') {
            if(rev) {
                rev=false;
            } else rev=true;
        }else if(p[i]=='D') {
            if(dq.size()==0) {
                flag=true;
                break;
            }
            if(rev)
                dq.pop_back();
            else dq.pop_front();
        }else {
            flag=true;
        }
    }
}

void dq_plus() {
    for(int i=1;i<=arr.length();i++) {
        if((arr[i]!=',') && (arr[i]!=']')) {
            inx++;
        } else {
            for(int j=inx;j>0;j--) {
                temp+=arr[i-j];
                }
            dq.push_back(temp);
            inx=0;
            temp="";
        }
    }
    if(dq.size()!=0) {
        order();
    } else flag=true;
}

void reset() {
    inx=0;
    flag=false;
    rev=false;
    p="";
    arr="";
    temp="";
    dq.clear();
}

int main() {
    ios::sync_with_stdio(false);
	cin.tie(0);
    cin >> T;

    while(T--) {
        reset();
        cin >> p;
        cin >> N;
        cin >> arr;
        dq_plus();
        
        if(!flag) {
            cout << "[";
            if(rev) reverse(dq.begin(),dq.end());
            for(int i=0;i<dq.size();i++) {
                cout << dq[i];
                if(i!=dq.size()-1)
                    cout << ",";
            }
            cout << "]\n";
        } else {
            cout << "error\n";
        }
    }
}

