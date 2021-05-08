#include <iostream>
#include <algorithm>

using namespace std;

int main(void)
{
    int N;
    int v1, v2, v3, tv1, tv2, tv3;
    int table[2][3] = { 0, };
    
    cin >> N;
    
    while (N--)
    {
        cin >> v1 >> v2 >> v3;
        
        tv1 = table[0][0], tv2 = table[0][1], tv3 = table[0][2];
        table[0][0] = v1 + min(tv1, tv2);
        table[0][1] = v2 + min(tv1, min(tv2, tv3));
        table[0][2] = v3 + min(tv2, tv3);
        
        tv1 = table[1][0], tv2 = table[1][1], tv3 = table[1][2];
        table[1][0] = v1 + max(tv1, tv2);
        table[1][1] = v2 + max(tv1, max(tv2, tv3));
        table[1][2] = v3 + max(tv2, tv3);
    }
    
    cout << max(table[1][0], max(table[1][1], table[1][2])) << endl;
    cout << min(table[0][0], min(table[0][1], table[0][2])) << endl;
}
