#include <iostream>
#include <algorithm>
#include <vector>
#include <cstring>
#include <cmath>
#include <climits>

using namespace std;

#define MAX_N 100000
#define MAX_M 100000
#define MAX_NUM 1000000001
#define MIN_NUM 1

int N, M;

vector<int> v;
vector<int> segMinTree;
vector<int> segMaxTree;

void build(int node, int start, int end, int mode = 0)
{
    if(start == end)
    {
        if(!mode) segMinTree[node] = v[start];
        else segMaxTree[node] = v[start];
        return;
    }
    int mid = (start + end) / 2;
    if(!mode)
    {
        build(node * 2, start, mid);
        build(node * 2 + 1, mid + 1, end);
        segMinTree[node] = min(segMinTree[node * 2], segMinTree[node * 2 + 1]);
    }
    else
    {
        build(node * 2, start, mid, 1);
        build(node * 2 + 1, mid + 1, end, 1);
        segMaxTree[node] = max(segMaxTree[node * 2], segMaxTree[node * 2 + 1]);
    }
}

int query(int node, int start, int end, int left, int right, int mode = 0)
{
    if(!mode)
    {
        if(right < start || end < left) return MAX_NUM;
        if(left <= start && end <= right)   return segMinTree[node];
        int mid = (start + end) / 2;
        return min(query(node * 2, start, mid, left, right),
            query(node * 2 + 1, mid + 1, end, left, right));
    }
    else
    {
        if(right < start || end < left) return MIN_NUM;
        if(left <= start && end <= right)   return segMaxTree[node];
        int mid = (start + end) / 2;
        return max(query(node * 2, start, mid, left, right, 1),
            query(node * 2 + 1, mid + 1, end, left, right, 1));
    }
}

void update(int node, int start, int end, int index, int val, int mode = 0)
{
    if(!mode)
    {
        if(start == end)
        {
            segMinTree[node] = val;
            return;
        }
        int mid = (start + end) / 2;
        if(index <= mid) update(node * 2, start, mid, index, val);
        else    update(node * 2 + 1, mid + 1, end, index, val);
        segMinTree[node] = min(segMinTree[node * 2], segMinTree[node * 2 + 1]);
    }
    else
    {
        if(start == end)
        {
            segMaxTree[node] = val;
            return;
        }
        int mid = (start + end) / 2;
        if(index <= mid) update(node * 2, start, mid, index, val, 1);
        else    update(node * 2 + 1, mid + 1, end, index, val, 1);
        segMaxTree[node] = max(segMaxTree[node * 2], segMaxTree[node * 2 + 1]);
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    cin >> N >> M;

    v.resize(N);
    segMinTree.resize(4 * N + 1);
    segMaxTree.resize(4 * N + 1);

    for(int i = 0; i < N; i++)
    {
        cin >> v[i];
    }

    build(1, 0, N - 1, 0);
    build(1, 0, N - 1, 1);

    for(int i = 0; i < M; i++)
    {
        int a, b;
        cin >> a >> b;
        int ret1 = query(1, 0, N - 1, a - 1, b - 1, 0);
        int ret2 = query(1, 0, N - 1, a - 1, b - 1, 1);
        cout << ret1 << " " << ret2 << "\n";
    }

    return 0;
}