# 처음으로 다른 문자열이 나올때 길이 반환
def get_not_common_string_length(str1, str2):
    count = 0
    
    for i in range(len(str1)):
        if str1[i] == str2[i]:
            count += 1
        else:
            count += 1
            break
        if i == len(str2)-1:
            count += 1
            break

    return count

def solution(words):
    answer = 0

    words.sort()
    
    for i in range(len(words)):
        
        if i == 0:
            answer = get_not_common_string_length(words[0], words[1])
        elif i == len(words) -1:
            answer += get_not_common_string_length(words[-1], words[-2])
        else:
            prev_word_length = get_not_common_string_length(words[i], words[i-1])
            next_word_length = get_not_common_string_length(words[i], words[i+1])
                            
            answer += max(prev_word_length, next_word_length)
            
    return answer