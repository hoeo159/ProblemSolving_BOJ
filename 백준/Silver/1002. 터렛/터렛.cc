#include <iostream>
#include <cmath>

using namespace std;

int t;

int main()
{
    ios::sync_with_stdio(0), cin.tie(0);

    cin >> t;

    while (t--)
    {
        double x1, x2, y1, y2, r1, r2;
        cin >> x1 >> y1 >> r1 >> x2 >> y2 >> r2;
        double dist = sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));
        double max_r = max(r1, r2), min_r = min(r1, r2);
        if (x1 == x2 && y1 == y2)
        {
            if (r1 == r2)
                cout << "-1" << endl;
            else
                cout << "0" << endl;
        }

        else
        {
            if (min_r + dist == max_r)
            {
                cout << "1" << endl;
                continue;
            }

            if (min_r + dist < max_r)
            {
                cout << "0" << endl;
                continue;
            }

            if (dist > r1 + r2)
            {
                cout << "0" << endl;
                continue;
            }
            if (dist == r1 + r2)
            {
                cout << "1" << endl;
                continue;
            }
            if (dist < r1 + r2)
            {
                cout << "2" << endl;
                continue;
            }
        }
    }

    return 0;
}
