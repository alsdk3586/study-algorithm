#include <string>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

bool check(int order[], int n, vector<string> data)
{
    for (int i = 0; i < n; ++i)
    {
        string d = data[i];
        int distance = abs(order[d[0] - 'A'] - order[d[2] - 'A']) - 1;

        if (!(d[3] == '=' && distance == d[4] - '0')
            && !(d[3] == '>' && distance > d[4] - '0')
            && !(d[3] == '<' && distance < d[4] - '0'))
        {
            return false;
        }
    }

    return true;
}

int solution(int n, vector<string> data) {

    char perm[8] = { 'A', 'C', 'F', 'J', 'M', 'N', 'R', 'T' };
    int cnt = 0;

    do {
        int order[26] = { 0, };
        for (int i = 0; i < 8; ++i)
        {
            order[perm[i] - 'A'] = i + 1;
        }

        if (check(order, n, data))
        {
            ++cnt;
        }

    } while (next_permutation(perm, perm + 8));

    return cnt;
}