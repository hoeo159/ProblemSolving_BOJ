#include<iostream>
#include <string>
#include <vector>
#include <queue>
#include <climits>

using namespace std;

int graph[101][101];
bool visited[101][101];
int dist[101][101];
int dx[] = {0, 0, 1, -1};
int dy[] = {1, -1, 0, 0};
int N;

struct Node
{
    int x, y, cost;
    bool operator<(const Node& other) const
    {
        return cost > other.cost;
    }
};

void init()
{
    for(int i = 0; i < 101; i++)
    {
        for(int j = 0; j < 101; j++)
        {
            graph[i][j] = 0;
            visited[i][j] = false;
            dist[i][j] = INT_MAX;
        }
    }
}

int solve()
{
    Node start = {1, 1};
    priority_queue<Node> pq;
    pq.push(start);
    dist[1][1] = graph[1][1];

    while(!pq.empty())
    {
        Node cur = pq.top();
        pq.pop();

        if(visited[cur.x][cur.y])   continue;

        visited[cur.x][cur.y] = true;

        for(int i = 0; i < 4; i++)
        {
            int nxtX = cur.x + dx[i];
            int nxtY = cur.y + dy[i];
            if(nxtX < 1 || nxtY < 1 || nxtX > N || nxtY > N) continue;

            int nxtCost = dist[cur.x][cur.y] + graph[nxtX][nxtY];
            if(nxtCost < dist[nxtX][nxtY])
            {
                dist[nxtX][nxtY] = nxtCost;
                pq.push({nxtX, nxtY, nxtCost});
            }
        }
    }

    return dist[N][N];
}

int main(int argc, char** argv)
{
	int test_case;
	int T;
	freopen("input.txt", "r", stdin);
	cin>>T;
	for(test_case = 1; test_case <= T; ++test_case)
	{
        init();
        cin >> N;
        for(int i = 1; i <= N; i++)
        {
            string str;
            cin >> str;
            for(int j = 1; j <= N; j++)
            {
                graph[i][j] = str[j - 1] - '0';
            }
        }

        int ret = solve();
        cout << "#" << test_case << " " << ret << endl;
	}
	return 0;//정상종료시 반드시 0을 리턴해야합니다.
}