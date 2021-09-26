#include <iostream>
#include <algorithm>

using namespace std;

string st1, st2;
int dp[1001][1001];


int main() {
    cin >> st1 >> st2;

    int len1= st1.size();
    int len2= st2.size();
	
    for(int i=1; i<=len2; i++) {
		for (int j = 1; j <= len1; j++) {
			if (st2[i - 1] == st1[j - 1])
				dp[i][j] = dp[i - 1][j - 1] + 1;
			else
				dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
		}
    }
	cout << dp[len2][len1];
}