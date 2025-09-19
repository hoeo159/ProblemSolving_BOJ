#include <vector>
#include <deque>
#include <array>
#include <algorithm>
#include <cstring>
#include <cstdio>

std::vector<std::deque<char>> memo;
std::vector<std::array<int, 26>> alphaPsum; // count alphabet of memo with prefix sum

int cursor = 0;
int totalRow = 0, totalCol = 0;
int endRow = 0, endCol = 0;

void init(int H, int W, char mStr[])
{
    int lenMemo = H * W;
    int lenStr = strlen(mStr);
    totalRow = H, totalCol = W;

    memo.clear();
    memo.resize(H);
    
    int lenPsum = (lenStr + W - 1) / W;
    alphaPsum.clear();
    alphaPsum.resize(H);

    for(int i = 0; i < H; i++)
    {
        memo[i].clear();
        alphaPsum[i].fill(0);
    }

    for(int i = 0; i < lenPsum; i++)
    {
        int startCol = i * W;
        int endCol = std::min(startCol + W, lenStr);
        for(int j = startCol; j < endCol; j++)
        {
            char c = mStr[j];
            memo[i].push_back(c);
            alphaPsum[i][c - 'a']++;
        }
    }

    cursor = 0;
    endRow = (lenStr - 1) / W;
    endCol = (lenStr - 1) % W;
}

void insert(char _mChar)
{
    int curRow = cursor / totalCol;
    int curCol = cursor % totalCol;
    int row = curRow;
    char mChar = _mChar;

    // printf("%d %d\n", curRow, curCol);

    while(true)
    {
        if(row >= (int)memo.size())
        {
            memo.emplace_back();
            alphaPsum.emplace_back();
            alphaPsum.back().fill(0);
        }
        
        memo[row].insert(memo[row].begin() + curCol, mChar);
        alphaPsum[row][mChar - 'a']++;

        if((int)memo[row].size() <= totalCol)
        {
            break;
        }

        char last = memo[row].back();
        memo[row].pop_back();
        alphaPsum[row][last - 'a']--;

        mChar = last;
        curCol = 0;

        row++;
    }

    endCol++;
    if(endCol >= totalCol)
    {
        endCol = 0;
        endRow++;
    }

    cursor++;
    if(cursor > endRow * totalCol + endCol)
        cursor = endRow * totalCol + endCol + 1;
}

char moveCursor(int mRow, int mCol)
{
    // 1 3
    int goalRow = mRow - 1, goalCol = mCol - 1;
    int lastRow = memo.size(), lastCol = memo[goalRow].size();
    // printf("last %d %d\n", lastRow, lastCol);
    if(goalRow >= lastRow || goalCol >= lastCol)
    {
        cursor = endRow * totalCol + endCol + 1;
        return '$';
    }

    cursor = goalRow * totalCol + goalCol;

    return memo[goalRow][goalCol];
}

int countCharacter(char mChar)
{
    int totallenMemo = endRow * totalCol + endCol;
    int find = mChar - 'a';
    int ret = 0;
    int curRow = cursor / totalCol;
    int curCol = cursor % totalCol;

    // printf("cur : %d %d\n", curRow, curCol);

    if(curRow < memo.size())
    {
        for(int i = curCol; i < (int)memo[curRow].size(); i++)
        {
            if(memo[curRow][i] == mChar)
            {
                ret++;
                // printf("ret : %d\n", ret);
            }
        }
        for(int i = curRow + 1; i < (int)memo.size(); i++)
        {
            ret += alphaPsum[i][find];
            // printf("ret : %d\n", ret);
        }
    }
    // printf("ret : %d\n", ret);
    return ret;
}

// 커서 위치는 *로 표시
// void showMemo()
// {
//     printf("cursor : %d %d %d\n", cursor, cursor / totalCol, cursor % totalCol);
//     for(int row = 0; row < memo.size(); row++)
//     {
//         for(int col = 0; col < memo[row].size(); col++)
//         {
//             if(row == (cursor / totalCol) && col == (cursor % totalCol))
//             {
//                 printf("*");
//             }
//             printf("%c", memo[row][col]);
//         }
//         if(row == (cursor / totalCol) && cursor % totalCol == memo[row].size())
//             printf("*");
//         printf("\n");
//     }
// }