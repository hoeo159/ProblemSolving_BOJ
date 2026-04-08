#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <climits>

using namespace std;

string str;
vector<int> ret;
int LEN = 0;
bool dp[2501][2501];

void buildDP()
{
    for(int i = 0; i < LEN; i++)
    {
        dp[i][i] = true;
        if(i > 0)
        {
            dp[i-1][i] = (str[i-1] == str[i]);
        }
    }
    
    for(int len = 2; len < LEN; len++)
    {
        for(int i = 0; i < LEN - len; i++)
        {
            int src = i, dst = i + len;
            dp[src][dst] = dp[src + 1][dst - 1] && (str[src] == str[dst]);
        }
    }
}

void solve()
{
    ret[0] = 1;
    for(int i = 1; i < LEN; i++)
    {
        int tmp = INT_MAX;
        if(dp[0][i])    tmp = 1;
        for(int j = 1; j <= i; j++)
        {
            if(dp[j][i])
            {
                if(tmp > ret[j - 1] + 1)
                {
                    tmp = ret[j - 1] + 1;
                }
            }
        }
        ret[i] = tmp;
    }
    return;
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> str;

    LEN = str.length();
    ret.resize(LEN, 0);

    buildDP();
    solve();

    cout << ret[LEN - 1] << "\n";

    return 0;
}