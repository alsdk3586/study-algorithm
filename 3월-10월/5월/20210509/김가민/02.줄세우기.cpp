#include<stdio.h>
#include<iostream>
#include<algorithm>
#include<math.h>
#include<string.h>
#include<stdlib.h>

using namespace std;

#define MAX 201

int n;
int arr[MAX];
int length[MAX];

int main()
{
    cin >> n;
    for(int i = 0; i < n; i++)
    {
        cin >> arr[i];
    }
    for(int i = 0; i < n; i++)
    {
        length[i] = 1;
        for(int j = 0; j < i; j++)
        {
            if(arr[j] < arr[i])
            {
                length[i] = max(length[i], length[j]+1);
            }
        }
    }
        int result = 0;
        for(int i =0; i < n; i++) result = max(length[i], result);
        cout << n - result;
    return 0;
}
