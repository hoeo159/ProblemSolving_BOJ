#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int N;
int dpMax[3], dpMin[3];

int main()
{
    cin >> N;
    for(int i = 0; i < N; i++)
    {
        int a, b, c;
        cin >> a >> b >> c;
        if(i == 0)
        {
            dpMax[0] = a, dpMax[1] = b, dpMax[2] = c;
            dpMin[0] = dpMax[0], dpMin[1] = dpMax[1], dpMin[2] = dpMax[2];
        }
        else
        {
            int tmpMax[3], tmpMin[3];
            tmpMax[0] = a + max(dpMax[0], dpMax[1]);
            tmpMax[1] = b + max(dpMax[0], max(dpMax[1], dpMax[2]));
            tmpMax[2] = c + max(dpMax[1], dpMax[2]);
            tmpMin[0] = a + min(dpMin[0], dpMin[1]);
            tmpMin[1] = b + min(dpMin[0], min(dpMin[1], dpMin[2]));
            tmpMin[2] = c + min(dpMin[1], dpMin[2]);

            dpMax[0] = tmpMax[0];
            dpMax[1] = tmpMax[1];
            dpMax[2] = tmpMax[2];
            dpMin[0] = tmpMin[0];
            dpMin[1] = tmpMin[1];
            dpMin[2] = tmpMin[2];
        }
    }

    int ret1 = max(dpMax[0], max(dpMax[1], dpMax[2]));
    int ret2 = min(dpMin[0], min(dpMin[1], dpMin[2]));
    cout << ret1 << " " << ret2 << "\n";
    return 0;
}