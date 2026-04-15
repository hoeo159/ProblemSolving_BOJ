#include <iostream>
#include <vector>
using namespace std;

vector<string> A, B;
int n, m;

void flip(int x, int y) {
	for (int i = x; i < x + 3; i++) {
		for (int j = y; j < y + 3; j++) {
			A[i][j] = (A[i][j] == '0' ? '1' : '0');
		}
	}
}

int main() {
	int count = 0;
	cin >> n >> m;
	A.resize(n);
	B.resize(n);
	for (auto& i : A)	cin >> i;
	for (auto& i : B)	cin >> i;

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (A[i][j] != B[i][j]) {
				if (i + 2 < n && j + 2 < m) {
					flip(i, j);
					count++;
				}
				else {
					cout << "-1" << endl;
					return 0;
				}
			}
		}
	}

	cout << count << endl;

	return 0;
}