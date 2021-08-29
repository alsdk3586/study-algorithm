import collections


def bfs(numbers, hand):
    numbers = collections.deque(numbers)
    left = ['1', '4', '7', '*']
    right = ['3', '6', '9', '#']
    middle = ['2', '5', '8', '0']
    left_location = [3, 0]
    right_location = [3, 2]
    answer = []

    while numbers:
        current = str(numbers.popleft())
        
        # 왼손 영역일 때
        if current in left:
            answer.append('L')
            left_location = [left.index(current), 0]
        # 오른손 영역일 때
        elif current in right:
            answer.append('R')
            right_location = [right.index(current), 2]
        else:
            target_row = middle.index(current)
            target_column = 1
            
            # 왼쪽 오른쪽 위치 계산
            left_result = abs(target_row - left_location[0]) + abs(target_column - left_location[1])
            right_result = abs(target_row - right_location[0]) + abs(target_column - right_location[1])
            
            # 거리 비교
            if left_result < right_result:
                answer.append('L')
                left_location = [target_row, target_column]
            elif left_result > right_result:
                answer.append('R')
                right_location = [target_row, target_column]
            else:
                # 거리가 같을 때 주 사용 손에 따라
                if hand == 'left':
                    answer.append('L')
                    left_location = [target_row, target_column]
                else:
                    answer.append('R')
                    right_location = [target_row, target_column]
    return answer

def solution(numbers, hand):
    return ''.join(bfs(numbers, hand))
