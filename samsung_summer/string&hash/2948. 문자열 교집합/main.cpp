#include<iostream>
#include <string>
#include <vector>
#include <unordered_set>

using namespace std;

int N, M;

int main(int argc, char** argv)
{
	int test_case;
	int T;
	//freopen("input.txt", "r", stdin);
	cin>>T;
	for(test_case = 1; test_case <= T; ++test_case)
	{
        string str = "", tmp = "";
        cin >> N >> M;
        unordered_set<string> set1, set2;
        for(int i = 0; i < N; i++)
        {
            cin >> tmp;
            set1.insert(tmp);   
        }

        int ret = 0;

        for(int i = 0; i < M; i++)
        {
            cin >> tmp;
            set2.insert(tmp);

            if(set1.count(tmp))
            {
                ret++;
            }
        }

        printf("#%d %d\n", test_case, ret);
	}
	return 0;//정상종료시 반드시 0을 리턴해야합니다.
}