#define WIDTH (8)

#include <cstring>
#include <iostream>

int graph[WIDTH][WIDTH];
int usedRowPerCol[WIDTH];
int tilePool[10000][WIDTH];
int N;

int mRet[5];

int getScore(int num)
{
    if(num == 3) return 1;
    else if(num == 4) return 4;
    else if(num >= 5) return 9;
    return 0;
}

void init(int _N, int mTiles[][WIDTH])
{
    N = _N;
    for(int i = 0; i < WIDTH; i++)
    {
        usedRowPerCol[i] = 0;
    }

    memcpy(tilePool, mTiles, sizeof(int) * N * WIDTH);

    for(int i = 0; i < WIDTH; i++)
    {
        for(int j = 0; j < WIDTH; j++)
        {
            graph[i][j] = mTiles[i][j];
            usedRowPerCol[j]++;
        }
    }
}

int removeMatchGraph()
{
    bool removedFlag = false;
    bool visitedGraph[WIDTH][WIDTH];
    memset(visitedGraph, 0, sizeof(visitedGraph));
    int score = 0;

    for(int row = 0; row < WIDTH; row++)
    {
        for(int col = 0; col < WIDTH; col++)
        {
            int val = graph[row][col];
            if(val == 0)    continue;
            int cnt = 1;
            while(col + cnt < WIDTH && graph[row][col + cnt] == val)
            {
                cnt++;
            }
            if(cnt >= 3)
            {
                score += getScore(cnt);
                for(int i = 0; i < cnt; i++)
                {
                    visitedGraph[row][col + i] = true;
                }
                removedFlag = true;
            }
            col += (cnt - 1);
        }
    }

    for(int col = 0; col < WIDTH; col++)
    {
        for(int row = 0; row < WIDTH; row++)
        {
            int val = graph[row][col];
            if(val == 0)    continue;
            int cnt = 1;
            while(row + cnt < WIDTH && graph[row + cnt][col] == val)
            {
                cnt++;
            }
            if(cnt >= 3)
            {
                score += getScore(cnt);
                for(int i = 0; i < cnt; i++)
                {
                    visitedGraph[row + i][col] = true;
                }
                removedFlag = true;
            }
            row += (cnt - 1);
        }
    }

    if(removedFlag)
    {
        for(int row = 0; row < WIDTH; row++)
        {
            for(int col = 0; col < WIDTH; col++)
            {
                if(visitedGraph[row][col])
                {
                    graph[row][col] = 0;
                }
            }
        }
    }

    return score;
}

void fillEmpty()
{
    for(int col = 0; col < WIDTH; col++)
    {
        int fillIdx = 0;
        for(int row = 0; row < WIDTH; row++)
        {
            if(graph[row][col] != 0)
            {
                int tmp = graph[row][col];
                graph[row][col] = 0;
                graph[fillIdx][col] = tmp;
                fillIdx++;
            }
        }

        while(fillIdx < WIDTH)
        {
            graph[fillIdx][col] = tilePool[usedRowPerCol[col]][col];
            usedRowPerCol[col]++;
            fillIdx++;
        }
    }
}

void graphSwap(int r1, int c1, int r2, int c2)
{
    int tmp = graph[r1][c1];
    graph[r1][c1] = graph[r2][c2];
    graph[r2][c2] = tmp;
}

int chkMatch(int _row, int _col)
{
    int val = graph[_row][_col];
    if(val == 0)    return 0;
    int ret = 0;
    int horizonCnt = 1, verticalCnt = 1;

    for(int col = _col - 1; col >= 0; col--)
    {
        if(graph[_row][col] == val)    horizonCnt++;
        else    break;
    }
    for(int col = _col + 1; col < WIDTH; col++)
    {
        if(graph[_row][col] == val)    horizonCnt++;
        else    break;
    }

    for(int row = _row - 1; row >= 0; row--)
    {
        if(graph[row][_col] == val)    verticalCnt++;
        else    break;
    }
    for(int row = _row + 1; row < WIDTH; row++)
    {
        if(graph[row][_col] == val)    verticalCnt++;
        else    break;
    }

    ret = getScore(horizonCnt) + getScore(verticalCnt);

    return ret;
}

