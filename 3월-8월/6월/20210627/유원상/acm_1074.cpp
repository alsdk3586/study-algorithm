#include <iostream>

int N, r, c;
int len[16];

int solve(int step, int row, int col) {
    if (step == 0 || row == 0 && col == 0)
        return 0;
    
    int blen = len[--step];
    int count = ((row / blen) * 2 + (col / blen)) * blen * blen;
    
    return count + solve(step, row % blen, col % blen);
}

int main(int argc, const char* argv[]) {
    len[0] = 1;
    for (int i = 1; i < 16; ++i)
        len[i] = len[i - 1] * 2;
        
    std::cin >> N >> r >> c;
    
    std::cout << solve(N, r, c);
    return 0;
}

