#include <string>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

struct Oper
{
    int index;
    int at;
    int cost;
    bool operator<(const Oper& other) const
    {
        if (cost != other.cost) return cost > other.cost;
        if (at != other.at) return at > other.at;
        return index > other.index;
    }
};



int solution(vector<vector<int>> jobs) {
    int answer = 0;
    
    sort(jobs.begin(), jobs.end());
    priority_queue<Oper> pq;
    
    int timestamp = 0;
    int N = jobs.size();
    int i = 0;
    
    for(int a = 0; a < N; )
    {
        while(i < N && jobs[i][0] <= timestamp)
        {
            pq.push({i, jobs[i][0], jobs[i][1]});
            i++;
        }
        
        
        if(pq.empty())
        {
            timestamp = jobs[i][0];
            continue;
        }
        
        Oper cur = pq.top();
        pq.pop();
        
        timestamp += cur.cost;
        answer += timestamp - cur.at;
        a++;
    }
    
    answer = answer / N;
    
    return answer;
}