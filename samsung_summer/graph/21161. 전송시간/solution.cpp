#include <vector>
#include <algorithm>
#include <queue>
#include <climits>

#define MAX_GROUP           300
#define MAX_EDGE            30000
#define MAX_TIME            10000
#define MAX_GROUP_LEADER    3
#define MAX_GROUP_MEMBER    27

struct Node
{
    int index, dist;
};

// groupgraph : group 내부 연결 그래프
// metagraph : group, root 간 연결 그래프(그룹 리더만 영향을 미침)

int groupCnt, metaEdgeCnt;

std::vector<Node> groupGraph[MAX_GROUP + 3][MAX_GROUP_MEMBER + MAX_GROUP_LEADER];
std::vector<Node> metaGraph[3 * MAX_GROUP + 3];

int cvtMetaIndex(int node)
{
    if(node >= 1 && node <= 3) return node - 1; // 루트 노드
    int groupIdx = node / 100; // 1 ~ 300
    int leaderIdx = node % 100 - 1; // 0 ~ 2
    if(leaderIdx < 3)    return 3 * groupIdx + leaderIdx;
    return -1; // member는 포함 x
}

void removeMetaEdge(int src, int dst)
{
    int srcLen = metaGraph[src].size();
    int dstLen = metaGraph[dst].size();
    for(int i = 0; i < srcLen; i++)
    {
        if(metaGraph[src][i].index == dst)
        {
            metaGraph[src].erase(metaGraph[src].begin() + i);
            break;
        }
    }
    for(int i = 0; i < dstLen; i++)
    {
        if(metaGraph[dst][i].index == src)
        {
            metaGraph[dst].erase(metaGraph[dst].begin() + i);
            break;
        }
    }
}

void removeGroupEdge(int src, int dst, int groupIdx)
{
    int srcLen = groupGraph[groupIdx][src].size();
    int dstLen = groupGraph[groupIdx][dst].size();
    for(int i = 0; i < srcLen; i++)
    {
        if(groupGraph[groupIdx][src][i].index == dst)
        {
            groupGraph[groupIdx][src].erase(groupGraph[groupIdx][src].begin() + i);
            break;
        }
    }
    for(int i = 0; i < dstLen; i++)
    {
        if(groupGraph[groupIdx][dst][i].index == src)
        {
            groupGraph[groupIdx][dst].erase(groupGraph[groupIdx][dst].begin() + i);
            break;
        }
    }
}

// group 내부 리더 노드 간 거리 계산 후 metaGraph 반영
void dijkstraGroup(int groupId)
{
    
    for(int LeaderIdx = 0; LeaderIdx < MAX_GROUP_LEADER; LeaderIdx++)
    {
        std::vector<int> dist(MAX_GROUP_MEMBER + MAX_GROUP_LEADER + 1, INT_MAX);
        std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<std::pair<int, int>>> pq;
        dist[LeaderIdx] = 0;
        pq.push({0, LeaderIdx});

        // 리더와 나머지 노드들 간 최단거리 계산
        while(!pq.empty())
        {
            auto [curDist, curNode] = pq.top();
            pq.pop();

            if(curDist != dist[curNode]) continue;

            for(const auto& neighbor : groupGraph[groupId][curNode])
            {
                int nextNode = neighbor.index;
                int newDist = curDist + neighbor.dist;

                if(newDist < dist[nextNode])
                {
                    dist[nextNode] = newDist;
                    pq.push({newDist, nextNode});
                }
            }
        }

        // 가장 짧은 길 찾으면 리더끼리 갱신 -> meta에 반영
        for(int otherIdx = LeaderIdx + 1; otherIdx < MAX_GROUP_LEADER; otherIdx++)
        {
            if(dist[otherIdx] == INT_MAX) continue;

            int metaA = groupId * 3 + LeaderIdx;
            int metaB = groupId * 3 + otherIdx;

            removeMetaEdge(metaA, metaB);
            
            metaGraph[metaA].push_back({metaB, dist[otherIdx]});
            metaGraph[metaB].push_back({metaA, dist[otherIdx]});
        }

    }
}

