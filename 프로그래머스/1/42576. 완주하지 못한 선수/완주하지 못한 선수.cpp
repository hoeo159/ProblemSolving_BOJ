#include <string>
#include <vector>
#include <unordered_map>

#include <iostream>

using namespace std;

unordered_map<string, int> complete;
unordered_map<string, int> part;

int N, M;

string solution(vector<string> participant, vector<string> completion) {
    string answer = "";
    N = participant.size(), M = completion.size();
    
    for(int i = 0; i < M; i++)
    {
        string cur = completion[i];
        complete[cur]++;
    }
    for(int i = 0; i < N; i++)
    {
        string cur = participant[i];
        part[cur]++;

    }
    
    
    for(int i = 0; i < N; i++)
    {
        string cur = participant[i];
        // cout << complete[cur] << " " << part[cur] << endl;
        
        if(complete[cur] != part[cur])
        {
            answer = cur;
        }
    }
    
    return answer;
}