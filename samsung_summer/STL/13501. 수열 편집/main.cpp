#include <iostream>
#include <string>
#include <list>
using namespace std;

int N, M, L;

int main(int argc, char** argv)
{
	cin.tie(NULL);
	ios_base::sync_with_stdio(false);

	int test_case;
	int T;
	freopen("sample_input.txt", "r", stdin);
	cin>>T;
	
	for(test_case = 1; test_case <= T; ++test_case)
	{
		cin >> N >> M >> L;
		list<int> tmp;
		for(int i = 0; i < N; i++)
		{
			int num = 0;
			cin >> num;
			tmp.push_back(num);
		}

		for(int i = 0; i < M; i++){
			string command;
			list<int>::iterator iter = tmp.begin();
			int pos, num;

			cin >> command;
			cin >> pos;

			for(int i = 0; i < pos; i++)
			{
				iter++;
			}

			if(command == "I")
			{
				cin >> num;
				tmp.insert(iter, num);
			}
			else if(command == "D")
			{
				tmp.erase(iter);
			}
			else if(command == "C")
			{
				cin >> num;
				*iter = num;
			}
		}

		cout << "#" << test_case << " ";
		if(tmp.size() < L - 1)
		{
			cout << -1 << "\n";
		}
		else
		{
			list<int>::iterator iter = tmp.begin();
			for(int i = 0; i < L; i++)
			{
				iter++;
			}
			cout << *iter << "\n";
		}
	}

	return 0;//정상종료시 반드시 0을 리턴해야합니다.
}