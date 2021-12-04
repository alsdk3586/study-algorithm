#include <iostream>
#include <string>
#include <vector>

using namespace std;

#define get(arr, x) (((arr[x >> 6] >> (x & 63)) & 1) == 1)
#define set(arr, x) (arr[x >> 6] |= 1llu << (x & 63))

typedef unsigned long long ulli;

int lcs(const string& s1, const string& s2) {
    int N = s1.size();
    int M = s2.size();
    int cap = (M >> 6) + 1;

    vector<vector<ulli>> table(256, vector<ulli>(cap, 0));
    for (int i = 0; i < M; i++)
        set(table[s2[i]], i);

    vector<ulli> row(cap);
    for (int i = 0; i < M; i++)
    {
        if (s1[0] == s2[i])
        {
            set(row, i);
            break;
        }
    }

    for (int i = 1; i < N; i++)
    {
        ulli carry = 1;
        ulli negative_carry = 0;

        for (int j = 0; j < cap; j++)
        {
            ulli xprime = table[s1[i]][j] | row[j];
            ulli t1 = (row[j] << 1) | carry;
            carry = row[j] >> 63;

            auto sub_carry = [](ulli& x, ulli y) {
                ulli tmp = x;
                return (x = tmp - y) > tmp;
            };

            ulli t2 = xprime;
            negative_carry = sub_carry(t2, negative_carry);
            negative_carry += sub_carry(t2, t1);

            row[j] = xprime & (xprime ^ t2);
        }

        row[M >> 6] &= (1llu << (M & 63)) - 1;
    }

    int ret = 0;
    for (int j = 0; j < M; j++)
    {
        if (get(row, j))
            ret++;
    }
    return ret;
}

int main(void)
{
    string s1, s2;
    getline(cin, s1);
    getline(cin, s2);

    cout << lcs(s1, s2) << endl;
}
