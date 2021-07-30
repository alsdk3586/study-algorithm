#include <iostream>
#include <algorithm>

using namespace std;

int main() {
    int N,result=0;
    scanf("%d",&N);

    int arr[N],dp[N];
    for(int i=1;i<=N;i++) {
        scanf("%d",&arr[i]);
    }

    for (int i = 1; i <= N; i++) { //LIS
		dp[i] = 1;
		for (int j = 1; j < i; j++)
			if (arr[j] < arr[i] && dp[i] <= dp[j])
				dp[i] += 1;
        result = max(result, dp[i]);
	}
    printf("%d",N - result);
}