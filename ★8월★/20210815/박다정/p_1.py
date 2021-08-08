import sys

input = sys.stdin.readline

n = int(input().rstrip())
answer = []

for _ in range(n):
    s = list(input().rstrip())
    # 문자를 제거한 방향
    left_flag = False
    right_flag = False
    # 문자를 제거한 위치
    left_index = 0
    right_index = 0
    # 투 포인터 변수
    start = 0
    end = len(s) - 1
    # 중간에 만나면 중지
    while start < end:
        # 같은 문자일 때 안으로 한칸씩 이동
        if s[start] == s[end]:
            start += 1
            end -= 1
        elif s[start] != s[end]:
            # 왼쪽 문자를 제거하고 현재 위치 저장
            if not left_flag and not right_flag:
                left_flag = True
                left_index = start
                right_index = end
                start += 1
            # 왼쪽 문자를 제거했지만 회문 실패
            # 오른쪽으로 회문을 다시 시작하기 위해 돌아감
            elif left_flag and not right_flag:
                start = left_index
                end = right_index - 1
                right_flag = True
            # 왼쪽 오른쪽 모두 끝났을 때 종료
            elif left_flag and right_flag:
                break
    # 문자를 제거하지 않고 회문 통과
    if not left_flag and not right_flag and start >= end:
        answer.append(0)
    # 왼쪽 또는 오른쪽 문자를 제거하고 회문 통과
    elif left_flag and not right_flag and start >= end:
        answer.append(1)
    elif left_flag and right_flag and start >= end:
        answer.append(1)
    # 회문 통과 못함
    else:
        answer.append(2)

for a in answer:
    print(a)
