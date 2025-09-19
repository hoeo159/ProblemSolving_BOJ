#include <vector>
#include <algorithm>
#include <deque>
#include <cstring>
#include <cstdio>

std::deque<char> globalStr;
std::vector<int> cntArray[5], cntArrayRev[5];
bool isReversed = false;

int hashString(int start, int end, bool isReversed = false)
{
    int ret = 0;
    if(isReversed)
    {
        for (int i = end; i >= start; i--)
        {
            ret = ret * 26 + (globalStr[i] - 'a');
        }
        return ret;
    }
    else
    {
        for (int i = start; i <= end; i++)
        {
            ret = ret * 26 + (globalStr[i] - 'a');
        }
    }
    return ret;
}

void init(char mStr[])
{
    int len = strlen(mStr);
	globalStr.clear();
    isReversed = false;
	for (int i = 0; i < len; i++)
	{
		globalStr.push_back(mStr[i]);
	}
    
    int _pow = 1;
    for(int i = 1; i <= 4; i++)
    {
        _pow *= 26;
        cntArray[i].clear();
        cntArray[i].resize(_pow, 0);
        cntArrayRev[i].clear();
        cntArrayRev[i].resize(_pow, 0);
    }

    for(int i = 0; i < len; i++)
    {
        int hash = 0;
        for(int j = 1; j <= 4; j++)
        {
            if(i + j > len) break;
            hash = hash * 26 + (mStr[i + j - 1] - 'a');
            cntArray[j][hash]++;
        }
    }

    for(int i = 0; i < len; i++)
    {
        int hash = 0;
        for(int j = 1; j <= 4; j++)
        {
            if(i + j > len) break;
            hash = hash * 26 + (mStr[len - (i + j)] - 'a');
            cntArrayRev[j][hash]++;
        }
    }
}

void appendWord(char mWord[])
{
    int len = strlen(mWord);

    if(!isReversed)
    {
        for (int i = 0; i < len; i++)
        {
            globalStr.push_back(mWord[i]);
            int globalLen = globalStr.size();

            for(int j = 1; j <= 4 && j <= globalLen; j++)
            {
                cntArray[j][hashString(globalLen - j, globalLen - 1, false)]++;
                cntArrayRev[j][hashString(globalLen - j, globalLen - 1, true)]++;
            }
        }
    }
    else
    {
        for (int i = 0; i < len; i++)
        {
            globalStr.push_front(mWord[i]);
            int globalLen = globalStr.size();

            for(int j = 1; j <= 4 && j <= globalLen; j++)
            {
                cntArray[j][hashString(0, j - 1, false)]++;
                cntArrayRev[j][hashString(0, j - 1, true)]++;
            }
        }
    }
}
void cut(int k)
{
    if(!isReversed)
    {
        
        for(int i = 0; i < k; i++)
        {
            int len = globalStr.size();

            for(int j = 1; j <= 4 && j <= len; j++)
            {
                cntArray[j][hashString(len - j, len - 1, false)]--;
                cntArrayRev[j][hashString(len - j, len - 1, true)]--;
            }

            globalStr.pop_back();
        }
    }
    else
    {
        for(int i = 0; i < k; i++)
        {
            int len = globalStr.size();

            for(int j = 1; j <= 4 && j <= len; j++)
            {
                cntArray[j][hashString(0, j - 1, false)]--;
                cntArrayRev[j][hashString(0, j - 1, true)]--;
            }

            globalStr.pop_front();
        }
    }

}

void reverse()
{
    isReversed = !isReversed;
}

int countOccurrence(char mWord[])
{
    int len = strlen(mWord);
    int hash = 0;
    for(int i = 0; i < len; i++)
    {
        hash = hash * 26 + (mWord[i] - 'a');
    }

    if(!isReversed)
    {
        return cntArray[len][hash];
    }
    else
    {
        return cntArrayRev[len][hash];
    }
	return 0;
}

// void checkStr()
// {
//     printf("cur : ");
//     if(!isReversed)
//     {
//         for (char c : globalStr)
//         {
//             printf("%c", c);
//         }
//     }
//     else
//     {
//         for (auto it = globalStr.rbegin(); it != globalStr.rend(); ++it)
//         {
//             printf("%c", *it);
//         }
//     }
//     printf("\n");
// }