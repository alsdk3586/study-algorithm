#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int n,temp,index,len;
int a[1001],dp[1001];
vector<int> arr;

int main() {
    cin >> n;

    for(int i=1;i<=n;i++) {
        cin >> a[i];
        len=0;

        for(int j=1;j<i;j++) {
            if(a[i]>a[j])
                len=max(dp[j],len);
        }
        dp[i]=len+1;

        if(temp<dp[i]) {
            temp = dp[i];
            index = i;
        }
    }

    for(int i=index;i>=1;i--) {
        if(temp==dp[i]) {
            arr.push_back(a[i]);
            temp--;
        }
    }

    int size=arr.size();
    cout <<size<<"\n";

    for(int i=0;i<size;i++) {
        cout << arr.back()<<" ";
        arr.pop_back();
    }
}