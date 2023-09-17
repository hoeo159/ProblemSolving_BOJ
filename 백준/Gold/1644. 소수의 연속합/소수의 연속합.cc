#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

int N, cnt = 0;
vector<bool> prime; // prime -> false
vector<long long> v;
void solve(){

    v.push_back(0);
    for(int i = 2; i <= sqrt(N); i++){
        if(prime[i])   continue;
        for(int j = i + i; j <= N; j += i){
            prime[j] = true;
        }
    }

    for(int i = 2; i <= N; i++){
        if(!prime[i]){
            long long num = v.back() + i;
            v.push_back(num);
        }
    }
    
    // for(auto i : v){
    //     cout << i << endl;
    // }

    int left = 0, right = 0, sum = 0;
    while(right < v.size() && left <= right){
        sum = v[right] - v[left];
        if(sum < N){
            right++;
        }
        else{
            if(sum == N){
                cnt++;
            }
            left++;
        }
    }
    cout << cnt << "\n";
    return;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    cin >> N;
    prime.resize(N + 1);
    solve();
    return 0;
}