#include <iostream>

using namespace std;
#define MAX 301

int N;
int stairs[MAX];
int dp[MAX];
int result=0;

int main() {
    cin >> N;

    for(auto i=0;i<N;i++) 
        cin >> stairs[i];
    
    dp[0] = stairs[0];
    dp[1] = max(stairs[1],stairs[0]+stairs[1]);
    dp[2] = max(stairs[0] + stairs[2],stairs[1]+stairs[2]);

    for(auto i=3;i<N; i++) 
        dp[i] = max(stairs[i] + dp[i-2], stairs[i]+stairs[i-1] +dp[i-3]);

    cout << dp[N-1];
}