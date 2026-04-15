#include <iostream>
#include <string.h>
#include <algorithm>

using namespace std;

string str;
int alpha[26];

int main()
{
	int ans = -1, idx, count = 0;
	memset(alpha, 0, sizeof(int) * 26);
	cin >> str;
	for (int i = 0; i < str.length(); i++)
	{
		if (str[i] > 95)
			alpha[str[i] - 97]++;
		else
			alpha[str[i] - 65]++;
	}
	for (int i = 0; i < 26; i++)
	{
		if (ans < alpha[i])
		{
			ans = alpha[i];
			idx = i;
		}
	}

	for (int i = 0; i < 26; i++)
	{
		if (alpha[i] == alpha[idx])
			count++;
	}

	if (count > 1)
		cout << "?" << endl;
	else
		cout << static_cast<char>(idx + 65) << endl;
	return 0;
}