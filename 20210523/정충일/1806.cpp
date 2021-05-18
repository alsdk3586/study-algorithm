#include <iostream>
#include <algorithm>

using namespace std;

int n,m;

int main() {
    cin >> n >> m;

    int a[n+1];

    for(int i=0;i<n;i++) {
        cin >> a[i];
    }

    int start=0,end=0;
    int result = a[0];
    int len=100001;

    while(start<=end && end<n) {
        if(result<m) {
            result+=a[++end];
        } else if(result>=m) {
            len=min(end-start+1,len);
            result -=a[start++];
            if(start>end) {
                end = start;
                result = a[start];
            }
        }
    }

    if(len==100001) {
        len=0;
        cout << len;
    } else cout << len;
}