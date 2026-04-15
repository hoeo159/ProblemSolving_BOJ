#include <iostream>
#include <string>
#include <queue>

using namespace std;

int dx[4] = {1, -1, 0, 0};
int dy[4] = {0, 0, 1, -1};
int N, M, ans = 10001;
int map[101][101];
int visited[101][101];
int count[101][101];
string str;
queue<pair<int, int>> q;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N >> M;
    for (int i = 0; i < N; i++)
    {
        cin >> str;
        for (int j = 0; j < M; j++)
        {
            map[i][j] = str[j] - '0';
        }
    }

    q.push(make_pair(0, 0));

    while (!q.empty())
    {
        int x = q.front().first;
        int y = q.front().second;
        q.pop();
        for (int i = 0; i < 4; i++)
        {
            int nx = x + dx[i];
            int ny = y + dy[i];
            if ((nx >= 0 && nx < N) && (ny >= 0 && ny < M) && map[nx][ny] == 1 && visited[nx][ny] == 0)
            {
                count[nx][ny] = count[x][y] + 1;
                visited[nx][ny] = 1;
                q.push(make_pair(nx, ny));
            }
        }
    }

    cout << count[N - 1][M - 1] + 1 << "\n";
}