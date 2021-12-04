#include <string>
#include <vector>
#include <algorithm>
#include <cctype>

using namespace std;

string solution(string new_id) {
	string answer = "";

	// 1단계
	std::transform(new_id.begin(), new_id.end(), new_id.begin(), (int(*)(int))tolower);

	// 2단계
	for (int i = 0; i < new_id.length();) {
		if (isalpha(new_id[i]) || (new_id[i] >= '0' && new_id[i] <= '9') ||
			new_id[i] == '-' || new_id[i] == '_' || new_id[i] == '.') {
			i++;
			continue;
		}
		new_id.replace(i, 1, "");
	}

	// 3단계
	for (int i = 0; i < new_id.length() - 1;) {
		if (new_id[i] == '.' && new_id[i + 1] == '.') {
			new_id.replace(i, 2, ".");
			continue;
		}
		i++;
	}

	// 4단계
	if (new_id[0] == '.')
		new_id.replace(0, 1, "");

	if (new_id[new_id.length() - 1] == '.')
		new_id.replace(new_id.length() - 1, 1, "");

	// 5단계
	if (new_id.length() == 0)
		new_id = "a";


	// 6단계
	if (new_id.length() >= 16)
		new_id = new_id.substr(0, 15);

	if (new_id[new_id.length() - 1] == '.')
		new_id.replace(new_id.length() - 1, 1, "");

	// 7단계
	if (new_id.length() <= 2) {
		while (new_id.length() != 3) {
			new_id += new_id[new_id.length() - 1];
		}
	}

	answer = new_id;

	return answer;
}