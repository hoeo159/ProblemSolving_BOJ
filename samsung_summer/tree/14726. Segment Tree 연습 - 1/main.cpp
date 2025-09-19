#include<iostream>
#include <vector>
#include <climits>
#include <algorithm>

using namespace std;

int N, Q;

vector<int> v;
vector<int> minSegTree;
vector<int> maxSegTree;
vector<int> ret;

int initMinSeg(int* tree, int node, int start, int end)
{
    if(start == end) return tree[node] = v[start];

    int mid = (start + end) / 2;
    int a = initMinSeg(tree, node * 2, start, mid);
    int b = initMinSeg(tree, node * 2 + 1, mid + 1, end);
    return tree[node] = min(a, b);
}

int initMaxSeg(int* tree, int node, int start, int end)
{
    if(start == end) return tree[node] = v[start];

    int mid = (start + end) / 2;
    int a = initMaxSeg(tree, node * 2, start, mid);
    int b = initMaxSeg(tree, node * 2 + 1, mid + 1, end);
    return tree[node] = max(a, b);
}

// qs qe : v의 질의 구간, ts te : tree의 구간
int queryMin(int* tree, int node, int ts, int te, int qs, int qe)
{
    if(ts > qe || te < qs) return INT_MAX;
    if(ts >= qs && te <= qe) return tree[node];

    int mid = (ts + te) / 2;
    int a = queryMin(tree, node * 2, ts, mid, qs, qe);
    int b = queryMin(tree, node * 2 + 1, mid + 1, te, qs, qe);
    return min(a, b);
}

int queryMax(int* tree, int node, int ts, int te, int qs, int qe)
{
    if(ts > qe || te < qs) return INT_MIN;
    if(ts >= qs && te <= qe) return tree[node];

    int mid = (ts + te) / 2;
    int a = queryMax(tree, node * 2, ts, mid, qs, qe);
    int b = queryMax(tree, node * 2 + 1, mid + 1, te, qs, qe);
    return max(a, b);
}

// index : 수정할 인덱스
void updateMin(int* tree, int node, int start, int end, int index, int value)
{
    if(start > index || end < index)    return;
    if(start == end)
    {
        tree[node] = value;
        return;
    }

    int mid = (start + end) / 2;
    
    updateMin(tree, node * 2, start, mid, index, value);
    updateMin(tree, node * 2 + 1, mid + 1, end, index, value);
    tree[node] = min(tree[node * 2], tree[node * 2 + 1]);

    return;
}

void updateMax(int* tree, int node, int start, int end, int index, int value)
{
    if(start > index || end < index)    return;
    if(start == end)
    {
        tree[node] = value;
        return;
    }

    int mid = (start + end) / 2;
    updateMax(tree, node * 2, start, mid, index, value);
    updateMax(tree, node * 2 + 1, mid + 1, end, index, value);
    tree[node] = max(tree[node * 2], tree[node * 2 + 1]);

    return;
}

int main(int argc, char** argv)
{
    ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	int test_case;
	int T;
	freopen("input.txt", "r", stdin);
	cin>>T;
	for(test_case = 1; test_case <= T; ++test_case)
	{
        cin >> N >> Q;
        v.clear();
        v.resize(N);

        ret.clear();
        minSegTree.clear(), maxSegTree.clear();
        minSegTree.resize(4 * N), maxSegTree.resize(4 * N);

        for(int i = 0; i < N; i++)
        {
            cin >> v[i];
        }

        initMinSeg(minSegTree.data(), 1, 0, N - 1);
        initMaxSeg(maxSegTree.data(), 1, 0, N - 1);

        // 0 a b : v_a를 b로 바꾼다
        // 1 a b : max(v_a, v_a+1 ... v_b-1) - min(v_a, v_a+1 ... v_b-1) 출력한다
        for(int i = 0; i < Q; i++)
        {
            int cmd, a, b;
            cin >> cmd >> a >> b;
            if(cmd == 0)
            {
                // update
                v[a] = b;
                updateMin(minSegTree.data(), 1, 0, N - 1, a, b);
                updateMax(maxSegTree.data(), 1, 0, N - 1, a, b);
            }
            else if(cmd == 1)
            {
                // query
                int minVal = queryMin(minSegTree.data(), 1, 0, N - 1, a, b - 1);
                int maxVal = queryMax(maxSegTree.data(), 1, 0, N - 1, a, b - 1);
                ret.push_back(maxVal - minVal);
            }
        }

        int tmplen = ret.size();
        cout << "#" << test_case;
        for(int i = 0; i < tmplen; i++)
        {
            cout << " " << ret[i];
        }
        cout << "\n";
    }

	return 0;
}