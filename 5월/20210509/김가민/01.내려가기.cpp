#include<stdio.h>
#include<iostream>
#include<algorithm>
#include<math.h>
#include<string.h>
#include<stdlib.h>

using namespace std;

int main(void)
{
	
    int n, maxDP[3] = {0, 0, 0}, minDP[3] = {0, 0, 0}, input[3], temp_0, temp_1;
	
    scanf("%d", &n);
    scanf("%d %d %d", &maxDP[0], &maxDP[1], &maxDP[2]);

	
    minDP[0] = maxDP[0];
    minDP[1] = maxDP[1];
    minDP[2] = maxDP[2];
    
    for(int i = 1; i < n; i++)
    {
        scanf("%d %d %d", &input[0], &input[1], &input[2]);
        temp_0 = maxDP[0];
        temp_1 = maxDP[1];
        
        maxDP[0] = max(maxDP[0], maxDP[1]) + input[0];
        maxDP[1] = max(max(temp_0, maxDP[1]), maxDP[2]) + input[1];
        maxDP[2] = max(temp_1, maxDP[2]) + input[2];
        
        temp_0 = minDP[0];
        temp_1 = minDP[1];
        
        minDP[0] = min(minDP[0], minDP[1]) + input[0];
        minDP[1] = min(min(temp_0, minDP[1]), minDP[2]) + input[1];
        minDP[2] = min(temp_1, minDP[2]) + input[2];
         
    }
    
    printf("%d ", (max(max(maxDP[0], maxDP[1]), maxDP[2])));
    printf("%d", (min(min(minDP[0], minDP[1]), minDP[2])));
    
 return 0;
}
