#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <iterator>

using namespace std;

string str, tmp, ans;
char dvd[] = {'<', '>', '&', '|', '(', ')'};
vector<string> tokens;

bool check(char letter)
{
	for (int i = 0; i < 6; i++)
	{
		if (letter == dvd[i])
		{
			return true;
		}
	}
	return false;
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);

	getline(cin, str);

	for (int i = 0; i < str.length(); i++)
	{
		if (check(str[i]))
		{
			if (str[i] == '&' || str[i] == '|')
			{
				ans.append(tmp);
				ans += " ";
				ans.append(1, str[i]);
				ans.append(1, str[i + 1]);
				ans += " ";
				i++;
			}
			else
			{
				ans.append(tmp);
				ans += " ";
				ans.append(1, str[i]);
				ans += " ";
			}

			tmp.clear();
		}
		else
		{
			tmp.append(1, str[i]);
		}
	}
	if (!tmp.empty())
		ans.append(tmp);

	istringstream iss(ans);
	string s;
	while (iss >> s)
	{
		tokens.push_back(s);
	}
	for (auto &i : tokens)
	{
		cout << i << " ";
	}

	return 0;
}