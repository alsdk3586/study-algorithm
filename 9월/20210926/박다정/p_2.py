import sys


def get_blind_spot(office):
    count = 0

    for row in range(len(office)):
        for column in range(len(office[row])):
            if office[row][column] == '0':
                count += 1
    return count


def view_office_for_cctv_type(office, cctv_type, row, column, current_direction):
    if cctv_type == '5':
        direction1 = current_direction
        direction2 = turn_cctv_to_left(direction1)
        direction3 = turn_cctv_to_left(direction2)
        direction4 = turn_cctv_to_left(direction3)

        fill_cctv_view_in_office(office, direction1, row, column)
        fill_cctv_view_in_office(office, direction2, row, column)
        fill_cctv_view_in_office(office, direction3, row, column)
        fill_cctv_view_in_office(office, direction4, row, column)
    elif cctv_type == '4':
        direction1 = current_direction
        direction2 = turn_cctv_to_left(direction1)
        direction3 = turn_cctv_to_left(direction2)

        fill_cctv_view_in_office(office, direction1, row, column)
        fill_cctv_view_in_office(office, direction2, row, column)
        fill_cctv_view_in_office(office, direction3, row, column)
    elif cctv_type == '3':
        direction1 = current_direction
        direction2 = turn_cctv_to_left(direction1)

        fill_cctv_view_in_office(office, direction1, row, column)
        fill_cctv_view_in_office(office, direction2, row, column)
    elif cctv_type == '2':
        direction1 = current_direction
        direction2 = turn_cctv_to_left(turn_cctv_to_left(direction1))

        fill_cctv_view_in_office(office, direction1, row, column)
        fill_cctv_view_in_office(office, direction2, row, column)
    else:
        fill_cctv_view_in_office(office, current_direction, row, column)


def fill_cctv_view_in_office(office, direction, row, column):
    if direction == 0:
        for i in range(row - 1, -1, -1):
            if office[i][column] == '6':
                return
            office[i][column] = '#'

    elif direction == 1:
        for i in range(column + 1, len(office[0])):
            if office[row][i] == '6':
                return
            office[row][i] = '#'

    elif direction == 2:
        for i in range(row + 1, len(office)):
            if office[i][column] == '6':
                return
            office[i][column] = '#'

    else:
        for i in range(column - 1, -1, -1):
            if office[row][i] == '6':
                return
            office[row][i] = '#'

    return office


def get_cctv_informations(office):
    cctv_informations = []

    for row in range(len(office)):
        for column in range(len(office[row])):
            if '0' < office[row][column] < '6':
                cctv_informations.append((row, column, office[row][column]))

    return cctv_informations


def turn_cctv_to_left(direction):
    return (direction + 3) % 4


def dfs(office, cctv_info, count, cctv_index):
    if count == 0:
        return [get_blind_spot(office)]

    result = []
    directions = [0, 1, 2, 3]

    for direction in directions:
        new_office = [row[:] for row in office]
        row, column, cctv_type = cctv_info[cctv_index]

        view_office_for_cctv_type(new_office, cctv_type, row, column, direction)

        result += dfs(new_office, cctv_info, count - 1, cctv_index + 1)

    return result


def main(n, m, office):
    cctv_informations = get_cctv_informations(office)

    print(min(dfs(office, cctv_informations, len(cctv_informations), 0)))


if __name__ == '__main__':
    n, m = map(int, input().split())
    office = [sys.stdin.readline().rstrip().split() for _ in range(n)]
    main(n, m, office)
