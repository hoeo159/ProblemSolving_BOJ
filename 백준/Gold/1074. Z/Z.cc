#include <iostream>
#include <algorithm>
#include <cmath>
using namespace std;

int n, a, b, cnt = 0;

void solve(int x, int y, int len)
{
    // 기저 사례 사이즈 1짜리 타일은 해당 값을 그대로 출력한다
    if (len == 1)
    {
        if (a == x && b == y)
        {
            cout << cnt << endl;
            exit(0);
        }
        else
            cnt++;
    }
    else
    {
        // 해당 쿼터에 존재하지 않으면 그냥 계산하고 건너뛴다
        if (x + len < a || y + len < b)
        {
            cnt += len * len;
        }
        else
        {
            solve(x, y, len / 2);
            solve(x, y + len / 2, len / 2);
            solve(x + len / 2, y, len / 2);
            solve(x + len / 2, y + len / 2, len / 2);
        }
    }
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cin >> n >> a >> b;

    solve(0, 0, pow(2, n));

    return 0;
}