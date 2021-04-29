#include <iostream>
#include <string>

using namespace std;


bool solution(string arr) {
    int count =0 ;
    for(int i = 0; i<arr.length();i++) {
        if(arr[i]=='(') {
            count++;
        } else if (arr[i]==')') {
            count--;
            if(count<0) {
                return false;
                break;
            }
        }
    }
    if(count==0) {
        return true;
    } else {
        return false;
    }

}
