#include <iostream>
#include <algorithm>
using namespace std;

int w, h, x, y, ans;

int main()
{
	cin >> x >> y >> w >> h;
	ans = min({x, y, w - x, h - y});

	cout << ans << endl;

	return 0;
}