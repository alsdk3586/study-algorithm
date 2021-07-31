import java.util.*;
class Solution {
    public static int[] solution(String[] enroll, String[] referral, String[] seller, int[] amount) {
        int[] answer = new int[enroll.length];
        int [] par = new int[enroll.length+1];
        HashMap key  = new HashMap<String,Integer>();
        int idx = 1;
        for(int i=0;i<enroll.length;i++){
            key.put(enroll[i], idx++);
        }

        for(int i=1;i<=referral.length;i++){
            String parName = referral[i-1];
            if(parName.equals("-")){
                par[i] = 0;
            }else{
                par[i] = (int)key.get(parName);
            }
        }
        for(int i=0;i<seller.length;i++){
            String name = seller[i];
            int num = (int)key.get(name);
            int coin = amount[i]* 100;
            while(true){
                if(num==0){
                    break;
                }

                answer[num-1] += coin - (int)(coin*0.1);
                coin *= 0.1;
                num = par[num];
            }
        }

        return answer;
    }
}