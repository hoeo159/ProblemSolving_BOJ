#include<iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <tuple>

using namespace std;

typedef struct GRID
{
	long long x, y;
} Grid;

vector<tuple<long long, long long, long long>> cost;
vector<Grid> island;

long long parent[1001];

long long Find(long long x)
{
    if (x == parent[x])
        return x;
    else return parent[x] = Find(parent[x]);
}

void Union(long long a, long long b)
{
    long long rootA = Find(a);
    long long rootB = Find(b);
    if (rootA != rootB)
        parent[rootB] = rootA;
}

long long getCost(long long island1, long long island2)
{
	long long sqDistance = 0;
	sqDistance = (island[island1].x - island[island2].x) * (island[island1].x - island[island2].x) + 
					(island[island1].y - island[island2].y) * (island[island1].y - island[island2].y);
	return sqDistance;
}

void init(long long N)
{
	for (long long i = 0; i < N; i++)
	{
		parent[i] = i;
	}
	cost.clear();
	island.clear();
	island.resize(N + 1);
}

int main(int argc, char** argv)
{
	long long test_case;
	long long T;
	freopen("input.txt", "r", stdin);
	cin>>T;
	for(test_case = 1; test_case <= T; ++test_case)
	{
		long long N; // 섬의 개수
		double E; // 환경 부담 세율 실수
		// 세금은 환경 부담 세율(E)과 각 해저터널 길이(L)의 제곱의 곱(E * L^2)만큼 지불
		cin >> N;
		init(N);

		for(long long i = 0; i < N; i++)
		{
			cin >> island[i].x;
		}
		for(long long i = 0; i < N; i++)
		{
			cin >> island[i].y;
		}
		cin >> E;

		for(long long i = 0; i < N; i++)
		{
			for(long long j = i + 1; j < N; j++)
			{
				long long costValue = getCost(i, j);
				cost.emplace_back(costValue, i, j);
			}
		}

		sort(cost.begin(), cost.end());

		long long sum = 0;
		for(auto &i : cost)
		{
			long long c;
			long long u, v;
			tie(c, u, v) = i;
			if (Find(u) != Find(v))
			{
				Union(u, v);
				sum += c;
			}
		}

		long long ret = (long long)round(sum * E);
		cout << "#" << test_case << " " << ret << endl;
	}
	return 0;//정상종료시 반드시 0을 리턴해야합니다.
}