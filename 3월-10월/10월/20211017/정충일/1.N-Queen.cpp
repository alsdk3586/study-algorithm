#include <iostream>

using namespace std;

int N;
int result=0;
int chess[16][16];
int dy[3]= {-1,-1,-1};
int dx[3]= {-1,0,1};

int down(int y,int x) {
    for (int i=0;i<3;i++) {
        int ny=y;
        int nx=x;

        while(true) {
            ny = ny+dy[i];
            nx = nx+dx[i];

            if(nx <0 || nx>=N || ny<0 || ny>=N)
                break;
            if(chess[ny][nx]==1)
                return false;
        }
    }
    return true;
}

void tooo1(int j) {
    if(j==N) {
        result++;
        return;
    }
    for (int i=0;i<N;i++) {
        if(down(j,i) && chess[j][i]==0) {
            chess[j][i]=1;
            tooo1(j+1);
            chess[j][i]=0;
        }
    }
}

int main() {
    cin>>N;
    tooo1(0);
    cout << result;
}