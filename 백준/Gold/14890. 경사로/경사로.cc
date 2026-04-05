#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>

using namespace std;

int N, L;
int graph[101][101];

bool RowTest(int curRow)
{
    int prev = -1;
    vector<bool> hillCheck;
    hillCheck.resize(N + 1, false);
    for(int i = 0; i < N; i++)
    {
        int cur = graph[curRow][i];
        if(prev == -1)
        {
            prev = cur;
            continue;
        }
        int a = prev - cur;
        if(abs(a) > 1)  return false;
        if(a == 0)  continue;
        if(a > 0) // 내려가는 방향 + L
        {
            if(i + L - 1 >= N)  return false;
            for(int j = 0; j < L; j++)
            {
                if(hillCheck[i + j])    return false;
                hillCheck[i + j] = true;
            }
        }
        else    // 올라가는 방향 - L
        {
            int start = i - L;
            if(start < 0)   return false;
            for(int j = 0; j < L; j++)
            {
                if(hillCheck[start + j])    return false;
                hillCheck[start + j] = true;
            }
        }
        prev = cur;
    }
    return true;
}

bool ColTest(int curCol)
{
    int prev = -1;
    vector<bool> hillCheck;
    hillCheck.resize(N + 1, false);
    for(int i = 0; i < N; i++)
    {
        int cur = graph[i][curCol];
        if(prev == -1)
        {
            prev = cur;
            continue;
        }
        int a = prev - cur;
        if(abs(a) > 1)  return false;
        if(a == 0)  continue;
        if(a > 0) // 내려가는 방향 + L
        {
            if(i + L - 1 >= N)  return false;
            for(int j = 0; j < L; j++)
            {
                if(hillCheck[i + j])    return false;
                hillCheck[i + j] = true;
            }
        }
        else    // 올라가는 방향 - L
        {
            int start = i - L;
            if(start < 0)   return false;
            for(int j = 0; j < L; j++)
            {
                if(hillCheck[start + j])    return false;
                hillCheck[start + j] = true;
            }
        }
        prev = cur;
    }
    return true;
}

bool Test(int index, bool mode)
{
    if(mode)
        return RowTest(index);
    else
        return ColTest(index);
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    int ret = 0;

    cin >> N >> L;

    for(int i = 0; i < N; i++)
    {
        for(int j = 0; j < N; j++)
        {
            cin >> graph[i][j];
        }
    }

    for(int i = 0; i < N; i++)
    {
        if(Test(i, true)) ret++;
    }
        for(int i = 0; i < N; i++)
    {
        if(Test(i, false)) ret++;
    }

    cout << ret << "\n";

    return 0;
}