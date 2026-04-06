#include <iostream>
#include <algorithm>
#include <queue>
#include <vector>
#include <climits>

using namespace std;

int N, K;
vector<int> visited(200001, 200000);

void solve()
{
    deque<int> dq;
    visited[N] = 0;
    dq.push_back(N);
    while(!dq.empty())
    {
        int cur = dq.front();
        dq.pop_front();

        int nxt = cur - 1;
        int nxtCost = visited[cur] + 1;
        if(nxt >= 0 && visited[nxt] > nxtCost)
        {
            visited[nxt] = nxtCost;
            dq.push_back(nxt);
        }

        nxt = cur + 1;
        if(nxt <= 200000 && visited[nxt] > nxtCost)
        {
            visited[nxt] = nxtCost;
            dq.push_back(nxt);
        }

        nxt = 2 * cur;
        if(nxt > 200000) continue;
        nxtCost = visited[cur];
        if(visited[nxt] > nxtCost)
        {
            visited[nxt] = nxtCost;
            dq.push_front(nxt);
        }
    }
    
    return;
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> N >> K;

    solve();

    cout << visited[K] << "\n";

    return 0;
}