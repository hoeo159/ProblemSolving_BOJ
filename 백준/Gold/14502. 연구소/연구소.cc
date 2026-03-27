#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <cstring>

int N, M, ret = 0;
#define MAX_N 8;
using namespace std;

int graph[9][9];
bool visited[9][9];
int dirRow[4] = {0, 1, -1, 0};
int dirCol[4] = {1, 0, 0, -1};

void solve(int r1, int c1, int r2, int c2, int r3, int c3)
{
    int _ret = 0;
    memset(visited, false, sizeof(visited));
    queue<pair<int, int>> q;


    for(int i = 0; i < N; i++)
    {
        for(int j = 0; j < M; j++)
        {
            if(graph[i][j] == 2)    q.push({i, j});  
        }
    }
    while(!q.empty())
    {
        auto cur = q.front();
        q.pop();
        visited[cur.first][cur.second] = true; 
        for(int i = 0; i < 4; i++)
        {
            int nxtRow = cur.first + dirRow[i];
            int nxtCol = cur.second + dirCol[i];

            if(nxtRow < 0 || nxtRow >= N || nxtCol < 0 || nxtCol >= M) continue;
            if(visited[nxtRow][nxtCol]) continue;
            if(graph[nxtRow][nxtCol] != 0) continue;

            q.push({nxtRow, nxtCol});
        }
    }

    for(int i = 0; i < N; i++)
    {
        for(int j = 0; j < M; j++)
        {
            if(graph[i][j] == 0 && !visited[i][j]) _ret++;
        }
    }

    if(_ret > ret)  ret = _ret;

    return;
}

int main()
{
    cin >> N >> M;
    
    for(int i = 0; i < N; i++)
    {
        for(int j = 0; j < M; j++)
        {
            cin >> graph[i][j];
        }
    }

    for(int t1 = 0; t1 < N * M; t1++)
    {
        int row1 = t1 / M;
        int col1 = t1 % M;
        if(graph[row1][col1] != 0) continue;
        for(int t2 = 0; t2 < N * M; t2++)
        {
            int row2 = t2 / M;
            int col2 = t2 % M;
            if(t1 == t2)    continue;
            if(graph[row2][col2] != 0) continue;

            for(int t3 = 0; t3 < N * M; t3++)
            {
                int row3 = t3 / M;
                int col3 = t3 % M;
                if(t2 == t3 || t1 == t3) continue;
                if(graph[row3][col3] != 0) continue;
                graph[row1][col1] = 1, graph[row2][col2] = 1, graph[row3][col3] = 1;
                solve(row1, col1, row2, col2, row3, col3);
                graph[row1][col1] = 0, graph[row2][col2] = 0, graph[row3][col3] = 0;
            }
        }
    }

    cout << ret << "\n";
    return 0;
}