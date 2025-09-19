#include<iostream>
#include <algorithm>
#include <vector>
#include <cstring>

using namespace std;

int K = 0;
string str;

void solve(int test_case)
{
    vector<string> suff;
    int len = str.length();
    for(int i = 0; i < len; i++)
    {
        suff.push_back(str.substr(i));
    }

    sort(suff.begin(), suff.end());
    
    printf("#%d %s\n", test_case, suff[K - 1].c_str());
}

int main(int argc, char** argv)
{
	int test_case;
	int T;
	//freopen("input.txt", "r", stdin);
	cin>>T;
	for(test_case = 1; test_case <= T; ++test_case)
	{
        cin >> K;
        cin >> str;
        solve(test_case);
	}
	return 0;//정상종료시 반드시 0을 리턴해야합니다.
}