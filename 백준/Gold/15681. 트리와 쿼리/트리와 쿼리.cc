#include <iostream>
#include <algorithm>
#include <queue>
#include <vector>

using namespace std;

typedef struct NODE{
    vector<int> child;
} Node;

int N, R, Q;
vector<vector<int>> graph;
vector<Node> tree;
vector<int> subsize;


void makeTree(int node, int parent){
    for(auto i : graph[node]){
        if(i == parent) continue;
        tree[node].child.push_back(i);
        makeTree(i, node);
    }
}

int countSubTree(int cur){
    subsize[cur] = 1;
    for(auto i : tree[cur].child){
        if(subsize[i] == 0){
            subsize[cur] += countSubTree(i);
        }
        else{
            subsize[cur] += subsize[i];
        }
    }
    return subsize[cur];
}

// void countSubTree(int cur){
//     queue<int> q;
//     vector<bool> visited(N + 1, false);
//     q.push(cur);
//     visited[cur] = true;
//     int cnt = 1;

//     while(!q.empty()){
//         int node = q.front();
//         q.pop();
//         for(auto i : tree[node].child){
//             if(visited[i]) continue;
//             visited[i] = true;
//             q.push(i);
//             cnt++;
//         }
//     }

//     cout << cnt << "\n";
// }


int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);

    // R is root node
    cin >> N >> R >> Q;
    graph.resize(N + 1);
    tree.resize(N + 1);
    subsize.resize(N + 1, 0);

    for(int i = 0; i < N - 1; i++){
        int u, v;
        cin >> u >> v;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    makeTree(R, 0);    

    for(int i = 0; i < Q; i++){
        int num;
        cin >> num;
        cout << countSubTree(num) << "\n";
    }

    return 0;
}