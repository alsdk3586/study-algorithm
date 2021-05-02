#include<string>
#include <iostream>

#include <stack>


using namespace std;

bool solution(string s)
{
    std::stack<char> st;

    for(auto itr = s.begin(); itr != s.end(); itr++) {
        // if stack is empty, put it 
        if(st.empty()) {
            st.push(*itr);
            continue;
        }
        
        // if stack.top is '(' and *itr is ')', pop '(' 
        if(st.top() == '(' && *itr == ')')
            st.pop();
        else
            st.push(*itr);

    }

    return st.empty();
}


int main() {
    std::string input("(())()");
    std::cout << std::boolalpha << solution(input) << std::endl;
    
    return 0;
}