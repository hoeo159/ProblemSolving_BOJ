#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

#define MAX_N 21

vector<pair<int, int>> dragon;
vector<int> direction[MAX_N];
bool graph[101][101];

int N;

// 0: x좌표가 증가하는 방향 (→)
// 1: y좌표가 감소하는 방향 (↑)
// 2: x좌표가 감소하는 방향 (←)
// 3: y좌표가 증가하는 방향 (↓)

pair<int, int> NextStep(int dir)
{
    pair<int, int> ret;
    switch (dir)
    {
    case 0:
        ret = {0, 1};
        break;
    case 1:
        ret = {-1, 0};
        break;
    case 2:
        ret = {0, -1};
        break;
    case 3:
        ret = {1, 0};
        break;
    default:
        ret = {0, 0};
        break;
    }
    return ret;
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> N;
    dragon.resize(N + 1);

    int ret = 0;

    for(int i = 0; i < N; i++)
    {
        int r, c, d, g;
        cin >> c >> r >> d >> g;
        dragon[i] = {r, c};
        direction[i].push_back(d);
        for(int j = 1; j <= g; j++)
        {
            int len = direction[i].size();
            for(int l = len - 1; l >= 0; l--)
            {
                direction[i].push_back(((direction[i][l] + 1) % 4));
            }
        }
    }

    for(int i = 0; i < N; i++)
    {
        int srcRow = dragon[i].first;
        int srcCol = dragon[i].second;
        graph[srcRow][srcCol] = true;
        pair<int, int> cur = dragon[i];
        int len = direction[i].size();
        for(int j = 0; j < len; j++)
        {
            pair<int, int> nxt = NextStep(direction[i][j]);
            cur.first += nxt.first;
            cur.second += nxt.second;
            
            if(cur.first < 0 || cur.first > 100 || cur.second < 0 || cur.second > 100)
                continue;
            
            graph[cur.first][cur.second] = true;
        }
    }

    for(int i = 0; i < 100; i++)
    {
        for(int j = 0; j < 100; j++)
        {
            pair<int, int> a = {i, j};
            pair<int, int> b = {i + 1, j};
            pair<int, int> c = {i, j + 1};
            pair<int, int> d = {i + 1, j + 1};
            if(graph[a.first][a.second] && graph[b.first][b.second]
                 && graph[c.first][c.second] && graph[d.first][d.second])
            {
                ret++;
            }
        }
    }

    cout << ret << "\n";

    return 0;
}