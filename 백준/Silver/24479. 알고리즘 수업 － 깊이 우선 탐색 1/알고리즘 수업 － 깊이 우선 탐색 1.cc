#include <iostream>
#include <algorithm>
#include <stack>
#include <vector>

using namespace std;

vector<bool> visited;
vector<int> graph[100001];
vector<int> answer;

int V, E, R, strt, fnsh, cnt = 1;

void dfs(int r);

int main()
{
    scanf("%d %d %d", &V, &E, &R);
    visited.resize(V);
    answer.resize(V);
    visited.assign(V, false);

    for (int i = 0; i < E; i++)
    {
        scanf("%d %d", &strt, &fnsh);
        graph[strt].push_back(fnsh);
        graph[fnsh].push_back(strt);
    }

    for (int i = 0; i < V; i++)
        sort(graph[i].begin(), graph[i].end());

    dfs(R);

    for (int i = 0; i < V; i++)
    {
        printf("%d\n", answer[i]);
    }

    return 0;
}

void dfs(int r)
{
    visited[r] = true;
    answer[r - 1] = cnt;
    cnt++;
    for (int i = 0; i < graph[r].size(); i++)
    {
        if (visited[graph[r][i]] == true)
        {
            continue;
        }
        dfs(graph[r][i]);
    }
}