```
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include<algorithm>
using namespace std;

typedef struct A {
	int id;
	double score;
};
int compare(A a, A b) {
	if (a.score > b.score)
		return 1;
	else if (a.score == b.score) {
		if (a.id < b.id)
			return 1;
	}
	return 0;
}
vector<int> solution(int N, vector<int> stages) {
	vector<int> answer;
	int stagelist[510] = { 0 };
	
	for (int i = 0; i < stages.size(); i++) {
		stagelist[stages[i]]++;
	}


	vector<A> list;
	int amount = stagelist[N+1];
	for (int i = N; i > 0; i--) {
		amount += stagelist[i];
		if(amount==0)
			list.push_back({ i, 0 });
		else
			list.push_back({ i, (double)stagelist[i] / amount });
	}
	sort(list.begin(), list.end(), compare);
	for (int i=0; i < list.size(); i++) {
		answer.push_back(list[i].id);
	}
	return answer;
}
```

