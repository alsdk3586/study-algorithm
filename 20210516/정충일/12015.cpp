#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int a;
vector<int> arr;

int main() {
    cin >> a;

    for (int i = 0; i < a; i++) {
        int input;
        cin >> input;
        if (arr.empty() || arr.back() < input) {
            arr.push_back(input);
        } else {
            *lower_bound(arr.begin(), arr.end(), input) = input;
        }
    }
    cout << arr.size();
}