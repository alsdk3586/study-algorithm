# 후보키



### 문제

> __데이터베이스에서 후보키의 최대 개수를 구하라__
>
> 후보키
>
> 	- 유일성 : 투플에 대해 유일하게 식별되어야한다.
> 	- 최소성 : 유일성을 가진 키를 구성하는 속성 중 하나라도 제외하는 경우 유일성을 깨지는 것을 의미한다. 즉, 릴ㄹ레이션의 모든 튜플을 유일하게 식별하는데 꼭 필요한 속성들로만 구성되어야한다. 



### 제한 사항

> 칼럼의 길이는 1이상 8이하
>
> 로우의 길이는 1이상 20이상
>
> 모든 문자열의 길이는 1이상 8이하



### Solution 

> 1. 열마다의  모든 조합 찾기 : `make` 함수
> 2. 찾은 조합의 유일성 판단  : `count` 함수
> 3. 유일성을 만족한 것 중에 최소성을 만족하는 것의 개수 세기 :`check` 함수



### 코드 

> 왜인지 모르게 sort를 주석처리하니깐 모두 정답처리가 되었다. 

```c++
#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <algorithm>
using namespace std;

typedef struct a {
	int c;
	int a[10];
}a;
int compare(a c, a b) {
	if (c.a > b.a)
		return 1;
	return 0;
}
vector<a> answer;
int count(vector<vector<string>> relation, vector<int> list) {
	map<string, int> m;
	for (int i = 0; i < relation.size(); i++) {
		string a = "";
		for (int j = 0; j < list.size(); j++) {
			a += relation[i][list[j]];
		}
		if (m.find(a) == m.end())
			m[a] = 1;
		else
			return 0;
	}
	return 1;
}
void make(vector<vector<string>> relation, int i, vector<int> list) {
	if (i == relation[0].size()) {
		if (count(relation, list)) {
			a b = { 0 };
			for (int k = 0; k < list.size(); k++) {
				b.a[list[k]] = 1;
			}
			answer.push_back(b);
		}
		return;
	}
	make(relation, i + 1, list);
	list.push_back(i);
	make(relation, i + 1, list);
}
int check(int i, int j,int n) {
	for (int k = 0; k < n; k++) {
		if (answer[i].a[k] == answer[j].a[k]) {
			continue;
		}
		else if (answer[j].a[k] == 1) {
			continue;
		}
		else {
			return 0;
		}
	}
	return 1;
}
int solution(vector<vector<string>> relation) {
	vector<int>list;
	answer .clear();
	make(relation, 0, list);

	int ans = 1;
	//sort(answer.begin(), answer.end(),compare);
	for (int i = 0; i < answer.size(); i++) {
		if (answer[i].c == 1)
			continue;
		for (int j = i+1; j < answer.size(); j++) {
			if (answer[j].c == 1)
				continue;
			if (check(i, j, relation[0].size()))
				answer[j].c = 1;
		}
	}
	for (int i = 1; i < answer.size(); i++) {
		if (answer[i].c == 0)
			ans++;
	}
	return ans;
}
```

