#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int dp[101][100001];
vector<int> weight, cost;
int N, M;

void solve(){
    for(int i = 1; i <= N; i++){
        for(int j = 1; j <= M; j++){
            if(weight[i] <= j){
                dp[i][j] = max(dp[i-1][j], dp[i-1][j-weight[i]]+ cost[i]);
            }
            else{
                dp[i][j] = dp[i-1][j];
            }
        }
    }
    cout << dp[N][M] << "\n";
    return;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    cin >> N >> M;
    weight.resize(N + 1);
    cost.resize(N + 1);
    for(int i = 1; i <= N; i++){
        cin >> weight[i] >> cost[i];
    }
    solve();
    return 0;
}