#include <iostream>
#include <algorithm>
#include <queue>
#include <vector>

using namespace std;

int N, K, T, W;
vector<int> graph[1005];

void solve(vector<int>& cost, vector<int>& degree, vector<int>& ans, queue<int>& q){
    for(int i = 0; i < N; i++){
        if(degree[i] == 0)  q.push(i);
    }
    for(int i = 0; i < N; i++){
        if(q.empty()){
            return;
        }
        int cur = q.front();
        q.pop();
        if(cur == W){
            break;
        }
        for(int i = 0; i < graph[cur].size(); i++){
            int tmp = graph[cur][i];
            ans[tmp] = max(ans[tmp], ans[cur] + cost[cur]);
            degree[tmp]--;
            if(degree[tmp] == 0){
                q.push(tmp);
            }
        }
    }
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    cin >> T;
    for(int testcase = 0; testcase < T; testcase++){
        cin >> N >> K;
        vector<int> cost, degree, ans;
        queue<int> q;
        cost.resize(N), degree.resize(N, 0), ans.resize(N, 0);
        for(int i = 0; i < N; i++){
            cin >> cost[i];
        }
        for(int i = 0; i < K; i++){
            int a, b;
            cin >> a >> b;
            a--;
            b--;
            graph[a].push_back(b);
            degree[b]++;
        }
        cin >> W;
        W--;
        solve(cost, degree, ans, q);
        cout << ans[W] + cost[W] << "\n";
        for(int i = 0; i < N; i++){
            graph[i].erase(graph[i].begin(), graph[i].end());
        }
    }
    return 0;
}