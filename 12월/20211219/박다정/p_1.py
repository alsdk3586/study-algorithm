def dfs(n, sequence, operations, current):
    if current > len(sequence)-1:
        return [sequence]
    
    result = []

    for i in range(len(operations)):
        if operations[i] == 0:
            continue

        new_sequence = sequence[:]
        new_sequence[current] = i
        new_operations = operations[:]
        new_operations[i] -= 1

        result += dfs(n, new_sequence, new_operations, current + 2)

    return result

def main(n, sequence, operations):
    results = dfs(n, sequence, operations, 1)
    numbers = []

    for result in results:
        number = result[0]
        for i in range(1,len(result), 2):
            if result[i] == 0:
                number += result[i+1]
            elif result[i] == 1:
                number -= result[i+1]
            elif result[i] == 2:
                number *= result[i+1]
            else:
                if result[i+1] < 0 and number > 0:
                    number /= abs(result[i+1])
                    number = int(number)
                    number *= -1
                    continue    
                number /= result[i+1]
                number = int(number)
        numbers.append(number)

    print(max(numbers))
    print(min(numbers))

if __name__ == '__main__':
    n = int(input())
    sequence = []

    for number in input().split(' '):
        sequence.append(int(number))
        sequence.append(0)
    sequence.pop()
    operations = list(map(int, input().split(' ')))
    main(n, sequence, operations)