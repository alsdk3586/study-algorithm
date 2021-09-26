def solution(word):
    answer=0
    vowel = {}
    vowel['A'] = [1,1,1,1,1]
    vowel['E'] = [782,157,32,7,2]
    vowel['I'] = [1563,313,63,13,3]
    vowel['O'] = [2344,469,94,19,4]
    vowel['U'] = [3125,625,125,25,5]

    for index, key in enumerate(word):
        answer+=vowel[key][index]
    return answer