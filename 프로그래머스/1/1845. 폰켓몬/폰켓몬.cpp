#include <vector>
#include <unordered_map>

#include <iostream>

using namespace std;

int N;
unordered_map<int, int> pockets;

int solution(vector<int> nums)
{
    int answer = 0;
    N = nums.size();
    
    for(int i = 0; i < N; i++)
    {
        int cur = nums[i];
        pockets[cur]++;
    }
    int len = pockets.size();
    cout << pockets.size() << endl;
    if(len <= N / 2)
    {
        answer = len;
    }
    else
        answer = N / 2;
    
    return answer;
}