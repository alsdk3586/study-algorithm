#include <iostream>
#include <cmath>

int N, r, c, num;

void solve(int y, int x, int div) {
    
    if (div == 1)
        return;
    
    div /= 2;
    
    if (y < div && x < div) {
        solve(y, x, div);
    }
    else if (y < div && x >= div) {
        num += (div * div);
        solve(y, x - div, div);
    }
    else if (y >= div && x < div) {
        num += (div * div * 2);
        solve(y - div, x, div);
    }
    else if (y >= div && x >= div) {
        num += (div * div * 3);
        solve(y - div, x - div, div);
    }
    
}

int main (int argc, const char * argv []) {
    
    std::scanf("%d %d %d", &N, &r, &c);
    
    num = 0;
    solve(r, c, std::pow(2, N));
    
    std::printf("%d", num);
    
    return 0;
}
