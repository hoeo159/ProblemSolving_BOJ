#include <iostream>
#include <list>
using namespace std;

int N, M;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cin.ignore(0);

    list<int> survive;
    cin >> N >> M;
    for (int i = 1; i <= N; i++)
    {
        survive.push_back(i);
    }
    
    list<int>::iterator kill = survive.begin();

    printf("<");

    while (survive.size() > 1)
    {
        for (int i = 0; i < M - 1; i++)
        {
            kill++;
            if (kill == survive.end())
                kill = survive.begin();
        }

        printf("%d, ", *kill);

        kill = survive.erase(kill);

        if (kill == survive.end())
            kill = survive.begin();
    }
    printf("%d>", *kill);
    return 0;
}
