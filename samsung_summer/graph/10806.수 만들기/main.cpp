#include<iostream>
#include <vector>
#include <queue>
#include <set>

using namespace std;

vector<int> a;

struct Cond
{
    int val;
    int cnt;
    bool operator<(const Cond& other) const
    {
        return val < other.val;
    }
};

int main(int argc, char** argv)
{
	int test_case;
	int T;
	freopen("input.txt", "r", stdin);

	cin>>T;

	for(test_case = 1; test_case <= T; ++test_case)
	{
        // X=0, D=1
        // 1. X에 D를 더한다.
        // 2. D에 A1,A2,…,AN 중 하나를 곱한다.
        int N;
        int K;
        cin >> N;

        a.clear();
        a.resize(N);
        
        for(int i = 0; i < N; i++)
        {
            cin >> a[i];
        }
        cin >> K;

        priority_queue<Cond> pq;
        Cond start = {0, K};
        pq.push(start);

        while(!pq.empty())
        {
            int cnt = -pq.top().val;
            int val = pq.top().cnt;
            pq.pop();

            if(val == 0)
            {
                cout << "#" << test_case << " " << cnt << endl;
                break;
            }

            for(int i = 0; i < N; i++)
            {
                int next_val = -(cnt + val % a[i]);
                int next_cnt = val / a[i];
                Cond next = {next_val, next_cnt};
                pq.push(next);
            }
        }

	}
	return 0;//정상종료시 반드시 0을 리턴해야합니다.
}