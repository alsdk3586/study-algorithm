def solution(table, languages, preference):
    answer = ''
    s = []
    for i in table:
        tables = i.split(" ")
        index_l = 0
        score = 0
        for l in languages:
            if l in tables:
                score += preference[index_l] * (6 - tables.index(l))
            index_l +=1
        s.append(score)
    m = max(s)
    if s.count(m) == 1:
        return table[s.index(m)].split(' ')[0]
    else:
        l = []
        n = -1
        for i in range(s.count(m)):
            n = s.index(m, n + 1)
            l.append(table[n].split(' ')[0])
        l.sort()
        return l[0]