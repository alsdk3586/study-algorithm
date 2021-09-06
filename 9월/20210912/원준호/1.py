def solution(word):
    answer = 0
    words = []    
    def make_words(word, length):
        if length > 5:
            return
        words.append(word)
        for char in ["A","E","I","O","U"]:
            make_words(word+char, length+1)
    
    make_words("", 0)
    words.sort()
    return words.index(word)
