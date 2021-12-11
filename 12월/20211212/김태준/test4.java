package com.company;

import java.util.*;

// 1번케이스 런타임에러 뜨면... 항공권이 같은값이 나올 수 있음..(아래 케이스)
//  ->  static String[][] tickets = {{"ICN", "SFO"}, {"SFO", "ICN"}, {"ICN", "SFO"}, {"SFO", "QRE"}};
//
// 여행경로 문제풀이
// 문제풀이 조건
//  - 모든 항공권을 다 사용해야 한다. -> dfs를 통해 완전탐색을 한다.
//  - 가능한 경로가 2개 이상일 경우 알파벳 순서가 앞서는 경로를 return 한다. -> 방문한 공항이름을 string으로 붙여 가장 작은 경로가 포함된 곳을 return한다. (treeMap 사용)
// 문제풀이 방법
//  1. 인풋으로 들어온 항공권을 (출발공항, (도착공항, 출발점->도착점 방문여부)) 형태의 그래프로 만든다. (makeAndFillMap)
//    - EndAirPortInfo 클래스를 정의(도착공항, 방문체크여부)
//    - 그래프의 값을 담기 위해 hashMap 사용 -> key: 시작공항, value : (도착공항, 방문체크여부)
//  2. 시작점인 "ICN"을 기준으로 DFS 돌림 (goTravel)
//  3. dfs 함수에서 모든 항공권을 다 사용했을때 treeMap에 여행경로(travelList)를 넣는다.
//    - 모든 항공권을 다 사용했는지 판단 조건
//       - 항공권을 n개 사용했으면 방문한 공항수는 n+1개
//
public class test3 {

    static int ticketCount;
    static String startAirPortName = "ICN";
    //static String[][] tickets = {{"ICN", "SFO"}, {"SFO", "ICN"}, {"ICN", "SFO"}, {"SFO", "QRE"}};
    static String[][] tickets = {{"ICN", "SFO"}, {"ICN", "ATL"}, {"SFO", "ATL"}, {"ATL", "ICN"}, {"ATL","SFO"}};
    static SortedMap<String, Integer> resMap = new TreeMap<>();
    static Map<String, List<EndAirPortInfo>> edgeMap = new HashMap<>();
    
    public static void main(String args[]) {

        ticketCount = tickets.length;
        makeAndFillMap(tickets); // ticket 이름 기준으로 그래프 생성
        goTravel(); // 시작점을 기준으로 dfs 시작
        System.out.println(resMap.firstKey());
        //return makeResultStr(resMap.firstKey());
    }

    // 출발점, (도착점, 출발점->도착점 방문체크여부)
    static void makeAndFillMap(String[][] tickets) {
        for(int i=0; i<tickets.length; i++) {

            String startAirPort = tickets[i][0];
            String endAirPort = tickets[i][1];

            List<EndAirPortInfo> endAirPortList = edgeMap.get(startAirPort);
            if(endAirPortList == null) {
                endAirPortList = new ArrayList<>();
            }

            endAirPortList.add(new EndAirPortInfo(endAirPort, false));
            edgeMap.put(startAirPort, endAirPortList);
        }
    }

    static void goTravel() {
        List<String> travelList = new ArrayList<>();
        travelList.add(startAirPortName);
        dfs(travelList);
    }

    static void dfs(List<String> travelList) {

        // 티켓의 갯수가 n개이면 모든 티켓을 다 방문하면 공항의 갯수는 n + 1
        if(travelList.size() == ticketCount + 1) {
            StringBuilder sb = new StringBuilder();
            for(int i=0; i<travelList.size(); i++) {
                sb.append(travelList.get(i));
                sb.append(" ");
            }
            resMap.put(sb.toString(), 1); // 가능한 경로가 여러개 일경우 알파벳 앞서는 순서대로 출력
            return;
        };

        String startAirPort = travelList.get(travelList.size() - 1);
        List<EndAirPortInfo> endAirPortList = edgeMap.get(startAirPort);
        if(endAirPortList == null) return;
        else {
            for(int i=0; i<endAirPortList.size(); i++) {
                EndAirPortInfo endAirPortInfo = endAirPortList.get(i);
                String endAirPort = endAirPortInfo.endAirPortName;
                boolean visit = endAirPortInfo.visit;

                if(visit) continue;

                endAirPortInfo.visit = true;
                travelList.add(endAirPort);
                dfs(travelList);
                endAirPortInfo.visit = false;
                travelList.remove(travelList.size() - 1);
            }
        }
    }

    static String[ ] makeResultStr(String resStr) {
        String resArr[ ] = resStr.split(" ");
        return resArr;
    }

    static class EndAirPortInfo {
        String endAirPortName;
        boolean visit;

        public EndAirPortInfo(String endAirPortName, boolean visit) {
            this.endAirPortName = endAirPortName;
            this.visit = visit;
        }
    }
}

