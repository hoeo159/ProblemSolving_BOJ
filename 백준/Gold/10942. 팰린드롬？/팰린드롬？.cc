#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>

using namespace std;

int N, M, S, E;
vector<int> v;
bool dp[2001][2001];

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    cin >> N;
    v.resize(N);

    for(int i = 0; i < N; i++){
        cin >> v[i];
    }

    for(int i = 0; i < N - 1; i++){
        dp[i][i] = true;
        if(v[i] == v[i+1])  dp[i][i+1] = true;
    }
    dp[N-1][N-1] = true;

    for(int i = 2; i < N; i++){ // i는 구간 크기!!
        for(int j = 0; j < N - i; j++){
            if(v[j] == v[j + i] && dp[j + 1][j + i - 1]){
                dp[j][j + i] = true;
            }
        }
    }
    cin >> M;
    for(int i = 0; i < M; i++){
        cin >> S >> E;
        if(dp[S-1][E-1]){
            cout << "1\n";
        }
        else    cout << "0\n";  
    }
    return 0;
}