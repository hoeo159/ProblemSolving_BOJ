#include <vector>
#include <queue>
#include <algorithm>

#define MAX_N 100000

using pint = std::pair<int, int>;

struct SegTree
{
    int node[MAX_N * 2];
    int merge(int a, int b)
    {
        return a + b;
    }
    void update(int start, int end, int index, int pos, int value)
    {
        // 리프 노드에 도달
        if(start == end)   node[index] = value;
        else
        {
            int mid = (start + end) / 2;
            // 현재 노드 담당 구간 : start, end 현재 노드 인덱스, 목표 위치 : pos
            if(pos <= mid)  update(start, mid, index * 2, pos, value);
            else            update(mid + 1, end, index * 2 + 1, pos, value);
            node[index] = merge(node[index * 2], node[index * 2 + 1]);
        }
    }

    void update(int pos, int value)
    {
        update(0, MAX_N - 1, 1, pos, value);
    }
    
    int query(int start, int end, int index, int left, int right)
    {
        if(left <= start && end <= right) return node[index];
        else if(left <= end && start <= right)
        {
            int mid = (start + end) / 2;
            // 중간에 있는 경우
            int left_sum = query(start, mid, index * 2, left, right);
            int right_sum = query(mid + 1, end, index * 2 + 1, left, right);
            return merge(left_sum, right_sum);
        }
        else return 0;
    }
    int query(int left, int right)
    {
        return query(0, MAX_N - 1, 1, left, right);
    }
} segTree;

int cityNum, population[10004], dist[10004], roadCnt[10004];
std::priority_queue<pint> pq;

void init(int N, int mPopulation[])
{
    cityNum = N;
    for(int i = 0; i < cityNum; i++) population[i] = mPopulation[i];
    for(int i = 0; i < cityNum - 1; i++) dist[i] = population[i] + population[i + 1];
    for(int i = 0; i < cityNum - 1; i++) roadCnt[i] = 1;

    while(!pq.empty()) pq.pop();

    // 기본적으로 dist 값이 동일한 경우 인덱스가 작은 게 우선순위로
    for(int i = 0; i < cityNum - 1; i++)  pq.push({dist[i], -i});
    for(int i = 0; i < cityNum - 1; i++)  segTree.update(i, dist[i]);

	return;
}

int expand(int M)
{
    int ret;

    while(M--)
    {
        int curIdx = -pq.top().second;
        pq.pop();

        roadCnt[curIdx]++;
        pq.push({dist[curIdx]/roadCnt[curIdx], -curIdx});
        segTree.update(curIdx, dist[curIdx]/roadCnt[curIdx]);

        ret = dist[curIdx]/roadCnt[curIdx];
    }
	return ret;
}

int calculate(int mFrom, int mTo)
{
    int x = std::min(mFrom, mTo);
    int y = std::max(mFrom, mTo);
    
	return segTree.query(x, y-1);
}

int from, to, k;

bool possible(int x)
{
    int cnt = 0, sum = 0;
    for(int i = from; i <= to; i++)
    {
        if(population[i] > x)   return false;

        if(sum + population[i] > x)
        {
            cnt++;
            sum = 0;
        }

        sum += population[i];
    }

    if(sum > 0) cnt++;

    return cnt <= k;
}

int divide(int mFrom, int mTo, int K)
{
    from = mFrom;
    to = mTo;
    k = K;
    int left = 0, right = 10000004;
    while(left + 1 < right)
    {
        int mid = (left + right) / 2;

        if(possible(mid))   right = mid;
        else    left = mid;
    }
	return right;
}