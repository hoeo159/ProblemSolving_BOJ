#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int N, M;
vector<int> v;

bool canSolve(int bill)
{
    int count = 0;
    int cur = 0;
    for(int i = 0; i < N; i++)
    {
        // cout << "cur: " << cur << "\n";
        if(cur < v[i])
        {
            cur = bill;
            count++;
        }
        cur -= v[i];
    }
    // cout << "count : " << count << "\n";
    if(count > M)
    {
        return false;
    }
    
    return true;
}

int BinarySearch(int low, int high)
{
    int ret = 0;
    while(low <= high)
    {
        int mid = (low + high) / 2;
        // cout << "lo : " << low << " hi : " << high << " mid : " << mid << "\n";
        if(canSolve(mid))
        {
            high = mid - 1;
            ret = mid;
        }
        else
        {
            low = mid + 1;
        }
    }
    return ret;
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> N >> M;
    v.resize(N);
    int low = 0;
    int hi = 0;
    for(int i = 0; i < N; i++)
    {
        cin >> v[i];
        hi += v[i];
        if(v[i] > low)
        {
            low = v[i];
        }
    }
    int ret = BinarySearch(low, hi);

    cout << ret << "\n";
    return 0;
}