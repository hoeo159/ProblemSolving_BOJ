#include <iostream>
#include <cmath>

using namespace std;

int m, n;

bool isPrime(int n)
{
    if (n == 1)
        return false;
    if (n == 2)
        return true;
    if (n % 2 == 0)
        return false;
    for (int i = 3; i <= (int)sqrt(n); i += 2)
    {
        if (n % i == 0)
            return false;
    }
    return true;
}

int main()
{
    cin >> m >> n;
    for (int i = m; i <= n; i++)
        if (isPrime(i))
            cout << i << '\n';
    return 0;
}