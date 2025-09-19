#include<iostream>

using namespace std;

int main(int argc, char** argv)
{
	int test_case;
	int T;
	//freopen("input.txt", "r", stdin);
	cin>>T;
	for(test_case = 1; test_case <= T; ++test_case)
	{
        long long N;
        scanf("%lld", &N);

        long long left = 1, right = 2000000000;
        long long ret = -1;
        while(left <= right)
        {
            long long mid = left + (right - left) / 2;
            long long candle;
            if(mid % 2 == 0)
            {
                candle = (mid / 2) * (mid + 1);
            } 
            else
            {
                candle = mid * ((mid + 1) / 2);
            }
            if(candle == N)
            {
                ret = mid;
                break;
            }
            else if(candle < N)
            {
                left = mid + 1;
            }
            else
            {
                right = mid - 1;
            }
        }
        printf("#%d %lld\n", test_case, ret);
	}
	return 0;//정상종료시 반드시 0을 리턴해야합니다.
}