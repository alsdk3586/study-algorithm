#include <iostream>
#include <vector>

using namespace std;

int N;
int arr[11];
vector<int> v;

int main() {
    cin >> N;

    for(int i=0;i<N;i++) 
        cin >> arr[i];
    

    for(int i=N-1;i>=0;i--) {
        vector<int>::iterator iter=v.begin();
        for(int j=0;j<arr[i];j++) 
            iter++;
        v.insert(iter,i+1);
    }    

    for(int i=0;i<v.size();i++)
        cout << v[i] << " ";
}