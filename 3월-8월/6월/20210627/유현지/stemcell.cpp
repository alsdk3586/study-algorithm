#include <iostream>
#include <vector>

int T, N, M, K;
std::vector<std::vector<int>> v, copyv;

void init() {
    N = M = K = 0;
    v.clear();
    copyv.clear();
}

void input() {
    std::scanf("%d %d %d", &N, &M, &K);
    
    v.resize(N);
    for (int i = 0; i < N; ++i)
    v[i].resize(M);
    
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            std::scanf("%d", &v[i][j]);
        }
    }
    
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            if (v[i][j] == 0)
                v[i][j] = -3;
        }
    }
    
    copyv = v;
}


void addcell(int y, int x) {
    int offset[4][2] = { {-1, 0}, {0, 1}, {1, 0}, {0, -1} };
    int copynum = copyv[y][x];
    
    for (int i = 0; i < 4; ++i) {
        int dy = y + offset[i][0];
        int dx = x + offset[i][1];
        
        if (v[dy][dx] == -3)
            v[dy][dx] = copyv[dy][dx] = copynum;
        else if (v[dy][dx] > 0)
            v[dy][dx] = (v[dy][dx] > copynum) ? v[dy][dx] : copynum;
    }
}


void expandcell() {
    
    int height = (int)v.size();
    int width = (int)v[0].size();
    
    v.resize(height + 2);
    copyv.resize(height + 2);
    for (int i = 0; i < v.size(); ++i) {
        v[i].resize(width + 2);
        copyv[i].resize(width + 2);
    }
    
    for (int i = 0; i < v.size(); ++i) {
        for (int j = 0; j < v[0].size(); ++j) {
            if (0 <= i && i < height && 0 <= j && j < width) continue;
            v[i][j] = -3;
        }
    }
    
    for (int i = height - 1; i >= 0; --i) {
        for (int j = width - 1; j >= 0; --j) {
            v[i + 1][j + 1] = v[i][j];
            copyv[i + 1][j + 1] = copyv[i][j];
            
            v[i][j] = -3;
            copyv[i][j] = 0;
        }
    }
}



void solve() {
    
    int step = 1;
    while (step <= K) {
        
        for (int i = 0; i < v.size(); ++i) {
            for (int j = 0; j < v[i].size(); ++j) {
                if (v[i][j] != -3 && v[i][j] != -2)
                    --v[i][j];
            }
        }
        
        bool flag = false;
        for (int i = 0; i < v.size(); ++i) {
            for (int j = 0; j < v[i].size(); ++j) {
                if (v[i][j] == -1) {
                    expandcell();
                    flag = true;
                    break;
                }
            }
            if (flag) break;
        }
        
        
        for (int i = 0; i < v.size(); ++i) {
            for (int j = 0; j < v[i].size(); ++j) {
                if (v[i][j] == -1)
                    addcell(i, j);
            }
        }
        
        ++step;
    }
    
}


void output() {
    
    int count = 0;
    for (int i = 0; i < v.size(); ++i)
        for (int j = 0; j < v[i].size(); ++j)
            if (v[i][j] > 0)
                ++count;
    
    std::printf("%d", count);
}


int main (int argc, const char * argv []) {
    
    std::scanf("%d", &T);
    
    for (int i = 0; i < T; ++i) {
        init();
        input();
        solve();
        output();
    }
    
    return 0;
}
