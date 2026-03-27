#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <cmath>
#include <climits>
#include <cstring>

#define MAX_N 100000
#define MAX_M 100000

using namespace std;

struct Node
{
    int sum;
    int lazy;
};

int N, M;
vector<int> v;
Node segTree[4 * MAX_N + 10];

void build(int node, int start, int end)
{
    if(start == end)
    {
        segTree[node].sum = v[start];
        segTree[node].lazy = 0;
        return;
    }
    int mid = (start + end) / 2;
    build(node * 2, start, mid);
    build(node * 2 + 1, mid + 1, end);
    segTree[node].sum = segTree[node * 2].sum + segTree[node* 2 + 1].sum;
    segTree[node].lazy = 0;
    return;
}

void pushDown(int node, int start, int end)
{
    if(segTree[node].lazy && start != end)
    {
        int mid = (start + end) / 2;
        segTree[node * 2].sum = (mid - start + 1) - segTree[node * 2].sum;
        segTree[node * 2].lazy = !segTree[node * 2].lazy;

        segTree[node * 2 + 1].sum = (end - mid) - segTree[node * 2 + 1].sum;
        segTree[node * 2 + 1].lazy = !segTree[node * 2 + 1].lazy;

        segTree[node].lazy = 0;
    }
}

// 현재 노드 담당이 start, end / 쿼리는 right, left(고정임!!!) 
int query(int node, int start, int end, int left, int right)
{
    if(segTree[node].lazy)
    {
        pushDown(node, start, end);
    }
    if(right < start || end < left) return 0;
    if(left <= start && end <= right) return segTree[node].sum;

    int mid = (start + end) / 2;
    return query(node * 2, start , mid, left, right) + query(node * 2 + 1, mid + 1, end, left, right);
}

void update(int node, int start, int end, int left, int right)
{
    if(segTree[node].lazy)
    {
        pushDown(node, start, end);
    }
    
    if(right < start || end < left ) return;

    if(start == end)
    {
        segTree[node].sum = !segTree[node].sum;
        return;
    }

    if(left <= start && end <= right)
    {
        segTree[node].sum = (end - start + 1) - segTree[node].sum;
        segTree[node].lazy = !segTree[node].lazy;
        return;
    }
    int mid = (start + end) / 2;
    update(node * 2, start, mid, left, right);
    update(node * 2 + 1, mid + 1, end, left, right);
    segTree[node].sum = segTree[node * 2].sum + segTree[node * 2 + 1].sum;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    cin >> N >> M;
    v.resize(N, 0);

    build(1, 0, N - 1);

    for(int i = 0; i < M; i++)
    {   
        int oper, a, b;
        cin >> oper >> a >> b;
        a--;    b--;
        if(oper == 0)
        {
            update(1, 0, N - 1, a, b);
        }
        if(oper == 1)
        {
            int ret = query(1, 0, N - 1, a, b);
            cout << ret << "\n";
        }
    }
}