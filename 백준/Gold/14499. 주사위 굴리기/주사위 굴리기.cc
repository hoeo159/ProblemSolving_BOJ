#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int N, M, x, y, K;

int graph[21][21];

struct Dice
{
    int row, col;
    int front, back, top, bottom, right, left;

    void roll(int command)
    {
        switch (command)
        {
            case 1:
                rollEast();
                break;
            case 2:
                rollWest();
                break;
            case 3:
                rollNorth();
                break;
            case 4:
                rollSouth();
                break;
            default:
                break;
        }

        return;
    }

    void rollEast()
    {
        int _right = right, _left = left, _top = top, _bottom = bottom;
        bottom = _right;
        left = _bottom;
        top = _left;
        right = _top;
        col++;
        return;
    }

    void rollWest()
    {
        int _right = right, _left = left, _top = top, _bottom = bottom;
        bottom = _left;
        left = _top;
        top = _right;
        right = _bottom;
        col--;
        return;
    }

    void rollNorth()
    {
        int _top = top, _bottom = bottom, _front = front, _back = back;
        bottom = _front;
        front = _top;
        top = _back;
        back = _bottom;
        row--;
    }

    void rollSouth()
    {
        int _top = top, _bottom = bottom, _front = front, _back = back;
        bottom = _back;
        front = _bottom;
        top = _front;
        back = _top;
        row++;
    }
};

Dice dice{0, 0, 0, 0, 0, 0, 0, 0};

bool CanMove(Dice dice, int command)
{
    int row = dice.row, col = dice.col;
    if(command == 1)
    {
        if(col + 1 >= M)    return false;
    }
    if(command == 2)
    {
        if(col - 1 < 0)     return false;
    }
    if(command == 3) // 북으로 이동
    {
        if(row - 1 < 0)     return false;
    }
    if(command == 4)
    {
        if(row + 1 >= N)    return false;
    }
    return true;
}

int CopyNumber(int diceNum, int row, int col)
{
    int graphNum = graph[row][col];
    if(graphNum == 0)
    {
        graph[row][col] = diceNum;
    }
    else
    {
        diceNum = graphNum;
        graph[row][col] = 0;
    }
    return diceNum;
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> N >> M >> x >> y >> K;
    dice.row = x, dice.col = y;
    for(int i = 0; i < N; i++)
    {
        for(int j = 0; j < M; j++)
        {
            cin >> graph[i][j];
        }
    }

    for(int i = 0; i < K; i++)
    {
        int command;
        cin >> command;
        if(!CanMove(dice, command))   continue;
        dice.roll(command);
        dice.bottom = CopyNumber(dice.bottom, dice.row, dice.col);
        // cout << "dice : " << "{" << dice.row << "," << dice.col << "}";
        // cout << " top:" << dice.top << " bottom:" << dice.bottom << " front : " << dice.front << " back : " << dice.back << "\n";
        cout << dice.top << "\n";
    } 

    return 0;
}