bool canMove()
{
    for(int row = 0; row < WIDTH; row++)
    {
        for(int col = 0; col < WIDTH; col++)
        {
            if(row + 1 < WIDTH)
            {
                graphSwap(row, col, row + 1, col);
                if(chkMatch(row, col) || chkMatch(row + 1, col))
                {
                    graphSwap(row, col, row + 1, col);
                    return true;
                }
                graphSwap(row, col, row + 1, col);
            }

            if(col + 1 < WIDTH)
            {
                graphSwap(row, col, row, col + 1);
                if(chkMatch(row, col) || chkMatch(row, col + 1))
                {
                    graphSwap(row, col, row, col + 1);
                    return true;
                }
                graphSwap(row, col, row, col + 1);
            }
        }
    }

    return false;
}

void clearAll()
{
    for(int col = 0; col < WIDTH; col++)
    {
        int startRow = usedRowPerCol[col];
        for(int row = 0; row < WIDTH; row++)
        {
            graph[row][col] = tilePool[startRow + row][col];
        }
        usedRowPerCol[col] += WIDTH;
    }
}

void getReady()
{
    bool readyFlag = false;
    while(!readyFlag)
    {
        fillEmpty();
        while(removeMatchGraph())
        {
            fillEmpty();
        }

        if(canMove()) // solution found
        {
            readyFlag = true;
        }
        else    clearAll();
    }
}

void swapTile()
{
    int maxScore = 0;
    int candidateRow = -1, candidateCol = -1;
    bool isHorizontal = true;

    for(int row = 0; row < WIDTH; row++)
    {
        for(int col = 0; col < WIDTH; col++)
        {
            if(col + 1 < WIDTH)
            {
                graphSwap(row, col, row, col + 1);
                int curScore = chkMatch(row, col) + chkMatch(row, col + 1);
                if(curScore > maxScore)
                {
                    maxScore = curScore;
                    candidateRow = row;
                    candidateCol = col;
                    isHorizontal = true;
                }
                graphSwap(row, col, row, col + 1);
            }

            if(row + 1 < WIDTH)
            {
                graphSwap(row, col, row + 1, col);
                int curScore = chkMatch(row, col) + chkMatch(row + 1, col);
                if(curScore > maxScore)
                {
                    maxScore = curScore;
                    candidateRow = row;
                    candidateCol = col;
                    isHorizontal = false;
                }
                graphSwap(row, col, row + 1, col);
            }
        }
    }

    if(maxScore > 0)
    {
        if(isHorizontal)
        {
            graphSwap(candidateRow, candidateCol, candidateRow, candidateCol + 1);
            mRet[1] = candidateRow;
            mRet[2] = candidateCol;
            mRet[3] = candidateRow;
            mRet[4] = candidateCol + 1;
        }
        else
        {
            graphSwap(candidateRow, candidateCol, candidateRow + 1, candidateCol);
            mRet[1] = candidateRow;
            mRet[2] = candidateCol;
            mRet[3] = candidateRow + 1;
            mRet[4] = candidateCol;
        }
    }
}

void chainTile()
{
    int score = 0;
    while(true)
    {
        int curScore = removeMatchGraph();
        if(curScore == 0)    break;

        score += curScore;
        fillEmpty();
    }
    mRet[0] = score;
}

int* takeTurn()
{
    // 1. 격자 준비상태 만들기
    getReady();
    // 2. 점수 우선 순위에 따라 인접한 타일의 위치를 교환하여 타일을 삭제하고 점수를 얻기
    swapTile();
    // 3. 삭제 후 빈 공간을 채우고, 매치되는 타일이 있으면 삭제 후 빈 공간 채우기 연쇄
    chainTile();
    // std::cout << mRet[0] << " " << mRet[1] << " " << mRet[2] << " " << mRet[3] << " " << mRet[4] << "\n";
	return mRet;
}