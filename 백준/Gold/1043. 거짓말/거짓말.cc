#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int N, M, K;

vector<int> set;
vector<int> party[51];

int find(int cur)
{
    if(set[cur] == -1) return cur;
    else    return set[cur] = find(set[cur]);
}

void unite(int a, int b)
{
    int pa = find(a);
    int pb = find(b);
    if(pa != pb)    set[pa] = pb;
}



int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> N >> M;
    set.resize(N + 1, -1);
    cin >> K;
    for(int i = 0; i < K; i++)
    {
        int num;
        cin >> num;
        unite(0, num);
    }

    int ret = 0;

    for(int i = 0; i < M; i++)
    {
        cin >> K;

        for(int j = 0; j < K; j++)
        {
            int num;
            cin >> num;
            party[i].push_back(num);
            if(j > 0)
            {
                unite(party[i][j - 1], party[i][j]);
            }
        }
    }

    for(int i = 0; i < M; i++)
    {
        bool findFlag = false;
        vector<int> curParty = party[i];
        int len = curParty.size();
        for(int j = 0; j < len; j++)
        {
            if(find(0) == find(curParty[j]))
            {
                findFlag = true;
                break;
            }
        }
        
        if(!findFlag)
        {
            ret++;
        }
    }
        

    cout << ret << "\n";

    return 0;
}