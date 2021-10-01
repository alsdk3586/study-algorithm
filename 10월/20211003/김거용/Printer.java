package Aprinter;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.Map;

//https://programmers.co.kr/learn/courses/30/lessons/42587
/*
일반적인 프린터는 인쇄 요청이 들어온 순서대로 인쇄합니다. 그렇기 때문에 중요한 문서가 나중에 인쇄될 수 있습니다. 
이런 문제를 보완하기 위해 중요도가 높은 문서를 먼저 인쇄하는 프린터를 개발했습니다. 
이 새롭게 개발한 프린터는 아래와 같은 방식으로 인쇄 작업을 수행합니다.

1. 인쇄 대기목록의 가장 앞에 있는 문서(J)를 대기목록에서 꺼냅니다.
2. 나머지 인쇄 대기목록에서 J보다 중요도가 높은 문서가 한 개라도 존재하면 J를 대기목록의 가장 마지막에 넣습니다.
3. 그렇지 않으면 J를 인쇄합니다.

예를 들어, 4개의 문서(A, B, C, D)가 순서대로 인쇄 대기목록에 있고 중요도가 2 1 3 2 라면 C D A B 순으로 인쇄하게 됩니다.

내가 인쇄를 요청한 문서가 몇 번째로 인쇄되는지 알고 싶습니다. 위의 예에서 C는 1번째로, A는 3번째로 인쇄됩니다.

현재 대기목록에 있는 문서의 중요도가 순서대로 담긴 배열 priorities와 내가 인쇄를 요청한 문서가 
현재 대기목록의 어떤 위치에 있는지를 알려주는 location이 매개변수로 주어질 때, 
내가 인쇄를 요청한 문서가 몇 번째로 인쇄되는지 return 하도록 solution 함수를 작성해주세요.
*/
public class Solution {
    public int solution(int[] priorities, int location) {
        //사고의 흐름을 적어보자.
        
        // 내 우선순위보다 높은 애는 모두 나보다 먼저 처리됨
        // 내 우선순위보다 바로 윗등급의 문서들이 어떻게 처리되느냐에 따라 
        //내 우선순위레벨 처리 시작시점의 배열의 상태가 변경되어있는 상태가 결정됨.
        
        //내 우선순위보다 높은애들을 카운팅
        //내 우선순위 바로 윗등급 문서의 처리 순서를 확인?...하려면 그 윗등급도 처리해야되나?
        //방법/룰/공식이 있을텐데...
        //O(M*N)으로 처리해야되나? 9부터 8 7 6 5 4 3 2 1? (M=9, N=100)
        
        //첫 순회(N)에서 각 우선순위별로 배열을 생성해서 인덱스를 삽입
        //for 9to1
        //  //내 우선순위이면 현재 배열에서 내 location을 찾아서 그 인덱스를 answer에 더하고 종료
        //  //최고 우선순위의 마지막 인덱스를 기준으로 그것보다 낮은 숫자는 모두 뒤로 보낸다.
        //아니아니아니아니
        
        //int lastProcessedLocation = 100; //도입
        //  lastProcessedLocation //보다 작은 수 중 Max 값/보다 큰 수 중 Min값 이 주요 키가 되겠다.
        //  보다 작은 수 중 Max 값이 다음 우선순위 처리 중 맨 뒤에 있을 값이 되겠지?
        //  보다 큰 수 중 Min값이 다음 우선순위 처리 중 맨 먼저 처리될 값이 되겠지?
        //  내 우선순위에 도달하지 않았으면
        //      보다 작은 수 중 Max 값을 구해서 lastProcessedLocation에 넣고 
        //      Answer에 현재 배열의 길이를 더한 뒤
        //      루프 넘김
        //  내 우선순위에 도달했으면
        //      보다 큰 수 중 Min값 부터 내 loc index까지의 거리를 구해서 
                    //..면 원형 단방향 큐를 쓰는게 좋나?..는 그냥 모듈러 연산? 
                    //내 loc index보다 크면 전체길이 - 해당 loc index + 내 loc index
                    //내 loc index보다 작으면 내 loc index - 해당 loc index
        //      Answer에 더하고
        //      전체 루프 종료
        
        // 하면 될것같음.  Almost O(2N)? 여기까지 30분컷!
            
        //  코딩 시작! - 완료에 한시간 리팩토링에 한시간 반;;;;;

        //내 문서의 우선순위
        int myDocPriority = priorities[location];
        //최대 우선순위(for 문 범위 지정)
        int maxPriority=-100;
        Map<Integer, ArrayList<Integer>> priorityMap = new HashMap<Integer, ArrayList<Integer>>();
        ArrayList<Integer> currentPriorityArray;
        
        //첫 순회(N)에서 각 우선순위별로 배열을 생성해서 인덱스를 삽입
        for(int priorityLocation = 0 ; priorityLocation < priorities.length ; priorityLocation++){
            //현재 우선 순위를 꺼내서
            int currentPriority = priorities[priorityLocation];

            //내 우선 순위보다 낮은 애들은 관심 밖이니까 스킵
            if(myDocPriority > currentPriority) continue;
            
            //최대 Priority를 구하고
            maxPriority = Math.max(maxPriority, currentPriority);

            //동일 순위가 없었으면 배열을 새로 만들고 
            if(!priorityMap.containsKey(currentPriority))   priorityMap.put(currentPriority, new ArrayList<Integer>());

            //해당 우선순위 배열에 주어진 배열의 인덱스(Location)을 삽입
            currentPriorityArray = priorityMap.get(currentPriority);
            currentPriorityArray.add(priorityLocation);
        }

        //마지막으로 처리된 인덱스
        int lastProcessedLocation = 100;
        int processedDocumentCount = 0;
        for(int currentPriority = maxPriority ; currentPriority >= myDocPriority ; currentPriority--){
            //현재 우선순위가 배열에 존재하지 않으면 스킵
            if(!priorityMap.containsKey(currentPriority))   continue;

            currentPriorityArray = priorityMap.get(currentPriority);

            int[] processResult = this.processDocPrinter(lastProcessedLocation, currentPriorityArray);
             //마지막 처리된 인덱스보다 작은 수중에 최대값      : 마지막에 처리될 문서의 위치
            int maxAmongSmaller = processResult[0];
            //마지막 처리된 인덱스보다 큰 수중에 최소값         : 맨 처음 처리될 문서의 위치
            int minAmongBiggerLocation = processResult[1];
            
            lastProcessedLocation = maxAmongSmaller;
             
            //  내 우선순위에 도달하기 전이면 처리된 도큐먼트 카운팅
            if(currentPriority > myDocPriority) processedDocumentCount += currentPriorityArray.size();
                
            // 내 우선순위에 도달하면  내 문서가 배열 안에서 몇번째 처리되는지 계산하고 종료
            else                processedDocumentCount += this.countMyDocSequence(minAmongBiggerLocation, location, currentPriorityArray);
            
        }
        
        return processedDocumentCount;
    }

