#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int N, M;
vector<int> v;
bool dp[2001][2001];

void solve()
{
    for(int i = 0; i < N; i++)
    {
        dp[i][i] = 1; // 길이 0
    }
    for(int i = 0; i < N - 1; i++)
    {
        dp[i][i + 1] = (v[i] == v[i + 1]); // 길이 1
    }
    for(int len = 2; len < N; len++)
    {
        for(int i = 0; i < N - len; i++)
        {
            int src = i, dst = i + len;
            dp[src][dst] = dp[src + 1][dst - 1] && (v[src] == v[dst]);
        }
    }
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    
    cin >> N;
    v.resize(N);
    for(int i = 0; i < N; i++)
    {
        cin >> v[i];
    }

    solve();

    cin >> M;
    for(int i = 0; i < M; i++)
    {
        int src, dst;
        cin >> src >> dst;
        cout << dp[src - 1][dst - 1] << "\n";
    }

    return 0;
}