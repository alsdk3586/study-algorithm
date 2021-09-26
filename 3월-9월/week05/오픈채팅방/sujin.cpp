#include <string>
#include <vector>
#include <map>
#include <sstream>

using namespace std;

vector<string> solution(vector<string> record) {
    vector<string> answer;
    vector<vector<string>> logs;  // [Enter / Leave, id]
    map<string, string> nicknames;  // id = nickname
    
    for (auto& rec : record) {
        string state, id, nickname;
        stringstream ss(rec);
        ss >> state >> id >> nickname;
        
        if (state != "Change")
            logs.push_back(vector<string> {state, id});
        if (state != "Leave")
            nicknames[id] = nickname;
    }
    
    for (auto& log : logs) {
        string state = log[0];
        string id = log[1];
        
        if (state == "Enter")
            answer.push_back(nicknames[id] + "님이 들어왔습니다.");
        else 
            answer.push_back(nicknames[id] + "님이 나갔습니다.");
    }
    return answer;
}
