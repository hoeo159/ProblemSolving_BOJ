#include <iostream>
#include <algorithm>
#include <climits>
#include <vector>
#include <cstring>

using namespace std;

#define MAX_C 1000
#define MAX_N 20

int C, N;

int dp[1001] = {0, };
int cost[21], member[21];

int main()
{
    cin >> C >> N;
    memset(dp, 0, sizeof(dp));
    for(int i = 0; i < N; i++)
    {
        cin >> cost[i] >> member[i];
    }

    for(int i = 1; i <= 1000; i++)
    {
        for(int j = 0; j < N; j++)
        {
            int before = max(0, i - member[j]);
            int curCost = dp[before] + cost[j];
            if(dp[i] > curCost || dp[i] == 0)
            {
                dp[i] = curCost;
            }
        }
    }

    cout << dp[C] << "\n";
    return 0;
}