#include <vector>
#include <algorithm>
#include <climits>

#define MAX_N 100000

// 구간 합 세그먼트 트리
class SegTree
{
    int t[MAX_N * 4];
    int lazy[MAX_N * 4];
public:
    SegTree()
    {
        std::fill(t, t + MAX_N * 4, 0);
        std::fill(lazy, lazy + MAX_N * 4, 0);
    }

    void push(int node, int start, int end)
    {
        if(lazy[node] != 0)
        {
            t[node ] += (end - start + 1) * lazy[node];
            if(start != end) // not leaf node
            {
                lazy[node * 2] += lazy[node];
                lazy[node * 2 + 1] += lazy[node];
            }
            lazy[node] = 0;
        }
    }

    void build(const std::vector<int>& data)
    {
        build_recursive(data, 1, 0, MAX_N - 1);
    }

    void build_recursive(const std::vector<int>& data, int node, int start, int end)
    {
        if(start == end) t[node] = data[start];
        else
        {
            int mid = (start + end) / 2;
            build_recursive(data, node * 2, start, mid);
            build_recursive(data, node * 2 + 1, mid + 1, end);
            t[node] = t[node * 2] + t[node * 2 + 1];
        }
        return;
    }

    // node : 현재 노드 인덱스, start, end : 현재 노드가 담당하는 구간, index : 업데이트할 위치, value : 업데이트할 값
    void update(int node, int start, int end, int index, int value)
    {
        push(node, start, end);

        if(start == end) t[node] = value;
        else
        {
            int mid = (start + end) / 2;
            if(index <= mid) update(node * 2, start, mid, index, value);
            else update(node * 2 + 1, mid + 1, end, index, value);

            t[node] = t[node * 2] + t[node * 2 + 1];
        }
        return;
    }

    void update(int index, int value)
    {
        update(1, 0, MAX_N - 1, index, value);
        return;
    }

    int query(int node, int start, int end, int left, int right)
    {
        push(node, start, end);
        if(right < start || end < left) return 0;
        if(left <= start && end <= right) return t[node];

        int mid = (start + end) / 2;
        return query(node * 2, start, mid, left, right) + query(node * 2 + 1, mid + 1, end, left, right);
    }
    
    int query(int left, int right)
    {
        return query(1, 0, MAX_N - 1, left, right); 
    }
};

// 각 도로 type index를 가지고 있는 구간 연결 리스트
std::vector<int> roadType[1001];
// N - 1 개의 구간 각 도로의 종류(종류는 M개 있음 0 ~ M - 1)
std::vector<int> intervalType;
// 각 구간의 현재 통과 예상 시간
std::vector<int> timeTable;
SegTree segTree;


// 같은 도로의 종류를 같는 구간은 200개 이하
void init(int N, int M, int mType[], int mTime[])
{
    intervalType.clear(), timeTable.clear();
    intervalType.resize(N - 1), timeTable.resize(N - 1);
    for(int i = 0; i < M; i++)
    {
        roadType[i].clear();
    }

    for(int i = 0; i < N - 1; i++)
    {
        intervalType[i] = mType[i];
        timeTable[i] = mTime[i];

        int type = mType[i];
        roadType[type].push_back(i);
    }

    for(int i = 0; i < N - 1; i++)
    {
        segTree.update(i, timeTable[i]);
    }
}

void destroy()
{

}

void update(int mID, int mNewTime)
{
    timeTable[mID] = mNewTime;
    segTree.update(mID, mNewTime);
}

int updateByType(int mTypeID, int mRatio256)
{
    int ret = 0;
    std::vector<int>& curTypeList = roadType[mTypeID];
    for(auto i : curTypeList)
    {
        int newTime = timeTable[i] * mRatio256 / 256;

        timeTable[i] = newTime;
        segTree.update(i, newTime);
        ret += newTime;
    }
    return ret;
}

int calculate(int mA, int mB)
{
    if(mA < mB) return segTree.query(mA, mB - 1);
    else if(mA > mB) return segTree.query(mB, mA - 1);
    else return 0;
}