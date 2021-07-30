#include<iostream>
#include<algorithm>
#include<fstream>
#include<cstring>
#include<string>
#include<vector>

using namespace std;

// 전역 변수를 정의할 경우 함수 내에 초기화 코드를 꼭 작성해주세요.
int solution(int n, vector<string> data) {
	int answer = 0;
	vector<string> arr = { { "A", "C", "F", "J", "M", "N", "R", "T" } };
	string friend1, friend2, calc;
	int val, leftIndex, rightIndex, dis;

	do
	{
		answer++;

		for (int i = 0; i < n; i++)
		{
			bool check = true;
			leftIndex = 0, rightIndex = 0, dis = 0;
			friend1 = data[i][0];
			friend2 = data[i][2];
			calc = data[i][3];
			val = data[i][4] - '0';

			for (int j = 0; j < 8; j++)
			{
				if (arr[j] == friend1)
					leftIndex = j;
				else if (arr[j] == friend2)
					rightIndex = j;
			}

			dis = leftIndex > rightIndex ? (leftIndex - rightIndex - 1) : (rightIndex - leftIndex - 1);

			if (calc.compare("=") == 0)
			{
				if (dis == val)
					check = true;
				else
					check = false;
			}
			else if (calc.compare(">") == 0)
			{
				if (dis > val)
					check = true;
				else
					check = false;

			}
			else if (calc.compare("<") == 0)
			{
				if (dis < val)
					check = true;
				else
					check = false;
			}
			if (!check)
			{
				answer--;
				break;
			}
		}

	} while (next_permutation(arr.begin(), arr.end()));

	return answer;
}