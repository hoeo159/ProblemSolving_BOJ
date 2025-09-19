#include <vector>
#include<iostream>

using namespace std;

vector<int> W;
vector<int> S;
int N, K; // block 수, 초기 데이터 덩어리 수

bool check(int maxWear)
{
    int chunkIdx = 0;
    int curblockSize = 0;

    for(int i = 0; i < N; i++)
    {
        if(chunkIdx >= K)
        {
            return true;
        }

        // 유효
        if(W[i] <= maxWear)
        {
            curblockSize++;
        }
        else
        {
            curblockSize = 0; 
        }

        if(curblockSize >= S[chunkIdx])
        {
            chunkIdx++;
            curblockSize = 0; // 다음 chunk 시작
        }
    }

    return chunkIdx >= K;
}

void solve(int test_case)
{
    // wear level max 200000
    int left = 0, right = 200001;
    int ret = 0;
    while(left + 1 < right)
    {
        int mid = (left + right) / 2;
        if(check(mid)) // 다음은 더 작은 값
        {
            ret = mid;
            right = mid;
        }
        else
        {
            left = mid;
        }
    }
    printf("#%d %d\n", test_case, ret);
}

int main(int argc, char** argv)
{
	int test_case;
	int T;
	cin>>T;
	for(test_case = 1; test_case <= T; ++test_case)
	{
        cin >> N >> K;
        W.clear(), W.resize(N + 1);
        S.clear(), S.resize(K + 1);
        for(int i = 0; i < N; i++)
        {
            cin >> W[i];
        }
        for(int i = 0; i < K; i++)
        {
            cin >> S[i];
        }
        solve(test_case);
	}
	return 0;//정상종료시 반드시 0을 리턴해야합니다.
}