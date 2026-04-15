#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

int N, num;
double sum = 0;
vector<int> v;
bool compare(const pair<int, int> &a, const pair<int, int> &b);

int main()
{
    ios::sync_with_stdio(0), cin.tie(0);

    cin >> N;
    v.resize(N);
    for (int i = 0; i < N; i++)
    {
        cin >> num;
        sum += num;
        v[i] = num;
    }

    // solve mean
    sort(v.begin(), v.end());
    if (sum / N < 0 && sum / N > -0.5)
        cout << 0 << endl;
    else
        cout << round(sum / N) << endl;

    // solve median
    cout << v[N / 2] << endl;

    // solve frequency
    vector<pair<int, int>> vp;
    for (int i = 0; i < N; i++)
    {
        bool find = false;
        for (auto &tmp : vp)
        {
            if (tmp.first == v[i])
            {
                tmp.second++;
                find = true;
                break;
            }
        }
        if (!find)
        {
            vp.push_back({v[i], 1});
        }
    }

    sort(vp.begin(), vp.end(), compare);

    if (vp[0].second == vp[1].second)
        cout << vp[1].first << endl;
    else
        cout << vp[0].first << endl;

    // solve range
    cout << v[N - 1] - v[0] << endl;

    return 0;
}

bool compare(const pair<int, int> &a, const pair<int, int> &b)
{
    if (a.second == b.second)
    {
        return a.first < b.first;
    }
    return a.second > b.second;
}
