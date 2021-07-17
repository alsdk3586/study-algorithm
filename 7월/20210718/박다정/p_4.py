# https://dev-note-97.tistory.com/156
# https://tech.kakao.com/2021/01/25/2021-kakao-recruitment-round-1/
# https://bladejun.tistory.com/72



def solution(play_time, adv_time, logs):
    # 모든 경우가 360000가지
    answer = 0
    total_time = [0 for _ in range(360001)]
    result = []
    
    play_time_sec = play_time.split(':')
    play_time_sec = int(play_time_sec[0]) * 3600 + int(play_time_sec[1]) * 60 + int(play_time_sec[2])
    
    adv_time_sec = adv_time.split(':')
    adv_time_sec = int(adv_time_sec[0]) * 3600 + int(adv_time_sec[1]) * 60 + int(adv_time_sec[2])
    
    # 사용자가 시청한 구간을 모두 표시
    for log in logs:
        start, end = log.split('-')
        
        start_time = start.split(':')
        start_time = int(start_time[0]) * 3600 + int(start_time[1]) * 60 + int(start_time[2])
        total_time[start_time] += 1
        
        # 마지막 시간은 포함하지 않기 위해
        end_time = end.split(':')
        end_time = int(end_time[0]) * 3600 + int(end_time[1]) * 60 + int(end_time[2])
        total_time[end_time] -= 1
    
    # 사용자가 시청한 구간을 표시
    for i in range(1, play_time_sec+1):
        total_time[i] = total_time[i] + total_time[i - 1]
    
    # 시청한 구간의 사용자들의 수를 표시
    for i in range(1, play_time_sec+1):
        total_time[i] = total_time[i] + total_time[i - 1]
        
    max_value = total_time[adv_time_sec]    
    max_time = 0
    
    # 모든 구간을 검색하여 시청자 수가 가장 많은 구간을 찾아냄
    for i in range(adv_time_sec-1, play_time_sec):
        if i >= adv_time_sec:
            if max_value < total_time[i] - total_time[i - adv_time_sec]:
                max_value = total_time[i] - total_time[i - adv_time_sec]
                max_time = i - adv_time_sec + 1
        else:
            if max_value < total_time[i]:
                max_value = total_time[i]
                max_time = i - adv_time_sec + 1
    
    # HH:MM:SS 형태로 수정
    hour = str(max_time // 3600).zfill(2)
    minute = str(max_time % 3600 // 60).zfill(2)
    second = str(max_time % 3600 % 60).zfill(2)
    
    return f"{hour}:{minute}:{second}"