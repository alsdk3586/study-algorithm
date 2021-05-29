// 세그먼트 트리 참고
// https://yabmoons.tistory.com/431

// 아래 코트
// https://yabmoons.tistory.com/432

#include<iostream>
#include<vector>
#include<cmath>
 
typedef long long ll;
using namespace std;
 
int N, M, K;
vector<ll> Arr;
vector<ll> Tree_Array;
vector<pair<int, pair<int, ll>>> Cmd;
 
void Input()
{
    cin >> N >> M >> K;
    for (int i = 0; i < N; i++)
    {
        int a; cin >> a;
        Arr.push_back(a);
    }
    for (int i = 0; i < M + K; i++)
    {
        int a, b, c;
        cin >> a >> b >> c;
        Cmd.push_back(make_pair(a, make_pair(b, c)));
    }
}
 
ll Make_SegmentTree(int Node, int Start, int End)
{
    if (Start == End) return Tree_Array[Node] = Arr[Start];
    
    int Mid = (Start + End) / 2;
    ll Left_Result = Make_SegmentTree(Node * 2, Start, Mid);
    ll Right_Result = Make_SegmentTree(Node * 2 + 1, Mid + 1, End);
    Tree_Array[Node] = Left_Result + Right_Result;
    return Tree_Array[Node];
}
 
ll Sum(int Node, int Start, int End, int Left, int Right)
{
    if (Left > End || Right < Start) return 0;
    if (Left <= Start && End <= Right) return Tree_Array[Node];
 
    int Mid = (Start + End) / 2;
    ll Left_Result = Sum(Node * 2, Start, Mid, Left, Right);
    ll Right_Result = Sum(Node * 2 + 1, Mid + 1, End, Left, Right);
    return Left_Result + Right_Result;
}
 
void Update_SegmentTree(int Node, int Start, int End, int Index, ll Diff)
{
    if (Index < Start || Index > End) return;
    Tree_Array[Node] = Tree_Array[Node] + Diff;
 
    if (Start != End)
    {
        int Mid = (Start + End) / 2;
        Update_SegmentTree(Node * 2, Start, Mid, Index, Diff);
        Update_SegmentTree(Node * 2 + 1, Mid + 1, End, Index, Diff);
    }
}
 
void Solution()
{
    int Tree_Height = (int)ceil(log2(N));
    int Tree_Size = (1 << (Tree_Height + 1));
    Tree_Array.resize(Tree_Size);
    Make_SegmentTree(1, 0, N - 1);
 
    for (int i = 0; i < Cmd.size(); i++)
    {
        int Command = Cmd[i].first;
        if (Command == 1)
        {
            int Index = Cmd[i].second.first - 1;
            ll Value = Cmd[i].second.second;
            ll Diff = Value - Arr[Index];
            Arr[Index] = Value;
            Update_SegmentTree(1, 0, N - 1, Index, Diff);
        }
        else
        {
            int Index = Cmd[i].second.first - 1;
            int Index2 = Cmd[i].second.second - 1;
            ll Result = Sum(1, 0, N - 1, Index, Index2);
            cout << Result << endl;
        }
    }
}
 
void Solve()
{
    Input();
    Solution();
}
 
int main(void)
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
 
    //freopen("Input.txt", "r", stdin);
    Solve();
 
    return 0;
}