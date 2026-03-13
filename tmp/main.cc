#include <iostream>
#include <string>
#include <vector>
using namespace std;

string prob;

void solve(string s)
{
    int len = s.length();
    vector<char> v(len + 1);
    for(int i = 0; i < len; i++)
    {
        v[i] = s[len - i - 1];
    }
    v[len] = '\0';
    for(int i = 0; i < len; i++)
    {
        if(v[i] != s[i])
        {
            cout << "no\n";
            return;
        }
    }
    cout << "yes\n";
    return;
}

int main()
{
    cin >> prob;
    while(prob != "0")
    {
        solve(prob);
        cin >> prob;
    }
}