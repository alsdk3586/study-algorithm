def solution(table, languages, preference):
    lpDictionary = {}
    
    for i in range(len(languages)):
        lpDictionary[ languages[i] ] = preference[i]
    
    maxScore = 0;
    maxScoredProfession = 'zzzzzzzzzz';
    
    for professionLanguageScore in table:
        plsBasis = professionLanguageScore.split(' ')
        profession = plsBasis[0]
        del plsBasis[0]
        plsBasis.append(profession)
        langScore = plsBasis[::-1]
        
        prefScore = 0
        for i in reversed(range(1,6)):
            currLang = langScore[i]
            if(currLang in lpDictionary):
                prefScore += lpDictionary[currLang] * i
                
        if(maxScore < prefScore):
            maxScore = prefScore
            maxScoredProfession = profession

        if(maxScore == prefScore):
            maxScoredProfession = min(maxScoredProfession,profession)
            
    return maxScoredProfession
