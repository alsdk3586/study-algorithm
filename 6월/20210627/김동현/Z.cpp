#include <iostream>
#include <math.h>
#define LOG2(x) (int)(log(x) / log(2))
#define POW(x, y) (int)pow(x, y)

using namespace std;

int main(void)
{
	int N, r, c, l, answer = 0;
	cin >> N >> r >> c;

	while (r > 1 || c > 1) {
		answer += r > 1 ? POW(4, l = LOG2(r)) * 2 : 0, r -= (r > 1 ? POW(2, l) : 0);
		answer += c > 1 ? POW(4, l = LOG2(c)) : 0, c -= (c > 1 ? POW(2, l) : 0);
	}

	cout << answer + r * 2 + c << endl;

	return 0;
}
