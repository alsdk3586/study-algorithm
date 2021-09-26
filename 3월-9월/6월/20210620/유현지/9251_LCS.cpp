#include <iostream>
#include <algorithm>
#include <string>

int count = 0;
int dp[1'001][1'001];
std::string str1, str2;

int main (int argc, const char * argv []) {
    std::ios::sync_with_stdio(false);
    std::cin >> str1 >> str2;
    
    for (int i = 0; i < 1'001; ++i)
        dp[0][i] = dp[i][0] = 0;
    
    for (int i = 1; i <= str1.size(); ++i) {
        for (int j = 1; j <= str2.size(); ++j) {
            count = std::max({
                dp[i][j - 1],
                dp[i - 1][j],
                dp[i - 1][j - 1] + (str1[i - 1] == str2[j - 1]) });
            
            dp[i][j] = count;
        }
    }
    
    std::cout << dp[str1.size()][str2.size()];
    
    return 0;
}
