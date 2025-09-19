#include <queue>
#include <vector>
#include <algorithm>
#include <climits>
#include <cstdio>

#define MAP_SIZE_MAX	350
#define HEALTH_MAX      100
#define GATEWAY_MAX     200

int dx[] = {-1, 1, 0, 0};
int dy[] = {0, 0, -1, 1};

// 지도 1 : 못감, 0 : 감
int graph[MAP_SIZE_MAX][MAP_SIZE_MAX];
// gate id 저장
int gateway[MAP_SIZE_MAX][MAP_SIZE_MAX];
bool visited[MAP_SIZE_MAX][MAP_SIZE_MAX];
int dist[MAP_SIZE_MAX][MAP_SIZE_MAX];
int hp = 0;
int mapSize = 0;
int gateCnt = 0;
bool isRemoved[GATEWAY_MAX];
// idx가 first로 도착까지 걸리는 비용이 second
std::vector<std::pair<int, int>> gatePerGate[GATEWAY_MAX];

struct Node
{
    int x, y, cost;
};

struct State
{
    int gateID;
    int cost;

    bool operator<(const State& other) const
    {
        return cost > other.cost;
    }
};

void init(int N, int mMaxStamina, int mMap[MAP_SIZE_MAX][MAP_SIZE_MAX])
{
    hp = mMaxStamina;
    mapSize = N;

	for(int i = 0; i < N; i++)
	{
		for(int j = 0; j < N; j++)
		{
			graph[i][j] = mMap[i][j];
			visited[i][j] = 0;
            gateway[i][j] = 0;
			dist[i][j] = INT_MAX;
		}
	}

    for(int i = 0; i < GATEWAY_MAX; i++)
    {
        gatePerGate[i].clear();
        isRemoved[i] = false;
    }
}

// 새로운 게이트가 추가될 때, 그 게이트에서부터 다른 모든 게이트까지의 최단 거리를 미리 계산
// 게이트 그래프의 간선 정보 만들기
void addGate(int mGateID, int mRow, int mCol)
{
    gateway[mRow][mCol] = mGateID;
	gateCnt = mGateID;

    for(int i = 0; i < mapSize; i++)
    {
        for(int j = 0; j < mapSize; j++)
        {
            visited[i][j] = false;
        }
    }

    std::queue<Node> pq;
    Node start = {mRow, mCol, 0};
    pq.push(start);
    
    while(!pq.empty())
    {
        int curX = pq.front().x;
        int curY = pq.front().y;
        int curCost = pq.front().cost;
        pq.pop();

        if(gateway[curX][curY] != 0 && curCost != 0)
        {
            int gateID = gateway[curX][curY];
            gatePerGate[mGateID].push_back({gateID, curCost});
            gatePerGate[gateID].push_back({mGateID, curCost});
        }

        if(curCost == hp) continue;

        for(int i = 0; i < 4; i++)
        {
            int nextX = curX + dx[i];
            int nextY = curY + dy[i];
            int nextCost = curCost + 1;
            if(nextX < 0 || nextY < 0 || nextX >= mapSize || nextY >= mapSize) continue;
            if(visited[nextX][nextY]) continue;
            if(nextCost > hp) continue;
            if(graph[nextX][nextY] == 1) continue;

            visited[nextX][nextY] = true;
            pq.push({nextX, nextY, nextCost});
        }
    }

    // for debugging
    // printf("Gateways:\n");
    // for(int i = 1; i <= gateCnt; i++)
    // {
    //     printf("Gate %d: ", i);
    //     for(const auto& p : gatePerGate[i])
    //     {
    //         printf("(%d, %d) ", p.first, p.second);
    //     }
    //     printf("\n");
    // }

	return;
}

void removeGate(int mGateID)
{
    isRemoved[mGateID] = true;
	return;
}

int getMinTime(int mStartGateID, int mEndGateID)
{
    int dijkstra_dist[GATEWAY_MAX + 1];
    for(int i = 0; i <= GATEWAY_MAX; i++)
    {
        dijkstra_dist[i] = INT_MAX;
    }

    std::priority_queue<State> pq;
    dijkstra_dist[mStartGateID] = 0;
    pq.push({mStartGateID, 0});

    while(!pq.empty())
    {
        int curGateID = pq.top().gateID;
        int curCost = pq.top().cost;
        pq.pop();

        if(curGateID == mEndGateID) return curCost;

        for(const auto& next : gatePerGate[curGateID])
        {
            int nextGateID = next.first;
            int nextCost = curCost + next.second;

            if(isRemoved[nextGateID]) continue;

            if(nextCost < dijkstra_dist[nextGateID])
            {
                dijkstra_dist[nextGateID] = nextCost;
                pq.push({nextGateID, nextCost});
            }
        }
    }

	return -1;
}