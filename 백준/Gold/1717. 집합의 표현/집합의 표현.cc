#include <iostream>
using namespace std;

int parent[1000001];

int n, m;

int _find(int x) {
    if (x == parent[x]) return x;
    return parent[x] = _find(parent[x]);
}

void _union(int x, int y) {
    x = _find(x);
    y = _find(y);
    parent[x] = y;
}

int main() {
    ios::sync_with_stdio(0), cin.tie(0);
    int temp, x, y;

    cin >> n >> m;
    
    for (int i = 0; i <= n; i++)   parent[i] = i;

    for (int i = 0; i < m; i++) {
        cin >> temp >> x >> y;
        if (temp == 0)   _union(x, y);
        else
        {
            if (_find(x) == _find(y))   cout << "YES\n";
            else
            {
                cout << "NO\n";
            }
        }
    }
    return 0;
}