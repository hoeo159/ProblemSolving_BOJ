#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

//  /*undirected, connected, weight can be negative
//   Kruskal : greedy, select least cost edge but no cycle
//  Prim : vertex -> select least cost edge*/

typedef struct EDGE{
    int u, v, weight;
} Edge;

int N, M;
int sum = 0;

bool compare(const Edge& a, const Edge& b){
    return a.weight < b.weight;
}

int FindSet(int v, vector<int>& set){
    if(set[v] == -1){
        return v;
    }
    return set[v] = FindSet(set[v], set);
}

void UnionSet(int u, int v, vector<int>& set){
    int setU = FindSet(u, set);
    int setV = FindSet(v, set);
    if(setU != setV){
        set[setU] = setV;
    }
}

void kruskalMST(vector<Edge>& edge, int n){
    vector<int> set(n + 1, -1);

    sort(edge.begin(), edge.end(), compare);

    for(Edge i : edge){
        if(FindSet(i.u, set) != FindSet(i.v, set)){
            UnionSet(i.u, i.v, set);
            sum += i.weight;
        } 
    }
}

void kruskal(){
    cin >> N >> M;
    vector<Edge> edge(M);

    for(int i = 0; i < M; i++){
        cin >> edge[i].u >> edge[i].v >> edge[i].weight;
    }

    kruskalMST(edge, N);
}

typedef pair<int, int> pii; // vertex, weight
vector<vector<pii>> graph; // 인접 리스트 간선에 대한 정보임!!!

void primMST(int startV, int n){
    vector<int> key(n + 1, INT32_MAX); // 정점에 mst에 없는 최소 간선
    vector<bool> inMST(n + 1, false); // mst에 있는가??

    priority_queue<pii, vector<pii>, greater<pii>> pq; // 선택될 가능성이 있는 간선들
    pq.push(make_pair(0, startV));
    key[startV] = 0;

    while(!pq.empty()){
        int pick = pq.top().second; // 정점에 가중치 작은 것
        pq.pop();

        if(inMST[pick])
            continue;
        
        inMST[pick] = true;
        sum += key[pick];

        for(pii i : graph[pick]){
            int v = i.first;
            int w = i.second;

            if(!inMST[v] && w < key[v]){
                pq.push(make_pair(w, v));
                key[v] = w;
            }
        }
    }
}

void prim(){
    cin >> N >> M;
    graph.resize(N + 1);

    for(int i = 0; i < M; i++){
        int u, v, w;
        cin >> u >> v >> w;
        graph[u].push_back(make_pair(v,w));
        graph[v].push_back(make_pair(u,w));
    }

    int startVertex = 1;

    primMST(startVertex, N);
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);

    // kruskal();
    prim();

    cout << sum << "\n";
}