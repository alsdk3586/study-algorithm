#include <iostream>
#include <vector>
#include <queue>
using namespace std;

typedef struct node {
    int i;
    int j;
};
vector<vector<int>> list = { {0,0,0,0},{0,1,0,0},{0,1,0,1},{1,1,0,0}, {1,1,0,1},{1,1,1,1} };
int dx[] = {-1,0,1,0 };
int dy[] = {0,1,0,-1 };
int N, M;
int max_check;
vector<int> shift(vector<int> i) {
    vector<int> k;

    k.push_back(i[3]);
    k.push_back(i[0]);
    k.push_back(i[1]);
    k.push_back(i[2]);

    return k;
}
void dfs(vector<vector<int>> map, int check, queue<node> qu) {
    if (qu.empty()) {
        if (max_check < check)
            max_check = check;
        return;
    }
    node value = qu.front();
    qu.pop();
    int k = map[value.i][value.j];
    vector<int> key = list[k];
    int n = value.i;
    int m = value.j;
    for (int i = 0; i < 4; i++) {
        int check1 = check;
        vector<vector<int>> map1 = map;
        for (int j = 0; j < 4; j++) {
            if (key[j] == 1) {
                n = value.i;
                m = value.j;
                while (1) {
                    n += dx[j];
                    m += dy[j];
                    if (n >= 0 && n < N && m >= 0 && m < M) {
                        if (map1[n][m] == 6)
                            break;
                        if (map1[n][m] == 0) {
                            check1++;
                            map1[n][m] = 7;
                        }
                    }
                    else
                        break;
                }
            }
        }
        dfs(map1, check1, qu);
        key = shift(key);
    }
}

int main() {

 
    cin >> N >> M;
    vector<vector<int>> map;
    int check = 0;
    queue<node> qu;
    for (int i = 0; i < N; i++) {
        vector<int> a;
        map.push_back(a);
        for (int j = 0; j < M; j++) {
            int k;
            cin >> k;
            if (k == 0)
                check++;
            if (k != 0 && k != 6)
                qu.push({ i,j });
            map[i].push_back(k);
        }
    }
    dfs(map, 0, qu);
    cout << check - max_check;


   
    return 0;
}

