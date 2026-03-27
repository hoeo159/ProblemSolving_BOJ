#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>
#include <queue>
#include <climits>

using namespace std;
#define MAX_N 125;

int graph[126][126];
int dist[126][126];
struct Node
{
    int cost;
    int row, col;
    bool operator<(const Node& other) const
    {
        return cost > other.cost;
    }
};

int dirRow[] = {1, -1, 0, 0};
int dirCol[] = {0, 0, 1, -1};

int N;

int solve()
{
    memset(dist, -1, sizeof(dist));

    priority_queue<Node> pq;
    dist[0][0] = graph[0][0];
    pq.push({dist[0][0], 0, 0});

    while(!pq.empty())
    {
        auto cur = pq.top();
        pq.pop();

        if(cur.row == N - 1 && cur.col == N - 1)
        {
            return cur.cost;
        }

        if(cur.cost > dist[cur.row][cur.col]) continue; // 이미 방문했는데 더 작은 케이스

        for(int i = 0; i < 4; i++)
        {
            int nxtRow = cur.row + dirRow[i];
            int nxtCol = cur.col + dirCol[i];

            if(nxtRow < 0 || nxtRow >= N || nxtCol < 0 || nxtCol >= N) continue;

            int nxtCost = cur.cost + graph[nxtRow][nxtCol];

            if(dist[nxtRow][nxtCol] > nxtCost || dist[nxtRow][nxtCol] == -1)
            {
                dist[nxtRow][nxtCol] = nxtCost;
                pq.push({nxtCost, nxtRow, nxtCol});
            }
        }
    }
    return -1;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    int testcase = 0;
    while(true)
    {
        testcase++;
        cin >> N;
        if(N == 0)  break;
        for(int i = 0; i < N; i++)
        {
            for(int j = 0; j < N; j++)
            {
                cin >> graph[i][j];
            }
        }
        int ret = solve();
        cout << "Problem " << testcase << ": " << ret << "\n";
    }

    return 0;
}