#include <iostream>
#include <algorithm>
#include <vector>
#include <cstring>

using namespace std;

int N, K;

vector<pair<int, int>> item; // weight, value
int dp[101][100001]; // i번째 인덱스에서 남은 무게가 j일 때

int dfs(int index, int lastWeight)
{
    if(dp[index][lastWeight] != -1)
    {
        return dp[index][lastWeight];
    }
    
    if(lastWeight == 0 || index == N) // 남은 무게가 0이면 못넣음
    {
        return 0;
    }
    else if(lastWeight < 0)
    {
        return -1;
    }

    int ret = 0;
    int curWeight = item[index].first;
    int curValue = item[index].second;
    int local;
    if(lastWeight - curWeight >= 0)
    {
        local = max(dfs(index + 1, lastWeight - curWeight) + curValue, dfs(index + 1, lastWeight));
    }
    else
    {
        local = dfs(index + 1, lastWeight);
    }

    if(ret < local)
    {
        ret = local;
    }

    dp[index][lastWeight] = ret;

    return ret;
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> N >> K;

    for(int i = 0; i < N; i++)
    {
        int weight, value;
        cin >> weight >> value;
        item.push_back({weight, value});
        memset(dp[i], -1, sizeof(dp[i]));
    }

    int ret = dfs(0, K);
    cout << ret << "\n";
    return 0;
}