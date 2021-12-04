class Trie():
    def __init__(self):
        self.root = dict()
        self.value = 0

    def add_word(self, word):
        cursor = self.root
        for char in word:
            if cursor.get(char) is None:
                cursor[char] = dict()
            cursor = cursor[char]
        cursor[True] = dict()

    def find_word(self, word):
        cursor = self.root
        cnt = 0
        for char in word:
            if len(cursor) <= 1:
                cnt += 1
            else:
                cnt = 0
            cursor = cursor[char]
        if len(cursor) >= 2:
            cnt = 0
        return len(word) - cnt

def solution(words):
    answer = 0
    trie = Trie()

    for word in words:
        trie.add_word(word)

    answer = 0
    for word in words:
        answer += trie.find_word(word)
    return answer
