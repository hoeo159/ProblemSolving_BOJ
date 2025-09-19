#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int N, sum = 0;  
int cost[1000][3];
int dp[1000][3];

// 규칙 : i % N, i - 1 % N, i + 1 % N과 색깔이 같으면 안됨

int solve(int k){
    for(int i = 0; i < N; i++){
        if(i == 0){
            dp[i][k] = cost[i][k];
            dp[i][(k + 1) % 3] = 1001;
            dp[i][(k + 2) % 3] = 1001;
        }
        else if (i < N - 1){
            dp[i][0] = min(dp[i-1][1], dp[i-1][2]) + cost[i][0];
            dp[i][1] = min(dp[i-1][0], dp[i-1][2]) + cost[i][1];
            dp[i][2] = min(dp[i-1][1], dp[i-1][0]) + cost[i][2];
        }
        else{
            dp[i][(k + 1) % 3] = min(dp[i-1][k % 3], dp[i-1][(k + 2) % 3]) + cost[i][(k + 1) % 3];
            dp[i][(k + 2) % 3] = min(dp[i-1][(k + 1) % 3], dp[i-1][k % 3]) + cost[i][(k + 2) % 3];
        }
    }
    int ret = min(dp[N - 1][(k + 1) % 3], dp[N - 1][(k + 2) % 3]);
    return ret;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    cin >> N;
    for(int i = 0; i < N; i++){
        cin >> cost[i][0] >> cost[i][1] >> cost[i][2];
    }
    cout << min(solve(0), min(solve(1), solve(2))) << "\n";
    return 0;
}