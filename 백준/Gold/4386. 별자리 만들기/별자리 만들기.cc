#include <iostream>
#include <algorithm>
#include <vector>
#include <cstring>
#include <climits>
#include <queue>
#include <cmath>

using namespace std;

#define MAX_N 100

int N;
double ret = 0;
vector<pair<double, double>> star(101);
int parent[101];

int find(int a)
{
    if(parent[a] == a) return a;
    return parent[a] = find(parent[a]);
}

void unite(int a, int b)
{
    a = find(a); b = find(b);
    if(a != b) parent[a] = b;
}

struct Edge
{
    double dist;
    int u, v;
    bool operator<(const Edge &other) const
    {
        return dist < other.dist;
    }
};

vector<Edge> edge;

double getDist(int u, int v)
{
    double a = pow(star[u].first - star[v].first, 2);
    double b = pow(star[u].second - star[v].second, 2);
    return sqrt(a + b);
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    cin >> N;
    for(int i = 0; i < N; i++)
    {
        cin >> star[i].first >> star[i].second;
        parent[i] = i;
    }

    for(int i = 0; i < N; i++)
    {
        for(int j = i + 1; j < N; j++)
        {
            edge.push_back({getDist(i, j), i , j});
        }
    }
    
    sort(edge.begin(), edge.end());
    
    int len = (int)edge.size();
    for(int i = 0; i < len; i++)
    {
        int u = edge[i].u;
        int v = edge[i].v;
        if(find(u) != find(v))
        {
            unite(u, v);
            ret += edge[i].dist;
        }
        else
        {
            continue;
        }
    }




    printf("%.2lf\n", ret);

    return 0;
}