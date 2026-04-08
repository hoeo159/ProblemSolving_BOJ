#include <iostream>
#include <string>
#include <algorithm>
#include <vector>

using namespace std;

int ret = 0;
string str;
string revStr;

bool solve(int index, int len)
{
    for(int i = index; i < len; i++)
    {
        if(str[i] != revStr[i - index])
        {
            return false;
        }
    }
    return true;
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> str;

    int len = str.length();
    for(int i = len - 1; i >= 0; i--)
    {
        revStr += str[i];
    }

    for(int i = 0; i < len; i++)
    {
        if(solve(i, len))
        {
            ret = i + len;
            cout << ret << "\n";
            break;
        }
    }
    

    return 0;
}