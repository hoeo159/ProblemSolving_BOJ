#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>

using namespace std;

const int MAX = 999999999;

double graph[16][16];
int    coord[16][2];
vector<double> dp[16];
int N;

double GetDist(int src, int dst)
{
    int sx = coord[src][0], sy = coord[src][1];
    int dx = coord[dst][0], dy = coord[dst][1];

    double dist = sqrt(pow((double)(sx - dx), 2.0) + pow((double)(sy - dy), 2.0));
    return dist;
}

double solve(int cur, int bitmask)
{
    if(dp[cur][bitmask] != -1)  return dp[cur][bitmask];

    if(bitmask == ((1 << N) - 1))
    {
        if(graph[cur][0] > 0)
        {
            return graph[cur][0];
        }
        else
        {
            return MAX;
        }
    }

    double ret = MAX;
    for(int i = 0; i < N; i++)
    {
        if(graph[cur][i] == 0.0) continue;

        if(!(bitmask & (1 << i))) // 방문 안했다면
        {
            ret = min(ret, graph[cur][i] + solve(i, bitmask | (1 << i)));
        }
    }
    dp[cur][bitmask] = ret;

    return ret;
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> N;
    int bitLen = (1 << N);
    for(int i = 0; i < N; i++)
    {
        dp[i].resize(bitLen, -1);
    }

    for(int i = 0; i < N; i++)
    {
        int row, col;
        cin >> row >> col;
        coord[i][0] = row, coord[i][1] = col;
    }

    for(int i = 0; i < N; i++)
    {
        graph[i][i] = 0.0;
        for(int j = i + 1; j < N; j++)
        {
            double dist = GetDist(i, j);
            graph[i][j] = dist;
            graph[j][i] = dist;
        }
    }

    double ret = solve(0, 1);    // start at 0
    printf("%.7lf", ret);
    return 0;
}