#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

long long T, ret = 0;
int sizeA, sizeB;

vector<int> A;
vector<int> B;
vector<long long> a, b;

int main()
{
    cin >> T;
    cin >> sizeA;
    A.resize(sizeA);
    for(int i = 0; i < sizeA; i++)
    {
        cin >> A[i];
    }
    cin >> sizeB;
    B.resize(sizeB);
    for(int i = 0; i < sizeB; i++)
    {
        cin >> B[i];
    }

    for(int i = 0; i < sizeA; i++)
    {
        long long sum = 0;
        for(int j = i; j < sizeA; j++)
        {
            sum += A[j];
            a.push_back(sum);
        }
    }

    for(int i = 0; i < sizeB; i++)
    {
        long long sum = 0;
        for(int j = i; j < sizeB; j++)
        {
            sum += B[j];
            b.push_back(sum);
        }
    }
    sort(b.begin(), b.end());

    int len = a.size();
    for(int i = 0; i < len; i++)
    {
        long long cur = T - a[i];

        auto start = lower_bound(b.begin(), b.end(), cur);
        auto end = upper_bound(b.begin(), b.end(), cur);

        ret += end - start;
    }

    cout << ret << "\n";
    return 0;
}