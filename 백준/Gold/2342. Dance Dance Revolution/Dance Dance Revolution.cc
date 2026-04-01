#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>
#include <climits>
#include <cstring>

using namespace std;

#define SCORE_MAX 0x3f3f3f3f

int lastStep[5][5];
int curStep[5][5];
vector<int> v;

int CalcScore(int src, int dst)
{
    bool srcEven = (src % 2 == 0);
    bool dstEven = (dst % 2 == 0);

    if(src == 0) return 2;
    if(src == dst) return 1;
    if(srcEven == dstEven) return 4;
    else return 3;

    return -1;
}

int main()  
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int input;

    for(int i = 0; i < 5; i++)
    {
        memset(lastStep[i], SCORE_MAX, sizeof(lastStep[i]));
    }

    cin >> input;
    int score = CalcScore(0, input);
    v.push_back(input);
    lastStep[0][input] = score;

    while(1)
    {
        for(int i = 0; i < 5; i++)
        {
            memset(curStep[i], SCORE_MAX, sizeof(curStep[i]));
        }

        cin >> input;
        
        if(input == 0) break;
        v.push_back(input);

        for(int i = 0; i < 5; i++)
        {
            for(int j = i; j < 5; j++)
            {
                if(lastStep[i][j] == SCORE_MAX)    continue;

                int cur = lastStep[i][j];
                int newL = min(input, j);
                int newR = max(input, j);
                curStep[newL][newR] = min(curStep[newL][newR], cur + CalcScore(i, input));

                newL = min(input, i);
                newR = max(input, i);
                curStep[newL][newR] = min(curStep[newL][newR], cur + CalcScore(j, input));
            }
        }

        for(int i = 0; i < 5; i++)
        {
            for(int j = 0; j < 5; j++)
            {
                lastStep[i][j] = curStep[i][j];
            }
        }
    }

    int ret = SCORE_MAX;
    for(int i = 0; i < 5; i++)
    {
        for(int j = 0; j < 5; j++)
        {
            ret = min(ret, lastStep[i][j]);
        }
    }
    cout << ret << "\n";

    return 0;
}