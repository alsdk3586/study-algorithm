import java.util.*;

class Word {
    public String word;
    public int level;
    
    public Word(String word, int level) {
        this.word = word;
        this.level = level;
    }
}

class Solution {
    private static Queue<Word> queue = new LinkedList();
    
    public int solution(String begin, String target, String[] words) {
        int answer = 0;
        HashMap<String, Boolean> visited = new HashMap<String, Boolean>();

        
        Word w = new Word(begin, 0);
        queue.offer(w);
        
        while (!queue.isEmpty()) {
            Word current = queue.poll();
            
            if (current.word.equals(target)) {
                return current.level;
            }
            
            for (String word : words) {
                int duplicatedCount = 0;
                
                for (int i = 0; i < word.length(); i += 1) {
                    if (word.charAt(i) == current.word.charAt(i)) {
                        duplicatedCount += 1;
                    }
                }
                if (word.length() - 1 == duplicatedCount && visited.get(word) == null) {
                    Word nw = new Word(word, current.level + 1);
                    visited.put(word, true);
                    queue.offer(nw);
                }
            }
        }
        
        return answer;
    }
}