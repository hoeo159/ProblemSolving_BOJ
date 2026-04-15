#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

string c1[8] = {
    "WBWBWBWB",
    "BWBWBWBW",
    "WBWBWBWB",
    "BWBWBWBW",
    "WBWBWBWB",
    "BWBWBWBW",
    "WBWBWBWB",
    "BWBWBWBW"};
string c2[8] = {
    "BWBWBWBW",
    "WBWBWBWB",
    "BWBWBWBW",
    "WBWBWBWB",
    "BWBWBWBW",
    "WBWBWBWB",
    "BWBWBWBW",
    "WBWBWBWB"};

string map[50];
int N, M, ans = INT32_MAX;

int compare_c1(int x, int y);
int compare_c2(int x, int y);

int main()
{
    cin >> N >> M;
    for (int i = 0; i < N; i++)
    {
        cin >> map[i];
    }
    for (int i = 0; i + 8 <= N; i++)
    {
        for (int j = 0; j + 8 <= M; j++)
        {
            int temp = min(compare_c1(i, j), compare_c2(i, j));
            ans = min(ans, temp);
        }
    }

    cout << ans << endl;
    return 0;
}

int compare_c1(int x, int y)
{
    int cnt = 0;
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            if (map[x + i][y + j] != c1[i][j])
                cnt++;
        }
    }
    return cnt;
}
int compare_c2(int x, int y)
{
    int cnt = 0;
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            if (map[x + i][y + j] != c2[i][j])
                cnt++;
        }
    }
    return cnt;
}