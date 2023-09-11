#include <iostream>
#include <algorithm>
#include <queue>
#include <vector>

using namespace std;

int N, K, T, W;
vector<int> cost;
vector<int> graph[1001];

void solve(){
    
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    cin >> T;
    for(int testcase = 0; testcase < T; testcase++){
        cin >> N >> K;
        cost.resize(N);
        for(int i = 0; i < N; i++){
            cin >> cost[i];
        }
        for(int i = 0; i < K; i++){
            int a, b;
            cin >> a >> b;
            graph[a].push_back(b);
        }
        cin >> W;
        solve();
    }
    return 0;
}