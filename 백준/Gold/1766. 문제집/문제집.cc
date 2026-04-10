#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

int N, M;

vector<int> inDegree;
vector<int> graph[32001];
priority_queue<int, vector<int>, greater<int>> pq; 
vector<int> ret;

void solve()
{
    while(!pq.empty())
    {
        int cur = pq.top();
        ret.push_back(cur);
        pq.pop();
        int len = graph[cur].size();
        for(int i = 0; i < len; i++)
        {
            int nxt = graph[cur][i];
            inDegree[nxt]--;
            if(inDegree[nxt] == 0)  pq.push(nxt);
        }
    }
    return;
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> N >> M;
    inDegree.resize(N);

    for(int i = 0; i < M; i++)
    {
        int src, dst;
        cin >> src >> dst;
        graph[src].push_back(dst);
        inDegree[dst]++;
    }

    for(int i = 1; i <= N; i++)
    {
        if(inDegree[i] == 0)
        {
            pq.push(i);
        }
    }

    solve();

    int len = ret.size();
    for(int i = 0; i < len; i++)
    {
        cout << ret[i] << " ";
    }
    cout << "\n";

    return 0;
}