package com.company.algorithm_solving.study;

import java.util.HashMap;
import java.util.Set;

public class test1 {
    //뉴스 클러스터링
    //https://programmers.co.kr/learn/courses/30/lessons/17677

    static HashMap<String, Integer> aMap = new HashMap<>();
    static HashMap<String, Integer> bMap = new HashMap<>();
    static int intersectionCnt = 0;
    static int unionCnt = 0;

    public static void main(String args[ ]) {

        String str1 = "E=M*C^2";
        String str2 = "e=m*c^2";

        // 대문자 -> 소문자
        str1 = str1.toLowerCase();
        str2 = str2.toLowerCase();

        makeSets(str1, str2);
        makeIntersection();
        makeUnion();
        //return calRes();
        System.out.println(calRes());
    }

    static void makeSets(String str1, String str2) {

        for(int i=0; i<str1.length() - 1; i++) {
            String key = str1.substring(i, i+2);
            Integer aCnt = aMap.get(key);

            if(aCnt == null) aMap.put(key, 1);
            else aMap.put(key, aCnt + 1);
        }

        for(int i=0; i<str2.length() -1; i++) {
            String key = str2.substring(i, i+2);
            Integer bCnt = bMap.get(key);

            if(bCnt == null) bMap.put(key, 1);
            else bMap.put(key, bCnt + 1);
        }
    }

    //영어외에 다른글자 포함되어있으면 제거
    static boolean isAlphabet(String str) {

        for(int i=0; i<str.length(); i++) {
            char ch = str.charAt(i);

            if('a' <= ch && ch <= 'z') continue;
            else return false;
        }

        return true;
    }

    // 교집합 구하기
    static void makeIntersection( ) {

        Set<String> keySetA = aMap.keySet();
        for (String aKey : keySetA) {
            if(!isAlphabet(aKey)) continue;
            if(bMap.get(aKey) == null) continue;
            else {
                int aCount = aMap.get(aKey);
                int bCount = bMap.get(aKey);

                intersectionCnt += Math.min(aCount, bCount);
            }
        }
    }

    // 합집합 구하기
    static void makeUnion( ) {

        HashMap<String, Integer> resMap = new HashMap<>();
        resMap = aMap;

        Set<String> keySetB = bMap.keySet();
        for(String bKey : keySetB) {
            if(!isAlphabet(bKey)) continue;
            if(resMap.get(bKey) == null) resMap.put(bKey, bMap.get(bKey));
            else {
                int aCount = resMap.get(bKey);
                int bCount = bMap.get(bKey);

                resMap.put(bKey, Math.max(aCount, bCount));
            }
        }

        Set<String> keySetRes = resMap.keySet();
        for(String resKey : keySetRes) {
            if(!isAlphabet(resKey)) continue;
            unionCnt += resMap.get(resKey);
        }
    }

    // 결과값 구하기
    static int calRes( ) {
        //System.out.println("교집합 : " + intersectionCnt);
        //System.out.println("합집합 : " + unionCnt);

        if(intersectionCnt == 0 && unionCnt == 0) return 65536;
        return (int)(((double)intersectionCnt / (double)unionCnt) * 65536);
    }
}
