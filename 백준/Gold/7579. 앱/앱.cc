#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>
#include <cstring>

using namespace std;

int N, M;
vector<int> appMemory;
vector<int> appCost;
int dp[101][10001];   //i 번째 app까지 고려했을 때 남은 비용이 j일때 최대 확보 메모리

int dfs(int index, int cost) // 현재 인덱스, 남은 비용 
{
    if(dp[index][cost] != -1)
    {
        return dp[index][cost];
    }
    if(index == N)
    {
        return 0;
    }

    int ret = 0;
    ret = max(ret, dfs(index + 1, cost));
    if(cost - appCost[index] >= 0)
        ret = max(ret, dfs(index + 1, cost - appCost[index]) + appMemory[index]);
    dp[index][cost] = ret;

    return ret;
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> N >> M;
    
    appMemory.resize(N);
    appCost.resize(N);

    for(int i = 0; i < N; i++)
    {
        cin >> appMemory[i];
        memset(dp[i], -1, sizeof(dp[i]));
    }
    for(int i = 0; i < N; i++)
    {
        cin >> appCost[i];
    }

    for(int i = 0; i <= N * 100; i++)
    {
        if(dfs(0, i) >= M)
        {
            cout << i << "\n";
            break;
        }
    }
    return 0;
}