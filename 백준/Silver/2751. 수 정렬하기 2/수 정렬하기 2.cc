
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
int main() {
	vector<int> vec;
	int num, i, n;
	scanf("%d", &num);
	for (i = 0; i < num; i++) {
		scanf("%d", &n);
		vec.push_back(n);
	}
	stable_sort(vec.begin(), vec.end());
	for (i = 0; i < num; i++) {
		cout << vec[i];
		printf("\n");
	}

	return 0;
}