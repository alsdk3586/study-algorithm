#include<iostream>

#include<queue>

using namespace std;

int N;
queue<int> decreaseNum;

int main() {
    cin>>N; 

	if(N <= 10){
		cout<<N;
	}
	else if(N == 1022)
		cout<<9876543210;
	else if(N >= 1023)
		cout<<-1;
	else{
        int i, j, tmp;
        int cnt=0;

		for(i=1; i<10; i++){
			decreaseNum.push(i);
			cnt++;
		}
		while(cnt < N){
			i = decreaseNum.front();
			decreaseNum.pop();
			tmp = i%10;

			for(j = 0; j<tmp; j++){
				decreaseNum.push(i*10 + j);
				cnt++;

				if(cnt == N){
					cout<<i*10 + j;
					break;
				}
			}
		}
	}
}