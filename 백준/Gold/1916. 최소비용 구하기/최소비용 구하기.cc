#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <climits>

using namespace std;

int N, M;
int SRC, DST;
vector<pair<int, int>> graph[1001]; // graph[src] = {dst, cost}
priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;

void solve()
{
    vector<int> dist(N + 1, INT_MAX);
    dist[SRC] = 0;

    pq.push({0, SRC}); // first visit
    while(!pq.empty())
    {
        auto v = pq.top();
        int src = v.second; // current visit
        int a = v.first;    // current cost
        pq.pop();

        if(a > dist[src]) continue; // already higher, continue

        for(auto i : graph[src])
        {
            int nxt = i.first;
            int b = i.second;
            int cost = a + b;
            if(dist[nxt] > cost)
            {
                dist[nxt] = a + b;
                pq.push({cost, nxt});
            }
        }
    }
    cout << dist[DST] << "\n";
    return;
}

int main()
{
    cin >> N >> M;

    for(int i = 0; i < M; i++)
    {
        int src, dst, cost;
        cin >> src >> dst >> cost;
        graph[src].push_back({dst, cost});
    }
    cin >> SRC >> DST;

    solve();

    return 0;
}