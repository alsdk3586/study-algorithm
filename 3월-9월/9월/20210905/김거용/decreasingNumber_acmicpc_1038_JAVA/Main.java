  
import java.io.*;
import java.util.*;

public class Main {
    public static void main(String[] args) throws IOException{
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        int n = Integer.parseInt(br.readLine());

        System.out.println(decreasingNumber(n));
    }
    public static long decreasingNumber(int n) {
        List<Long> generatedNumberSequence = new ArrayList<>();
        for(int powerOf10=9;powerOf10>=0;powerOf10--){
            for(int range=9;range>=powerOf10;range--){
                buildNumberSequence(generatedNumberSequence, powerOf10, range-1, range);        
            }
        }
        
        Collections.reverse(generatedNumberSequence);
        Long targetNumber = -1l;
        if(n<generatedNumberSequence.size())
            targetNumber = generatedNumberSequence.get(n);
        
        //System.out.println(targetNumber);
        
        return targetNumber;
    }
    private static void buildNumberSequence(List<Long> generatedNumberSequence,int powerOf10, int range, long generatedNumber){
        if(powerOf10==0){
            generatedNumberSequence.add(generatedNumber);
            return;
        }
        
        powerOf10 -=1;
        for(;range>=powerOf10;range--){
            long genNum = generatedNumber*10 + range;
            buildNumberSequence(generatedNumberSequence, powerOf10, range-1, genNum);        
        }
    }
}