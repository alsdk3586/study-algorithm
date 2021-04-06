#include <iostream>
#include <vector>
#include <climits>
#include <cmath>
#include <algorithm>

using namespace std;

int S[17][17]; // 시너지 정보
int N;
int K;
int C[17]; // N개 중 K개를 고른 조합
vector<int> A; // A음식의 식재료들
vector<int> B; // B음식의 식재료들
int minDiff; // 두 음식간의 최소 맛의 차이

// 각 음식들의 시너지 합을 구하고 맛의 차이를 구하는 함수
void makeSynergy() {
	int aSum = 0; // A음식의 맛
	int bSum = 0; // B음식의 맛

	// 각 재료들의 시너지들을 더함
	for (int i = 0; i < A.size(); i++) {
		for (int j = 0; j < A.size(); j++) {
			if (i != j) {
				aSum += S[A[i]][A[j]];
			}
		}
	}

	// 각 재료들의 시너지들을 더함
	for (int i = 0; i < B.size(); i++) {
		for (int j = 0; j < B.size(); j++) {
			if (i != j) {
				bSum += S[B[i]][B[j]];
			}
		}
	}

	// 두 음식의 맛이 차이가 최소값보다 작으면 갱신
	int diff = abs(aSum - bSum);
	minDiff = min(minDiff, diff);

	return;
}

// N개의 재료 중 K개를 선택
void nCk(int depth, int next) {
	if (depth == K) { // K개를 모두 선택했다면
		// 식재료를 담은 벡터 초기화
		A.clear();
		B.clear();

		int check[17] = { 0, }; // A음식이 선택한 식재료들 체크
		// K개를 고른 조합을 A음식의 식재료로 넣고
		// 선택되지 않은 요소들을 B음식의 식재료에 넣음
		for (int i = 0; i < K; i++) {
			A.push_back(C[i]);
			check[C[i]] = 1;

		}
		for (int i = 0; i < N; i++) {
			if (check[i] == 0) {
				B.push_back(i);
			}
		}

		makeSynergy();
	}
	else { // 아직 K개의 조합을 다 고르지 않았다면
		for (int i = next; i < N; i++) {
			C[depth] = i; // depth번째 식재료로 i번을 선택
			nCk(depth + 1, i + 1); // i번 이후 식재료로 조합의 수를 이어나감
		}
	}

	return;
}

int main(int argc, char** argv)
{
	int test_case;
	int T;

	cin >> T;

	for (test_case = 1; test_case <= T; ++test_case)
	{
		// 초기화
		cin >> N;
		K = N / 2;
		minDiff = INT_MAX;

		// 시너지 값 저장
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				cin >> S[i][j];
			}
		}

		nCk(0, 0); // (0개 선택, 0번까지 선택)

		cout << "#" << test_case << " " << minDiff << endl;
	}
	return 0;
}