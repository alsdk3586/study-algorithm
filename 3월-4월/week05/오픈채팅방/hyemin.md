```c++
#include <iostream>
#include <string>
#include <vector>
#include <map>
using namespace std;

typedef struct A {
	string id;
	string name;
};

vector<string> solution(vector<string> record) {
	vector<string> answer;
	map<string, string> id_list;
	vector<A> records;

    int point = 0;
    while (point < record.size()) {
    	string list[3];
    	int p = 0;
    	for (int i = 0; i < record[point].length(); i++) {
    		if (record[point][i] == ' ') {
    			p++;
    			continue;
    		}
    		list[p] += record[point][i];
    	}
    	if (list[0] == "Enter") {
    		if (!id_list.empty()) {
    			auto pp = id_list.find(list[1]);
    			if (pp == id_list.end()) {
    				id_list.insert(make_pair(list[1], list[2]));
    			}
    			else {
    				if (pp->second != list[2])
    					pp->second = list[2];
    			}
    		}
    		else {
    			id_list.insert(make_pair(list[1], list[2]));
    		}
    		records.push_back({ list[1],"님이 들어왔습니다." });
    	}
    	if (list[0] == "Leave") {
    		records.push_back({ list[1],"님이 나갔습니다." });
    	}
    	if (list[0] == "Change") {
    		auto pp = id_list.find(list[1]);
    		if (pp->second != list[2])
    			pp->second = list[2];
    	}
    	point++;
    }
    point = 0;
    while (point < records.size()) {
    	string a = "";
    	auto pp = id_list.find(records[point].id);
    	a += pp->second;
    	a += records[point].name;
    	answer.push_back(a);
    	point++;
    }

    return answer;

}

```

