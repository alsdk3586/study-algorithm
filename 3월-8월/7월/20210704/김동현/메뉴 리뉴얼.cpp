#include <string>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

vector<string> subset(const string& s)
{
    int p = 1 << (int)s.length();
    vector<string> ret;
    for (int i = 0; i < p; i++)
    {
        string sub;
        for (int j = 0; j < s.length(); j++)
        {
            if (i & (1 << j))
                sub.push_back(s[j]);
        }
        sort(sub.begin(), sub.end());
        ret.push_back(sub);
    }
    return ret;
}

vector<string> solution(vector<string> orders, vector<int> course) {    
    map<string, int> freq;
    for (const auto& order : orders)
    {
        auto ss = subset(order);
        for (const auto& s : ss)
            freq[s]++;
    }
    
    
    pair<int, vector<string>> pv[11];
    for (const auto& kv : freq)
    {
        int l = (int)kv.first.length();
        int v = kv.second;
        if (l >= 2 && v >= 2 && find(course.begin(), course.end(), l) != course.end())
        {
            if (pv[l].first < v)
            {
                pv[l].first = v;
                pv[l].second.clear();
            }
            if (pv[l].first == v)
                pv[l].second.push_back(kv.first);
        }
    }
    
    vector<string> answer;
    for (int i = 0; i < 11; i++)
        answer.insert(answer.end(), pv[i].second.begin(), pv[i].second.end());
    
    sort(answer.begin(), answer.end());
    
    return answer;
}
