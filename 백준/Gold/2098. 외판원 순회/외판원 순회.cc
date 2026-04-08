#include <iostream>
#include <algorithm>
#include <vector>
#include <climits>
#include <cmath>

using namespace std;

#define MAX 999999999

int N;
vector<int> graph[16];
vector<int> dp[16];

int dfs(int curCity, int bitmask)
{
    if(dp[curCity][bitmask] != -1) return dp[curCity][bitmask];
    if(bitmask == (1 << N) - 1)
    {
        if(graph[curCity][0] > 0)
        {
            return graph[curCity][0];
        }
        else
        {
            return MAX;
        }
    }

    int ret = MAX;

    for(int i = 0; i < N; i++)
    {
        if(graph[curCity][i] == 0) continue;

        if(!(bitmask & (1 << i)))
        {
            ret = min(ret, graph[curCity][i] + dfs(i, (bitmask | (1 << i))));
        }
    }
    dp[curCity][bitmask] = ret;
    return ret;
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> N;
    for(int i = 0; i < N; i++)
    {
        for(int j = 0; j < N; j++)
        {
            int num;
            cin >> num;
            graph[i].push_back(num);
        }
    }
    int bitmask = 1 << N;
    
    for(int i = 0; i < 16; i++)
    {
        dp[i].resize(bitmask, -1);
    }

    int ret = dfs(0, 1);
    cout << ret << "\n";
    return 0;
}