import java.util.Arrays;
import java.util.Collections;
import java.util.ArrayList;
import java.util.List;

class Solution {
    private static final int[] math_giver_one = {1, 2, 3, 4, 5};
    private static final int[] math_giver_two = {2, 1, 2, 3, 2, 4, 2, 5};
    private static final int[] math_giver_three = {3, 3, 1, 1, 2, 2, 4, 4, 5, 5};
    
    private int[] getAnswerCount(int[] answers) {
        int one = 0;
        int two = 0;
        int three = 0;
        
        for (int i = 0; i < answers.length; i += 1) {
            if (math_giver_one[i % math_giver_one.length] == answers[i]) {
                one += 1;
            }
            if (math_giver_two[i % math_giver_two.length] == answers[i]) {
                two += 1;
            }
            if (math_giver_three[i % math_giver_three.length] == answers[i]) {
                three += 1;
            }
        }
        
        if (one == two && two == three) {
            int[] answer = {1, 2, 3};
            return answer;
        } else if (one == two && two > three) {
            int[] answer = {1, 2};
            return answer;
        } else if (one == three && three > two) {
            int[] answer = {1, 3};
            return answer;
        } else if (two == three && three > one) {
            int[] answer = {2, 3};
            return answer;
        } else {
            int[] result = {one, two, three};
            int max = Math.max(Math.max(one, two), three);
            
            for (int i = 0; i < 3; i += 1) {
                if (max == result[i]) {
                    int[] answer = {i + 1};
                    return answer;
                }
            }
        }
        int[] answer = {};
        return answer;
    }
    
    public int[] solution(int[] answers) {
        int[] answer = {};
        return getAnswerCount(answers);
    }
}