#include <iostream>
#include <algorithm>
#include <cmath>

using namespace std;

long long N, k;

bool canSolve(long long num) // num 보다 작은 숫자 k개 여야한다!!
{
    long long ret = 0;
    for(long long i = 1; i <= N; i++)
    {
        ret += min(num / i, N);
    }
    if(ret >= k)    return true;
    else    return false;
}

long long BinarySearch(long long lo, long long hi)
{
    long long ret = 0;
    while(lo <= hi)
    {
        long long mid = (lo + hi) / 2;
        if(canSolve(mid))
        {
            ret = mid;
            hi = mid - 1;
        }
        else
        {
            lo = mid + 1;
        }
    }
    return ret;
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> N >> k;

    long long ret = BinarySearch(1, N * N);

    cout << ret << "\n";
    return 0;
}
