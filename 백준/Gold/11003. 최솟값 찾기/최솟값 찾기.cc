#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <cmath>

using namespace std;

int N, L;
vector<int> v;
deque<pair<int, int>> dq;


int main()  
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> N >> L;
    v.resize(N);
    
    for(int i = 0; i < N; i++)
    {
        cin >> v[i];
        if(i == 0)
        {
            dq.push_back({v[i], i});
        }
        else
        {
            if(i - dq.front().second >= L)  dq.pop_front();
            while(!dq.empty() && dq.back().first >= v[i])  dq.pop_back();
            dq.push_back({v[i], i});
        }
        int ret = dq.front().first;
        cout << ret << " ";
    }
    cout << "\n";

    return 0;
}