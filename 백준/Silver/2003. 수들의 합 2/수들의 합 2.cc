//2020312914 백민호
#include <iostream>
#include <vector>

using namespace std;

int main() {
	int a, b, num;
	int count = 0, sum = 0;
	vector<int> temp;
	cin >> a >> b;
	for (int i = 0; i < a; i++) {
		cin >> num;
		temp.push_back(num);
	}
	for (int i = 0; i < a; i++) {
		sum = 0;
		for (int j = i; j < a; j++) {
			sum += temp[j];
			if (sum == b)	count++;
		}
	}
	cout << count << endl;
	return 0;
}