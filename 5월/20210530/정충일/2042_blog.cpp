//https://hugssy.tistory.com/132

#include<iostream>
#define MAX 10000002
using namespace std;
 
typedef long long ll;
ll idxTree[4 * MAX];
 
void Update(int idx, ll delta) {
    while (idx > 0) {
        idxTree[idx] += delta;
        idx /= 2;
    }
}
 
ll findSum(int st, int en) {
    ll ret = 0;
    while (st < en) {
        if (st % 2 == 1) ret += idxTree[st];
        if (en % 2 == 0) ret += idxTree[en];
        st = (st + 1) / 2;
        en = (en - 1) / 2;
    }
    ret += idxTree[st];
    return ret;
}
 
int main(void) {
    long long n, m, k;
    cin >> m >> k;
    n = 1000;
    long long start = 1;
    while (start < n) {
        start *= 2; //n보다 큰 가장 작은 2의 제곱수
    }
    
    for (int i = 0; i < n; i++) { //원래 빈공간도 채워줘야 한다. 쿼리에 영향을 받지 않는 값으로
       // cin >> idxTree[start + i];
        idxTree[start + i] = i + 1;
    }
    //트리의 아래에서 위로 채워가기
    for (int i = start - 1; i >= 1; i--) {
        idxTree[i] = idxTree[2 * i] + idxTree[2 * i + 1];
    }
    for (int i = 0; i < m + k; i++) {
        int a, b, c;
        cin >> a >> b >> c; //두 경우 모두 인덱스를 계산해서 넘겨야함, 차이는 새거-있던거
        if (a == 1) Update(b + start - 1, c - idxTree[b + start - 1]);
        else if (a == 2) cout << findSum(b + start - 1, c + start - 1) << '\n';
    }
    return 0;
}