    private int[] processDocPrinter(int lastProcessedLocation, ArrayList<Integer> currentPriorityArray) {
        
        //마지막 처리된 인덱스보다 작은 수중에 최대값   : 마지막에 처리될 문서의 위치
        int maxAmongSmallerLocation = -1;
        //마지막 처리된 인덱스보다 큰 수중에 최소값     : 맨 처음 처리될 문서의 위치
        int minAmongBiggerLocation = 100;
        
        for(int currentLocation : currentPriorityArray)
        {
            //가장 마지막에 처리될 문서의 위치를 찾는다.
            if(currentLocation < lastProcessedLocation)         maxAmongSmallerLocation = Math.max(maxAmongSmallerLocation, currentLocation);

            //맨 처음 처리될 문서의 위치를 찾는다. == 이전 배열에서 마지막에 처리되었던 문서 바로 다음에 오는 문서
            else if(currentLocation > lastProcessedLocation)    minAmongBiggerLocation = Math.min(minAmongBiggerLocation, currentLocation);
        }

        //맨 마지막에 처리될 문서를 못찾았으면 맨 앞에서부터 처리되므로 맨 마지막에 있는 문서를 마지막에 처리한 문서로 리턴한다.
        if(maxAmongSmallerLocation == -1)   maxAmongSmallerLocation = currentPriorityArray.get(currentPriorityArray.size()-1);

        //맨 처음 처리될 문서를 못찾았으면 맨 앞에서부터 처리되므로 내 문서의 현재 배열 위치가 처리 순서다.
        if(minAmongBiggerLocation == 100)   minAmongBiggerLocation = currentPriorityArray.get(0); 

        return new int[]{maxAmongSmallerLocation, minAmongBiggerLocation};
    }

    private int countMyDocSequence(int minAmongBiggerLocation, int myDocLocation, ArrayList<Integer> currentPriorityArray) {
        int nDocProcessedB4MyDoc = -1;

        //내 문서의 현재 배열에서의 인덱스
        int myDocLocationIndex = currentPriorityArray.indexOf(myDocLocation);

        //lastProcessedLocation보다 큰 수부터 순서대로 출력한다.
        int minAmongBiggerIndex = currentPriorityArray.indexOf(minAmongBiggerLocation);//100이면 lastProcessedLocation보다 큰 수가 없으므로 맨 앞부터 순서대로 출력한다.
                        
         //처음 처리되는 문서보다 내 문서가 뒤에 있으면 단순 계산
        if(myDocLocationIndex >= minAmongBiggerIndex)   nDocProcessedB4MyDoc = myDocLocationIndex - minAmongBiggerIndex + 1;
        
        //처음처리되는 문서보다 내문서가 앞에 있으면 큐를 한바퀴 돌려서 계산
        else                                                                nDocProcessedB4MyDoc = myDocLocationIndex + currentPriorityArray.size() - minAmongBiggerIndex +1;
        
        //내 문서가 처리될때 까지 현재 배열에서 처리된 문서 수
        return nDocProcessedB4MyDoc;
    }
}
