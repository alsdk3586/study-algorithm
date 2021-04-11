/* 길 찾기 게임, kang-hyuck
  (트리)
  1. 트리 구현 하는 방법:  root에서 부터 (왼쪽,오른쪽)이 비어있는 곳까지 계속 탐색하면 된다.
  2. cmp함수: {return a.x < b.x} 하면, 왼쪽 x값이 작은순으로 정렬된다.
*/
#include <string>
#include <vector>
#include <algorithm>  // sort()
using namespace std;

typedef struct Node{
    int y,x, num, left,right;
}Node;

// 변수선언
vector<vector<int>> ans;
vector<int> preOrder, postOrder;
vector<Node> nodeSorted;  // 노드 정렬용도
Node node[10010];   // [노드번호]=(노드정보)
int visited[10010];
int root;

// 함수선언
void DFS(int);
void ConnectTree(int, int);
bool cmp(Node, Node);

vector<vector<int>> solution(vector<vector<int>> nodeinfo) {
    
    // 전역변수 초기화
    for(int i=0; i<nodeinfo.size(); i++){
        nodeSorted.push_back({nodeinfo[i][1],nodeinfo[i][0], i+1});  // nodeSorted: 정렬용도
        node[i+1] = {nodeinfo[i][1], nodeinfo[i][0], i+1};  //  node[번호] = (node 정보)
    }
    
    // 실행부
    sort(nodeSorted.begin(),nodeSorted.end(), cmp);  // 정렬
    root = nodeSorted[0].num;  // root 등록
    for(int i=1; i<nodeSorted.size(); i++) ConnectTree(root, nodeSorted[i].num);  // 해당 노드를 트리에 연결
    DFS(root);  // 탐색 시작
    
    // 출력부
    ans.push_back(preOrder);  ans.push_back(postOrder);
    return ans;
}

void ConnectTree(int num, int child)  // (현재 노드번호, 연결할 자식노드)
{
    // 노드 이동  (child를 연결할 수 있는 위치까지 이동)
    if(node[num].x > node[child].x && node[num].left  != 0) ConnectTree(node[num].left,  child);
    if(node[num].x < node[child].x && node[num].right != 0) ConnectTree(node[num].right, child);
    
    // 노드 연결
    if(node[num].x > node[child].x && node[num].left  == 0) node[num].left =child;
    if(node[num].x < node[child].x && node[num].right == 0) node[num].right=child;
}

void DFS(int num)
{
    // 종료부
    if(visited[num]==1) return;  // 방문한 적이 있는 경우
    if(num==0) return;  // 0인 경우 (없는 노드인 경우)
    
    visited[num]=1;  // 방문표시
    
    // 전위탐색 번호 저장
    preOrder.push_back(num);
    
    // 자식 노드 호출
    DFS(node[num].left );
    DFS(node[num].right);
    
    // 후위탐색 번호 저장
    postOrder.push_back(num);
}

bool cmp(Node a, Node b){
    if( a.y==b.y ) return a.x<b.x;  // x좌표 오름차순
    return a.y>b.y;  // y좌표 내림차순
}
