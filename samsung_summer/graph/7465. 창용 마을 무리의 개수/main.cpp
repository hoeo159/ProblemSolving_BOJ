#include <stdio.h>
#include <vector>
#include <algorithm>
#include <set>

std::vector<int> parent;

int Find(int x)
{
    if (x == parent[x])
        return x;
    else return Find(parent[x]);
}

void Union(int a, int b)
{
    int rootA = Find(a);
    int rootB = Find(b);
    if (rootA != rootB)
        parent[rootB] = rootA;
}

int main(void)
{
	int test_case;
	int T;
	setbuf(stdout, NULL);
    
    // freopen("input.txt", "r", stdin);
	scanf("%d", &T);

	for (test_case = 1; test_case <= T; ++test_case)
	{
        int N, M;
        scanf("%d %d", &N, &M);
        parent.clear();
        parent.resize(N + 2);
        for(int i = 0; i <= N; i++)
            parent[i] = i;

        for(int i = 0; i < M; i++)
        {
            int a, b;
            scanf("%d %d", &a, &b);
            Union(a, b);
        }

        std::set<int> root;
        for(int i = 1; i <= N; i++)
        {
            int tmp = Find(i);
            root.insert(tmp);
        }

        int ret = (int)root.size();
        printf("#%d %d\n", test_case, ret);
	}
	return 0; //정상종료시 반드시 0을 리턴해야 합니다.
}