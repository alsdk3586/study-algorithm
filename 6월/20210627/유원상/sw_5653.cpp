#include <iostream>
#include <queue>
#include <cstring>

int dy[] = {-1, 0, 1, 0};
int dx[] = {0, 1, 0, -1};

struct coord_t {
    
    coord_t(int y, int x):y(y), x(x) {};
    int y, x;
};

int cell_type[1000][1000];
int cell_life[1000][1000];
std::queue<coord_t> act, deact;

int T, N, M, K;

enum state { activate_point = 0, dead, alive, empty, added };

state get_state(int y, int x) {
    if (cell_type[y][x] == 0)
        return state::empty;
    else if (cell_life[y][x] == 0)
        return state::activate_point;
    else if (cell_life[y][x] == -cell_type[y][x])
        return state::added;
    else if (cell_life[y][x] == cell_type[y][x])
        return state::dead;
    else
        return state::alive;
}

void init() {
    std::memset((void*)cell_type, 0, sizeof cell_type);
    std::memset((void*)cell_life, 0, sizeof cell_type);
    act = std::queue<coord_t>();
    deact = std::queue<coord_t>();
}

void input() {
    std::cin >> N >> M >> K;
    
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            int y = i + 500;
            int x = j + 500;
            int life;
            std::cin >> life;
            
            cell_type[y][x] = life;
            cell_life[y][x] = -life;
            
            if (get_state(y, x) != state::empty)
                deact.emplace(y, x);
        }
    }
}

void solve() {
    while (K--) {
        int dsize = (int)deact.size();
        int asize = (int)act.size();
        
        while (dsize--) {
            auto c = deact.front();
            deact.pop();
            
            ++cell_life[c.y][c.x];
            
            if (get_state(c.y, c.x) == state::activate_point)
                act.push(c);
            else
                deact.push(c);
        }
        
        while (asize--) {
            auto c = act.front();
            act.pop();
            
            for (int i = 0; i < 4; ++i) {
                coord_t n(c.y + dy[i], c.x + dx[i]);
                
                switch (get_state(n.y, n.x)) {
                    case state::empty: {
                        cell_type[n.y][n.x] = cell_type[c.y][c.x];
                        cell_life[n.y][n.x] = -cell_type[n.y][n.x];
                        deact.push(n);
                        break;
                    }
                    case state::added: {
                        cell_type[n.y][n.x] = std::max(
                            cell_type[n.y][n.x],
                            cell_type[c.y][c.x]
                        );
                        cell_life[n.y][n.x] = -cell_type[n.y][n.x];
                        break;
                    }
                    default:
                        break;
                }
            }
            
            ++cell_life[c.y][c.x];
            
            if (get_state(c.y, c.x) == state::alive)
                act.push(c);
        }
    }
}

void output(int t) {
    std::cout << "#" << t << " " << act.size() + deact.size() << "\n";
}

int main(int argc, const char* argv[]) {
    
    std::cin >> T;
    
    for (int t = 1; t <= T; ++t) {
        init();
        input();
        solve();
        output(t);
    }
    return 0;
}
