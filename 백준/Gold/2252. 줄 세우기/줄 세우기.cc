#include <iostream>
#include <algorithm>
#include <queue>
#include <vector>

using namespace std;

int N, M;

vector<int> inDegree;
vector<int> graph[32001];
queue<int> q;
vector<int> ret;

int main()
{
    cin >> N >> M;
    inDegree.resize(N + 1);
    for(int i = 0; i < M; i++)
    {
        int src, dst;
        cin >> src >> dst;
        inDegree[dst]++;
        graph[src].push_back(dst);
    }

    int init = 0;

    for(int i = 1; i <= N; i++)
    {
        if(inDegree[i] == 0)
        {
            q.push(i);
        }
    }

    while(!q.empty())
    {
        int cur = q.front();
        ret.push_back(cur);
        q.pop();
        int len = graph[cur].size();
        for(int i = 0; i < len; i++)
        {
            int nxt = graph[cur][i];
            inDegree[nxt]--;
            if(inDegree[nxt] == 0)  q.push(nxt);
        }
    }

    for(int i = 0; i < ret.size(); i++)
    {
        cout << ret[i] << " ";
    }
    cout << "\n";
    return 0;
}