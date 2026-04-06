#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int N, C;

vector<int> house;

bool canPlace(int dist)
{
    int cnt = 1;
    int cur = house[0];

    for(int i = 1; i < N; i++)
    {
        if(house[i] - cur >= dist)
        {
            cur = house[i];
            cnt++;
            if(cnt == C) return true;
        }
    }
    return false;
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> N >> C;
    house.resize(N);
    for(int i = 0; i < N; i++)
    {
        cin >> house[i];
    }
    sort(house.begin(), house.end());

    int low = 0, mid = 0;
    int high = house[N - 1] - house[0];

    int ans = 0;
    while(low <= high)
    {
        mid = (low + high) / 2;
        if(canPlace(mid))
        {
            ans = mid;
            low = mid + 1;
        }
        else
        {
            high = mid - 1;
        }
    }

    cout << ans << "\n";
    return 0;
}