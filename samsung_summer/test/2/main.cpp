#include<iostream>
#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char** argv)
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);
	int test_case;
	int T;

	cin>>T;

	for(test_case = 1; test_case <= T; ++test_case)
	{

		long long N, M;
        cin >> N >> M;

        long long score_odd = ((N + 1) / 2) * ((N + 1) / 2);
        long long score_even = (N / 2) * (N / 2 + 1);

        long long ret = score_odd - score_even;
        cout << ret << " ";

        vector<long long> move(M - 1);

        for(int i = 0; i < M - 1; i++){
            cin >> move[i];
        }

        vector<long long> move_unique = move;
        sort(move_unique.begin(), move_unique.end());

        auto newEnd = unique(move_unique.begin(), move_unique.end());
        move_unique.resize(newEnd - move_unique.begin());

        long long unique_size = move_unique.size();

        vector<bool> toggle;
        toggle.resize(unique_size, false);

        for(auto i : move){
            int index = lower_bound(move_unique.begin(), move_unique.end(), i) - move_unique.begin();
            bool curTeam = (i & 1) ^ toggle[index];

            if(curTeam){
                ret -= 2 * i;
            }
            else{
                ret += 2 * i;
            }
            toggle[index] = !toggle[index];
            cout << ret << " ";
        }
        
        cout << "\n";
	}
	return 0;
}