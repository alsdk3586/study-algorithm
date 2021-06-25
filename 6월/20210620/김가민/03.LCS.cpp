#include<iostream>
#include<algorithm>
#include<fstream>
#include<cmath>

using namespace std;
int LCS[1001][1001];
int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	string A, B;
	cin >> A;
	cin >> B;
	int lenA = A.size();
	int lenB = B.size();

	for (int i = 0; i < lenA; i++)
	{
		for (int j = 0; j < lenB; j++)
		{
			if (A[i] == B[j])
			{
				LCS[i + 1][j + 1] = LCS[i][j] + 1;
			}
			else
			{
				LCS[i + 1][j + 1] = max(LCS[i + 1][j], LCS[i][j + 1]);
			}
		}
	}
	cout << LCS[lenA][lenB] << "\n";

	return 0;
}