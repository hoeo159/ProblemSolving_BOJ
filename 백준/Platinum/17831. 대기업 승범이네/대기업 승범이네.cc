#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int N;
vector<vector<int>> tree;
vector<int> v;
int dp[200001][2];  // i 직원이 0: 멘토링 멤버 아닐 때 최댓값, 1 : 멘토링 멤버 일 때 최댓값

int dfs(int index) // 0 직원 처리 할 때 자식 노드들의 최댓값
{
    if(dp[index][0] != -1 && dp[index][1] != -1)
    {   
        return max(dp[index][0], dp[index][1]);
    }

    int ret = 0;
    int len = tree[index].size();
    dp[index][0] = 0, dp[index][1] = 0;
    for(int i = 0; i < len; i++)
    {
        int cur = tree[index][i];
        dp[index][0] += dfs(cur);
    }
    
    dp[index][1] = dp[index][0];
    int Max = 0;
    for(int i = 0; i < len; i++)
    {
        int cur = tree[index][i];
        int curMax = v[index] * v[cur] + dp[cur][0] - max(dp[cur][0], dp[cur][1]);
        if(Max < curMax)
        {
            Max = curMax;
        }
    }
    dp[index][1] += Max;

    ret = max(dp[index][0], dp[index][1]);

    return ret;
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> N;
    tree.resize(N);
    v.resize(N);

    for(int i = 1; i < N; i++)
    {
        int mentor;
        cin >> mentor;
        tree[mentor - 1].push_back(i);
    }

    for(int i = 0; i < N; i++)
    {
        cin >> v[i];
        dp[i][0] = -1, dp[i][1] = -1;
    }

    int ret = dfs(0);
    cout << ret << "\n";
    return 0;
}