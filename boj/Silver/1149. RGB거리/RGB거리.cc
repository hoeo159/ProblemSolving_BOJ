#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int N, sum = 0;  
int cost[1000][3];
int dp[1000][3];

// 규칙 : i % N, i - 1 % N, i + 1 % N과 색깔이 같으면 안됨

void solve(){
    for(int i = 0; i < N; i++){
        if(i == 0){
            dp[i][0] = cost[i][0];
            dp[i][1] = cost[i][1];
            dp[i][2] = cost[i][2];
        }
        else{
            dp[i][0] = min(dp[i-1][1], dp[i-1][2]) + cost[i][0];
            dp[i][1] = min(dp[i-1][0], dp[i-1][2]) + cost[i][1];
            dp[i][2] = min(dp[i-1][1], dp[i-1][0]) + cost[i][2];
        }
    }
    int ans = min(dp[N-1][0] ,min(dp[N-1][1], dp[N-1][2]));
    cout << ans << "\n";
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    cin >> N;
    for(int i = 0; i < N; i++){
        cin >> cost[i][0] >> cost[i][1] >> cost[i][2];
    }
    solve();
    return 0;
}