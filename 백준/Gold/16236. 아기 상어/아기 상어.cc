#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <cstring>

#define MAX_N 20;
int N, M, ret = 0;

int graph[21][21];
int dirRow[] = {0, 0, 1, -1};
int dirCol[] = {1, -1, 0, 0};
bool endFlag = false;

int dist[21][21];

using namespace std;

struct Candidate
{
    int distance;
    int row, col;
    bool operator<(const Candidate &other) const
    {
        if(distance != other.distance)
            return distance < other.distance;
        if(row != other.row)
            return row < other.row;
        return col < other.col;
    }
};

struct Shark
{
    int size = 2;
    int eat = 2;
    int row, col;
};

Shark shark;

void move()
{
    queue<pair<int, int>> q;
    vector<Candidate> cand;
    memset(dist, -1, sizeof(dist));
    for(int i = 0; i < N; i++)
    {
        for(int j = 0; j < N; j++)
        {
            if(graph[i][j] == 9)
            {
                q.push({i, j});
                dist[i][j] = 0;
                shark.row = i, shark.col = j;
                break;
            }
        }
    }

    while(!q.empty())
    {
        auto cur = q.front();
        q.pop();
        int curDist = dist[cur.first][cur.second];
        for(int i = 0; i < 4; i++)
        {
            int nxtRow = cur.first + dirRow[i];
            int nxtCol = cur.second + dirCol[i];

            if(nxtRow < 0 || nxtRow >= N || nxtCol < 0 || nxtCol >= N) continue;
            if(graph[nxtRow][nxtCol] > shark.size) continue;
            if(dist[nxtRow][nxtCol] == -1)
            {
                q.push({nxtRow, nxtCol});
                dist[nxtRow][nxtCol] = curDist + 1;
                if(graph[nxtRow][nxtCol] < shark.size && graph[nxtRow][nxtCol] > 0)
                {
                    cand.push_back({curDist + 1, nxtRow, nxtCol});
                }
            }
        }
    }

    sort(cand.begin(), cand.end());

    if(cand.size() == 0)
    {
        endFlag = true;
        return;
    }

    int eatRow = cand[0].row;
    int eatCol = cand[0].col;
    int eatDist = cand[0].distance;

    shark.eat--;
    if(shark.eat == 0)
    {
        shark.size++;
        shark.eat = shark.size;
    }
    graph[shark.row][shark.col] = 0;
    graph[eatRow][eatCol] = 9;
    ret += eatDist;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cin >> N;
    for(int i = 0; i < N; i++)
    {
        for(int j = 0; j < N; j++)
        {
            cin >> graph[i][j];
        }
    }

    while(!endFlag)
    {
        move();
    }

    cout << ret << "\n";
    return 0;
}