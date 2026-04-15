#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
	vector<pair<int, int>> v;
	int num, a, b, temp;
	int ans = 1;
	cin >> num;
	for (int i = 0; i < num; i++) {
		cin >> a >> b;
		v.push_back(make_pair(b, a));
	}
	sort(v.begin(), v.end());
//	for (int i = 0; i < num; i++)	cout << v[i].first << " " << v[i].second << endl;
	
	temp = v[0].first;
	for (int i = 1; i < num; i++) {
		if (temp <= v[i].second) {
			temp = v[i].first;
			ans++;
		}
	}

	cout << ans << endl;

	return 0;
}