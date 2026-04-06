#include <iostream>
#include <algorithm>

using namespace std;

int graph[500][500];
int dp[500][500];
int N, M;

int dirRow[] = {1, -1, 0, 0};
int dirCol[] = {0, 0, 1, -1};

int dfs(int row, int col)
{
    if(row == N - 1 && col == M - 1)    return 1;
    if(dp[row][col] != -1) return dp[row][col];

    dp[row][col] = 0;
    for(int i = 0; i < 4; i++)
    {
        int nxtRow = row + dirRow[i];
        int nxtCol = col + dirCol[i];
        if(nxtRow < 0 || nxtRow >= N || nxtCol < 0 || nxtCol >= M) continue;
        if(graph[row][col] > graph[nxtRow][nxtCol])
        {
            dp[row][col] += dfs(nxtRow, nxtCol);
        }
    }

    return dp[row][col];
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> N >> M;
    for(int i = 0; i < N; i++)
    {
        for(int j = 0; j < M; j++)
        {
            cin >> graph[i][j];
            dp[i][j] = -1;
        }
    }

    int ret = dfs(0, 0);

    cout << ret << "\n";

    return 0;
}