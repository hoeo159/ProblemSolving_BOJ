#include <algorithm>
#include <cmath>

#define MAXCOL 1 << 20
#define MAXNODE 1 << 21

struct Result{
    int top;
    int count;
};

int totalCol = 0;

struct Node
{
    int minValue, maxValue;
    long long sum;

    Node operator+(const Node& b) const
    {
        Node ret;
        ret.minValue = std::min(minValue, b.minValue);
        ret.maxValue = std::max(maxValue, b.maxValue);
        ret.sum = sum + b.sum;
        return ret;
    }
};

struct SegTree
{
    Node node[MAXNODE];
    long long lazy[MAXNODE];

    void update_value(int start, int end, int index, int value)
    {
        node[index].minValue += value;
        node[index].maxValue += value;
        node[index].sum += (end - start + 1) * value; // 현재 노드 합 업데이트
        lazy[index] += value; // 방문할 자식 노드를 위한 표시
    }

    void propagate(int start, int end, int index)
    {
        if(start == end)    return;

        int mid = (start + end) / 2;
        int value = lazy[index];
        update_value(start, mid, index * 2, value);
        update_value(mid + 1, end, index * 2 + 1, value);

        lazy[index] = 0; // 전파 완료 후 초기화
    }

    // 현재 노드 담당 구간 : start, end 현재 노드 인덱스, 목표 구간 : left, right
    void update(int start, int end, int index, int left, int right, int value)
    {
        // 가장 먼저 미뤄둔 작업이 있으면 자식에게 전파
        propagate(start, end, index);
        if(right < start || end < left)  return; // 구간 벗어남

        if(left <= start && end <= right) update_value(start, end, index, value); // 구간이 완전히 겹치는 경우
        else if(left <= end || right <= start) // 양 사이드로 걸칠 때
        {
            int mid = (start + end) / 2;
            update(start, mid, index * 2, left, right, value);
            update(mid + 1, end, index * 2 + 1, left, right, value);
            node[index] = node[index * 2] + node[index * 2 + 1];
        }
    }

    void update(int left, int right, int value)
    {
        update(0, totalCol - 1, 1, left, right, value);
    }

    Node query()
    {
        return node[1];
    }
} segTree;

void init(int C)
{
    totalCol = C;
    for(int i = 0; i < MAXNODE; i++)
    {
        segTree.node[i] = {0, 0, 0};
        segTree.lazy[i] = 0;
    }
}   

Result dropBlocks(int mCol, int mHeight, int mLength)
{
    Result ret;
    ret.top = 0;
    ret.count = 0;

    segTree.update(mCol, mCol + mLength - 1, mHeight);
    Node q = segTree.query();

    ret.top = q.maxValue - q.minValue;
    ret.count = (q.sum - totalCol * (long long)q.minValue) % 1000000;

    return ret;
}
