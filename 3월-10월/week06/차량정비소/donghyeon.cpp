#include <iostream>
#include <string.h>
#include <queue>
using namespace std;

// 고객정보를 담은 구조체
typedef struct _customer {
	int arriveTime; // 처음 도착시간
	int receptionNum; // 이용했던 접수처 번호
	int repairNum; // 이용했던 정비소 번호
	int processTime; // 남은 일처리 시간
	int receptionFinishTime; // 접수처에서 나온 시간
}Customer;
Customer customer[1002];

// 정비소 대기인원 정렬기준
// 정비소에 먼저 온 순서(= 접수처에서 나온 시간) 오름차순 -> 이용했던 접수처 번호 오름차순
struct cmp {
	bool operator()(int a, int b) {
		if (customer[a].receptionFinishTime != customer[b].receptionFinishTime) {
			return customer[a].receptionFinishTime > customer[b].receptionFinishTime;
		}
		else {
			return customer[a].receptionNum > customer[b].receptionNum;
		}
	}
};

int N;
int M;
int K;
int A;
int B;
int receptionDesk[11]; // 각 접수처가 처리하는 고객번호
int repairDesk[11]; // 각 정비소가 처리하는 고객번호
int receptionTime[11]; // 각 접수처 처리시간
int repairTime[11]; // 각 정비소 처리시간
queue<int> notArrive; // 아직 도착하지 않은 고객번호
queue<int> waitingReception; // 접수처에 가기 위해 대기하는 고객번호
priority_queue<int, vector<int>, cmp> waitingRepair; // 정비소에 가기 위해 대기하는 고객번호
int times; // 현재 시간
int completeCnt; // 모든 처리를 마친 고객 수
int answer;

// 접수처 일처리
void processReception() {
	for (int i = 1; i <= N; i++) {
		if (receptionDesk[i] != 0) { // i번 접수처에 고객이 있다면
			int cm = receptionDesk[i];
			customer[cm].processTime--; // 해당 접수처의 고객의 남은 일처리 시간을 감소
			if (customer[cm].processTime == 0) { // 일을 끝냈다면
				customer[cm].receptionFinishTime = times; // 접수처에서 일을 끝낸 시간 저장
				waitingRepair.push(cm); // 정비소 대기 고객열에 넣음
				receptionDesk[i] = 0; // 해당 접수처가 맡고 있는 고객 표시를 지움
			}
		}
	}
}

// 비어있는 접수처 중 가장 번호가 작은 곳을 가져옴
int isEmptyReception() {
	for (int i = 1; i <= N; i++) {
		if (receptionDesk[i] == 0) {
			return i;
		}
	}
	return 0;
}

// 접수처 대기 고객 -> 접수처에 매칭하는 함수
void matchReception() {
	while (!waitingReception.empty()) { // 접수처 대기 고객이 있는 경우에만
		int receptionNum = isEmptyReception(); // 빈 접수처를 가져옴
		if (receptionNum == 0) { // 빈 접수처가 없다면 종료
			return;
		}

		int cm = waitingReception.front(); // 대기 고객 중 가장 먼저인 고객을 가져와
		waitingReception.pop();
		receptionDesk[receptionNum] = cm; // 빈 접수처에 매칭
		customer[cm].processTime = receptionTime[receptionNum]; // 매칭된 고객의 일처리 시간 = 해당 접수처 처리시간
		customer[cm].receptionNum = receptionNum; // 매칭된 고객 접수처 번호 = 해당 접수처 번호
	}
}

// 정비소 일처리
void processRepair() {
	for (int i = 1; i <= M; i++) {
		if (repairDesk[i] != 0) { // i번 정비소에 고객이 있다면
			int cm = repairDesk[i];
			customer[cm].processTime--; // 해당 정비소의 고객의 남은 일처리 시간을 감소
			if (customer[cm].processTime == 0) {  // 일을 끝냈다면
				repairDesk[i] = 0; // 해당 정비가 맡고 있는 고객 표시를 지움
				completeCnt++; // 모든 일을 끝낸 고객 수 증가
				if (customer[cm].receptionNum == A && customer[cm].repairNum == B) {
					answer += cm; // 해당 고객의 접수처 번호와 정비소 번호가 찾으려는 고객과 일치하면 고객 번호 더함
				}
			}
		}
	}
}

// 비어있는 정비소 중 가장 번호가 작은 곳을 가져옴
int isEmptyRepair() {
	for (int i = 1; i <= M; i++) {
		if (repairDesk[i] == 0) {
			return i;
		}
	}
	return 0;
}

// 정비소 대기 고객 -> 정비소에 매칭하는 함수
void matchRepair() {
	while (!waitingRepair.empty()) { // 정비소 대기 고객이 있는 경우에만
		int repairNum = isEmptyRepair(); // 빈 정비소를 가져옴
		if (repairNum == 0) { // // 빈 정비소가 없다면 종료
			return;
		}
		// 대기 고객 중 가장 우선순위가 높은 고객을 가져옴(먼저 온 순서 -> 접수처 번호가 작은 순서)
		int cm = waitingRepair.top();
		waitingRepair.pop();
		repairDesk[repairNum] = cm; // 빈 정비소에 매칭
		customer[cm].processTime = repairTime[repairNum]; // 매칭된 고객의 일처리 시간 = 해당 정비소 처리시간
		customer[cm].repairNum = repairNum; // 매칭된 고객 정비소 번호 = 해당 정비소 번호
	}
}

int main(int argc, char** argv)
{
	int test_case;
	int T;

	cin >> T;

	for (test_case = 1; test_case <= T; ++test_case)
	{
		/*************** 초기화 ***************/
		cin >> N >> M >> K >> A >> B;

		for (int i = 1; i <= N; i++) {
			cin >> receptionTime[i];
		}
		for (int i = 1; i <= M; i++) {
			cin >> repairTime[i];
		}
		for (int i = 1; i <= K; i++) {
			cin >> customer[i].arriveTime;
		}

		memset(receptionDesk, 0, sizeof(receptionDesk));
		memset(repairDesk, 0, sizeof(repairDesk));
		times = 0;
		completeCnt = 0;
		answer = 0;
		/*************** 초기화 ***************/

		for (int i = 1; i <= K; i++) { // 아직 도착하지 않은 고객들을 넣음
			notArrive.push(i);
		}

		while (completeCnt < K) { // 모든 고객을 처리할 때까지
			while (!notArrive.empty()) { // 아직 도착하지 않은 고객들이 있다면
				// 해당 고객들의 도착시간이 현재시간 보다 앞서면
				// 접수처 대기 고객열에 넣음
				if (customer[notArrive.front()].arriveTime <= times) {
					waitingReception.push(notArrive.front());
					notArrive.pop();
				}
				else {
					break;
				}
			}

			processReception(); // 접수처 일처리
			matchReception(); // 접수처 매칭
			processRepair(); // 정비소 일처리
			matchRepair(); // 정비소 매칭

			times++; // 시간 증가
		}

		if (answer == 0) {
			answer = -1;
		}
		cout << "#" << test_case << " " << answer << endl;
	}
	return 0;
}