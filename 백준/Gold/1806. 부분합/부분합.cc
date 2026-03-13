#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int N, M, len;

vector<int> sum;

void solve(){

    sum.resize(N + 1, 0);
    len = N;

    for(int i = 1; i <= N; i++){
        int num;
        cin >> num;
        sum[i] = num + sum[i-1];
    }

    if(sum[N] < M){
        len = 0;
    }
    else{
        int left = 0, right = 0;
        while(left <= N){

            int psum = sum[right] - sum[left];

            if(psum >= M){
                if(len >= right - left){
                    len = right - left;
                }
                left++;
            }
            else{
                if(right < N){
                    right++;
                }
                else{
                    break;
                }
            }
        }
    }

    cout << len << "\n";
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    cin >> N >> M;
    solve();
}