void init(int N, int K, int mNodeA[], int mNodeB[], int mTime[])
{
    groupCnt = N;
    metaEdgeCnt = 3 + 3 * groupCnt; // 그룹 당 리더 3명 + 루트 3명

    for(int i = 0; i < MAX_GROUP + 3; i++)
    {
        for(int j = 0; j < MAX_GROUP_MEMBER + MAX_GROUP_LEADER; j++)
        {
            groupGraph[i][j].clear();
        }
    }
    for(int i = 0; i < 3 * MAX_GROUP + 3; i++)
    {
        metaGraph[i].clear();
    }

    for(int i = 0; i < K; i++)
    {
        int nodeA = mNodeA[i];
        int nodeB = mNodeB[i];
        int time = mTime[i];

        int groupA = nodeA / 100;
        int groupB = nodeB / 100;
        int metaA = cvtMetaIndex(nodeA);
        int metaB = cvtMetaIndex(nodeB);

        if(groupA != 0 && groupB != 0 && groupA == groupB)
        {
            int memA = nodeA % 100 - 1;
            int memB = nodeB % 100 - 1;
            groupGraph[groupA][memA].push_back({memB, time});
            groupGraph[groupA][memB].push_back({memA, time});
        }
        else
        {
            int metaA = cvtMetaIndex(nodeA);
            int metaB = cvtMetaIndex(nodeB);
            if(metaA != -1 && metaB != -1)
            {
                metaGraph[metaA].push_back({metaB, time});
                metaGraph[metaB].push_back({metaA, time});
            }
        }
    }

    // update Group
    for(int i = 1; i <= groupCnt; i++)
    {
        dijkstraGroup(i);
    }
}

void addLine(int mNodeA, int mNodeB, int mTime)
{
    int nodeA = mNodeA;
    int nodeB = mNodeB;
    int time = mTime;

    int groupA = nodeA / 100;
    int groupB = nodeB / 100;
    int metaA = cvtMetaIndex(nodeA);
    int metaB = cvtMetaIndex(nodeB);

    if(groupA != 0 && groupB != 0 && groupA == groupB)
    {
        int memA = nodeA % 100 - 1;
        int memB = nodeB % 100 - 1;
        groupGraph[groupA][memA].push_back({memB, time});
        groupGraph[groupA][memB].push_back({memA, time});
        dijkstraGroup(groupA);
    }
    else
    {
        if(metaA != -1 && metaB != -1)
        {
            metaGraph[metaA].push_back({metaB, time});
            metaGraph[metaB].push_back({metaA, time});
        }
    }
}

void removeLine(int mNodeA, int mNodeB)
{
    int nodeA = mNodeA;
    int nodeB = mNodeB;

    int groupA = nodeA / 100;
    int groupB = nodeB / 100;
    int metaA = cvtMetaIndex(nodeA);
    int metaB = cvtMetaIndex(nodeB);

    if(groupA != 0 && groupB != 0 && groupA == groupB)
    {
        int memA = nodeA % 100 - 1;
        int memB = nodeB % 100 - 1;
        removeGroupEdge(memA, memB, groupA);
        dijkstraGroup(groupA);
    }
    else
    {
        if(metaA != -1 && metaB != -1)
        {
            removeMetaEdge(metaA, metaB);
        }
    }
}

int checkTime(int mNodeA, int mNodeB)
{
    std::vector<int> dist(metaEdgeCnt, INT_MAX);
    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<std::pair<int, int>>> pq;

    int metaA = cvtMetaIndex(mNodeA);
    int metaB = cvtMetaIndex(mNodeB);

    for(int i = 0; i < metaEdgeCnt; i++)
    {
        dist[i] = INT_MAX;
    }

    dist[metaA] = 0;
    pq.push({0, metaA});

    while(!pq.empty())
    {
        auto [curDist, curNode] = pq.top();
        pq.pop();

        if(curDist != dist[curNode]) continue;
        if(curNode == metaB) return curDist;

        for(auto& edge : metaGraph[curNode])
        {
            int nxtNode = edge.index;
            int nxtDist = edge.dist;

            if(dist[curNode] + nxtDist < dist[nxtNode])
            {
                dist[nxtNode] = dist[curNode] + nxtDist;
                pq.push({dist[nxtNode], nxtNode});
            }
        }
    }

	return -1; // 보장되긴 함!!
}