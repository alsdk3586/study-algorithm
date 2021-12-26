package com.company.algorithm_solving.study.week4;

import java.util.HashMap;
import java.util.List;
import java.util.*;

public class test1 {
    //static String child[ ] = {"john", "mary", "edward", "sam", "emily", "jaimie", "tod", "young"}; // 피추천인
    //static String parent[ ] = {"-", "-", "mary", "edward", "mary", "mary", "jaimie", "edward"}; // 추천인
    //static String seller[ ] = {"young", "john", "tod", "emily", "mary"};
    static String child[ ] = {"john", "mary", "edward", "sam", "emily", "jaimie", "tod", "young"};
    static String parent[ ] = {"-", "-", "mary", "edward", "mary", "mary", "jaimie", "edward"}; // 추천인
    static String seller[ ] = {"young", "john", "tod", "emily", "mary"};
    static int amount[ ] = {12, 4, 2, 5, 10};
    static Map<String, Integer> salesMap = new HashMap<>();
    static Map<String, String> referEdge = new HashMap<>(); // 피추천자 -> 추천자
    static String root="-";

    public static void main(String args[ ]) {

        processInputData();
        doMainProcess();
        processOutputData();
    }

    public static void processInputData( ) {

        //추천관련 그래프 생성
        for(int i=0; i<child.length; i++) {
            String c = child[i];
            String p = parent[i];
            referEdge.put(c, p);
            salesMap.put(c, 0);
        }

        for(int i=0; i<seller.length; i++) {
            String _seller = seller[i];

            Integer sellAmount = salesMap.get(_seller);
            sellAmount += (amount[i]*100); // seller 에는 같은 이름이 중복해서 들어있을 수 있습니다.

            salesMap.put(_seller, sellAmount);
        }
    }

    public static void doMainProcess( ) {

        for(int i=0; i<seller.length; i++) {
            String child = seller[i];
            String parent = referEdge.get(child);
            int firstPrice = amount[i]*100;
            dfs(child, parent, firstPrice);
        }
    }

    public static void dfs(String _child, String _parent, int _firstPrice) {

        if(_child.equals(root)) return;

        int parentSalesRate = (_firstPrice / 10); // 절사 == 버림

        if(parentSalesRate == 0) return;
        else {
            int childSalesRate = salesMap.get(_child);
            salesMap.put(_child, childSalesRate - parentSalesRate);

            Integer oldParentSalesRate = salesMap.getOrDefault(_parent, 0);
            int newParentSalesRate = oldParentSalesRate + parentSalesRate;
            salesMap.put(_parent, newParentSalesRate);

            _child = _parent;
            _parent = referEdge.get(_child);
            dfs(_child, _parent, parentSalesRate);
        }
    }

    public static void processOutputData( ) {

        int result[ ] = new int[child.length];
        int idx = 0;
        for(int i=0; i<child.length; i++) {
            result[idx++] = salesMap.get(child[i]);
        }

        for(int i=0; i<result.length; i++) {
            System.out.println(result[i]);
        }
    }
}

