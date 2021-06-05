//오답, 도와주세요

#include <iostream>
#include <vector>
#include <algorithm>
#include <tuple>

using namespace std;
#define MAX 200001

int M,N;
int parent[MAX];
vector<tuple<int,int,int>> v;

int find(int x) {
    if(parent[x]==x) return x;
    else return parent[x]=find(parent[x]);
}

void connection(int x,int y) {
    x=find(x);
    y=find(y);
    if(x!=y) {
        parent[x]=y;
    }
}

bool same(int x,int y) {
    x=find(x);
    y=find(y);
    if(x==y) return true;
    else return false;
}

int main() {
    cin >> M >> N;
    while(M && N) {
        while(!v.empty()) v.pop_back();
        long long result=0;
        long long total=0;

        for(int i=0;i<=M;i++) {
            parent[i]=i;
        }

        for(int i=0;i<N;i++) {
            int x,y,z;
            cin >> x >> y >> z;
            total+=z;
            v.push_back({z,x,y});
        }

        sort(v.begin(),v.end());

        for(int i=0;i<N;i++) {
        if(!same(get<1>(v[i]), get<2>(v[i]))) {
            connection(get<1>(v[i]), get<2>(v[i]));
            result +=get<0>(v[i]);
        }
    }

        cin >> M >> N;
        
        cout << total-result;
        }
}