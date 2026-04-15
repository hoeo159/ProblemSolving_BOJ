#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

vector<int> weight;

int N, num, ans = 0;

int main()
{
    ios_base::sync_with_stdio(false), cin.tie(0);
    cin >> N;
    weight.resize(N);
    for (auto &i : weight)
        cin >> i;

    sort(weight.begin(), weight.end());

    for (auto &i : weight)
    {
        if (i > ans + 1)
            break;
        ans += i;
    }

    cout << ans + 1 << endl;
}