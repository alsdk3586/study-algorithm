#include <string>
#include <vector>
#include <algorithm>

using namespace std;

typedef struct _node { // 노드의 정보를 담은 구조체
	int x;
	int y;
	int num;
	int left;
	int right;
}Node;
vector<Node> nodes; // 노드들의 정보를 담은 벡터
vector<int> preorder; // 전위 순회했을 때의 방문 순서
vector<int> postorder; // 후위 순회했을 때의 방문 순서

// 정렬 기준 : y값 기준 내림차순 -> x값 기준 오름차순
bool comp(Node n1, Node n2) {
	return n1.y != n2.y ? n1.y > n2.y : n1.x < n2.x;
}

// 이진트리를 만드는 함수
// 각 노드에 부모를 매칭시켜줌
void make_binary_tree(int nodeNum, int parent) {
	if (nodes[nodeNum].x < nodes[parent].x) { // 부모 노드보다 x값이 작은 경우
		if (nodes[parent].left == -1) { // 부모 노드의 왼쪽 자식이 없으면 연결
			nodes[parent].left = nodeNum;
		}
		else { // 왼쪽 자식이 있다면 왼쪽 자식을 부모 노드로 재귀
			make_binary_tree(nodeNum, nodes[parent].left);
		}
	}
	else { // 부모 노드보다 x값이 큰 경우
		if (nodes[parent].right == -1) { // 부모 노드의 오른쪽 자식이 없으면 연결
			nodes[parent].right = nodeNum;
		}
		else { // 오른쪽 자식이 있다면 오른쪽 자식을 부모 노드로 재귀
			make_binary_tree(nodeNum, nodes[parent].right);
		}
	}

	return;
}

// 전위 순회
// 현재 노드값 저장 -> 왼쪽 자식 방문 -> 오른쪽 자식 방문
void dfs_pre(int idx) {
	preorder.push_back(nodes[idx].num + 1);

	if (nodes[idx].left != -1) {
		dfs_pre(nodes[idx].left);
	}
	if (nodes[idx].right != -1) {
		dfs_pre(nodes[idx].right);
	}
}

// 후위 순회
// 왼쪽 자식 방문 -> 오른쪽 자식 방문 -> 현재 노드값 저장
void dfs_post(int idx) {
	if (nodes[idx].left != -1) {
		dfs_post(nodes[idx].left);
	}
	if (nodes[idx].right != -1) {
		dfs_post(nodes[idx].right);
	}
	postorder.push_back(nodes[idx].num + 1);
}

vector<vector<int>> solution(vector<vector<int>> nodeinfo) {
	vector<vector<int>> answer;

	// 노드 정보 저장
	for (int i = 0; i < nodeinfo.size(); i++) {
		Node node;
		node.x = nodeinfo[i][0];
		node.y = nodeinfo[i][1];
		node.num = i;
		node.left = -1;
		node.right = -1;
		nodes.push_back(node);
	}

	sort(nodes.begin(), nodes.end(), comp); // 노드 정렬

	// 이진트리를 만듦
	for (int i = 1; i < nodes.size(); i++) {
		make_binary_tree(i, 0);
	}

	dfs_pre(0);
	dfs_post(0);

	answer.push_back(preorder);
	answer.push_back(postorder);

	return answer;
}