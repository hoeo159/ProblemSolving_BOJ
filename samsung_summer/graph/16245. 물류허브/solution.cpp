#include <vector>
#include <queue>
#include <cmath>
#include <algorithm>
#include <climits>

int city[2801], cityCnt;

struct Road
{
    // cid는 목적지 도시임!!
    int cid, cost;
};

std::vector<Road> road[601], roadRev[601];
int dist[601];
bool visited[601];

// s 출발 e 도착 mCost 비용
int init(int N, int sCity[], int eCity[], int mCost[]) {
    for(int i = 0; i < N; i++)
    {
        city[i] = sCity[i];
        city[i + N] = eCity[i];
    }

    std::sort(city, city + 2 * N);
    cityCnt = std::unique(city, city + 2 * N) - city;

    for(int i = 0; i < cityCnt; i++)
    {
        road[i].clear();
        roadRev[i].clear();
    }

    for(int i = 0; i < N; i++)
    {
        // binary search로 city[i] 위치 찾기(포인터 끼리 빼면 인덱스가 된다)
        int u = std::lower_bound(city, city + cityCnt, sCity[i]) - city;
        int v = std::lower_bound(city, city + cityCnt, eCity[i]) - city;

        road[u].push_back({v, mCost[i]});
        roadRev[v].push_back({u, mCost[i]});
    }

	return cityCnt;
}

void add(int sCity, int eCity, int mCost) {
    int u = std::lower_bound(city, city + cityCnt, sCity) - city;
    int v = std::lower_bound(city, city + cityCnt, eCity) - city;

    road[u].push_back({v, mCost});
    roadRev[v].push_back({u, mCost});
	return;
}

void solveInit()
{
    for(int i = 0; i < 601; i++)
    {
        dist[i] = INT_MAX;
        visited[i] = 0;
    }
}

int solve(int start, std::vector<Road> *road)
{
    solveInit();
    dist[start] = 0;
    
    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<>> pq;
    pq.push({0, start});

    while(!pq.empty())
    {
        int curCost = pq.top().first;
        int curCity = pq.top().second;
        pq.pop();

        if(dist[curCity] < curCost) continue;

        for(const auto &r : road[curCity])
        {
            int dstCity = r.cid;
            int roadCost = r.cost;
            int newCost = curCost + roadCost;
            if(newCost < dist[dstCity])
            {
                dist[dstCity] = newCost;
                pq.push({newCost, dstCity});
            }
        }
    }

    int ret = 0;
    for(int i = 0; i < cityCnt; i++)
    {
        if(dist[i] != INT_MAX) ret += dist[i];
    }
    return ret;
}

int cost(int mHub) {
    int curId = std::lower_bound(city, city + cityCnt, mHub) - city;
    int letsgo = solve(curId, road);
    int comeback = solve(curId, roadRev);
	return letsgo + comeback;
}