#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <cmath>
#include <climits>
#include <cstring>

using namespace std;

int N, M;

int graph[51][51];
int ans = INT_MAX;
vector<pair<int, int>> virus;
vector<int> candidate;
int dirRow[] = {0, 0, -1, 1};
int dirCol[] = {1, -1, 0, 0};

int BFS()
{
    queue<pair<int, int>> q;
    int visited[51][51];
    int len = candidate.size();
    int ret = 0;
    for(int i = 0; i < N; i++)
    {
        for(int j = 0; j < N; j++)
        {
            visited[i][j] = INT_MAX;
        }
    }

    for(int i = 0 ; i < len; i++)
    {
        q.push(virus[candidate[i]]);
        visited[virus[candidate[i]].first][virus[candidate[i]].second] = 0;
    }
    while(!q.empty())
    {
        pair<int, int> cur = q.front();
        q.pop();
        for(int i = 0; i < 4; i++)
        {
            int nxtRow = cur.first + dirRow[i];
            int nxtCol = cur.second + dirCol[i];

            if(nxtRow < 0 || nxtCol < 0 || nxtRow >= N || nxtCol >= N) continue;
            if(graph[nxtRow][nxtCol] == 1) continue;
            if(visited[nxtRow][nxtCol] != INT_MAX) continue;;


            visited[nxtRow][nxtCol] = visited[cur.first][cur.second] + 1;
            q.push({nxtRow, nxtCol});
        }
    }
    
    for(int i = 0; i < N; i++)
    {
        for(int j = 0; j < N; j++)
        {
            if(graph[i][j] == 0)
            {
                if(visited[i][j] == INT_MAX)
                {
                    return -1;
                }
                else
                {
                    if(ret < visited[i][j]) ret = visited[i][j];
                }
            }
        }
    }

    return ret;
}

void PickAndSolve(int initIndex, int pickCount)
{
    if(pickCount == M)
    {
        int tmp = BFS();
        if(tmp != -1 && tmp < ans)
        {
            ans = tmp;
        }
        return;
    }
    int len = virus.size();
    for(int i = initIndex; i < len; i++)
    {
        candidate.push_back(i);
        PickAndSolve(i + 1, pickCount + 1);
        candidate.pop_back();
    }
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> N >> M;

    for(int i = 0; i < N; i++)
    {
        for(int j = 0; j < N; j++)
        {
            cin >> graph[i][j];
            if(graph[i][j] == 2)
            {
                virus.push_back({i, j});
            }
        }
    }

    PickAndSolve(0, 0);
    if(ans == INT_MAX) ans = -1;
    cout << ans << "\n";
    return 0;
}