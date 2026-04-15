#include <iostream>
#include <stack>
#include <string>

using namespace std;

int N;
string str;

int main()
{
    ios::sync_with_stdio(0), cin.tie(0);

    cin >> N;

    while (N--)
    {
        stack<char> tmp;
        cin >> str;

        for (int i = 0; i < str.length(); i++)
        {
            if (str[i] == '(' || str[i] == '{' || str[i] == '[')
                tmp.push(str[i]);

            if ((str[i] == ')' || str[i] == '}' || str[i] == ']') && tmp.empty())
            {
                tmp.push(str[i]);
                break;
            }

            if (str[i] == ')')
            {
                if (tmp.top() == '(')
                    tmp.pop();

                else
                    break;
            }
            if (str[i] == '}')
            {
                if (tmp.top() == '{')
                    tmp.pop();
                else
                    break;
            }
            if (str[i] == ']')
            {
                if (tmp.top() == '[')
                    tmp.pop();
                else
                    break;
            }
        }

        if (tmp.empty())
            cout << "YES" << endl;
        else
        {
            cout << "NO" << endl;
        }
    }

    return 0;
}
