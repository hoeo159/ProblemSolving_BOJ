#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

vector<int> height;
int N;
int solve(int left, int right)
{
    if (left == right)
        return height[left];
    int mid = (left + right) / 2;

    int ans = max(solve(left, mid), solve(mid + 1, right));

    int leftmid = mid, rightmid = mid + 1;
    int h = min(height[leftmid], height[rightmid]);
    ans = max(ans, h * 2);
    while (left < leftmid || rightmid < right)
    {
        if (rightmid < right && (leftmid == left || height[leftmid - 1] < height[rightmid + 1]))
        {
            rightmid++;
            h = min(h, height[rightmid]);
        }
        else
        {
            leftmid--;
            h = min(h, height[leftmid]);
        }
        ans = max(ans, h * (rightmid - leftmid + 1));
    }
    return ans;
}

int main()
{
    cin >> N;
    height.resize(N);
    for (int i = 0; i < N; i++)
    {
        cin >> height[i];
    }

    cout << solve(0, N - 1);

    return 0;
}