#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

vector<int> v;
vector<int> dp;

int N, k;

int main()  
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> N >> k;

    v.resize(N, 0);
    dp.resize(10001, 0);

    dp[0] = 1;

    for(int i = 0; i < N; i++)
    {
        cin >> v[i];
    }

    for(int i = 0; i < N; i++)
    {
        int curCoin = v[i];
        for(int j = 1; j <= 10000; j++)
        {
            if(j - curCoin >= 0)
            {
                dp[j] += dp[j - curCoin];
            }
        }
    }


    cout << dp[k] << "\n";
    return 0;
}