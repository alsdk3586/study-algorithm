#include <iostream>
#include <algorithm>

using namespace std;
#define MAX 3000001

int N,d,k,c;
int arr[MAX];
int visited[MAX];

int main() {
    cin >> N >> d >> k >> c;

    //초밥 종류 입력 받기
    for(int i=0;i<N;i++)
        cin >> arr[i];
    
    int total =0;
    int max=0;

    //종류의 개수 세기
    for(int i=0;i<k;i++) {
        if(visited[arr[i]]==0) total++;
        visited[arr[i]]++;
    }
    max=total;

    for(int i=1;i<N;i++) {
        if (max <=total) { 
            if(visited[c]==0) max=total+1; //쿠폰 확인
            else max = total;
       }
       visited[arr[i-1]]--;
       if(visited[arr[i-1]]==0) total--;

       if(visited[arr[(i+k-1)%N]]==0) total++;
       visited[arr[(i+k-1)%N]]++;
    }

    cout << max;

}