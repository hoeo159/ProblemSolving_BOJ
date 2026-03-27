#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <cstring>
#include <climits>

#define MAX_N 1000
#define MAX_M 250000
#define MAX_K 100

using namespace std;

int N, M, K;
vector<pair<int, int>> graph[1001]; // graph[src] = {dset, cost}
priority_queue<int> dist[1001];

void solve()
{
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int,int>>> pq; // pq = cost, dest

    int src = 0;
    pq.push({0, src});
    
    while(!pq.empty())
    {
        int curSrc = pq.top().second;
        int curCost = pq.top().first;
        pq.pop();
        dist[curSrc].push(curCost);

        if((int)dist[curSrc].size() > K)
        {
            dist[curSrc].pop(); 
            continue;
        }

        int len = graph[curSrc].size();

        for(int i = 0; i < len; i++)
        {
            int nxtDest = graph[curSrc][i].first;
            int nxtCost = graph[curSrc][i].second + curCost;

            if(nxtDest < 0 || nxtDest >= N) continue;
            if((int)dist[nxtDest].size() < K)
            {
                pq.push({nxtCost, nxtDest});
            }
            else
            {
                continue;
            }
        }
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    cin >> N >> M >> K;
    for(int i = 0; i < M; i++)
    {
        int src, dst, cost;
        cin >> src >> dst >> cost;
        src--, dst--;
        graph[src].push_back({dst, cost});
    }

    solve();
    for(int i = 0; i < N; i++) {
        if((int)dist[i].size() == K) cout << dist[i].top() << "\n";
        else cout << -1 << "\n";
    }

    return 0;
}