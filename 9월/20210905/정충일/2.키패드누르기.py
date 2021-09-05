def get_distance(hand, number):
    location = {'1': (0, 0), '2': (0, 1), '3': (0, 2),
                '4': (1, 0), '5': (1, 1), '6': (1, 2),
                '7': (2, 0), '8': (2, 1), '9': (2, 2),
                '*': (3, 0), '0': (3, 1), '#': (3, 2)}
    number = str(number)
    x_hand, y_hand = location[hand]
    x_number, y_number = location[number]
    return abs(x_hand - x_number) + abs(y_hand - y_number)

def solution(numbers, hand):
    answer = ''
    left, right = '*', '#'
    hand = 'R' if hand == 'right' else 'L'
    for number in numbers:
        if number in [1, 4, 7]:
            answer += 'L'
            left = str(number)
            continue
        if number in [3, 6, 9]:
            answer += 'R'
            right = str(number)
            continue
        if number in [2, 5, 8, 0]:
            dis1 = get_distance(left, number)
            dis2 = get_distance(right, number)
            if dis1 > dis2:
                answer += 'R'
                right = str(number)
            if dis1 < dis2:
                answer += 'L'
                left = str(number)
            if dis1 == dis2:
                answer += hand
                if hand == 'R':
                    right = str(number)
                if hand == 'L':
                    left = str(number)
    return answer