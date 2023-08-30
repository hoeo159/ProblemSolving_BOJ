#include <iostream>
#include <algorithm>
#include <string>
#include <vector>

using namespace std;

string str;
int board[9][9];
vector<pair<int, int>> emptySpace;

bool canPush(int x, int y, int num){
    for(int i = 0; i < 9; i++){
        if(board[x][i] == num){
            return false;
        }
    }
    for(int i = 0; i < 9; i++){
        if(board[i][y] == num){
            return false;
        }
    }
    int matX = (x/3) * 3;
    int matY = (y/3) * 3;
    for(int i = matX; i < matX + 3; i++){
        for(int j = matY; j < matY + 3; j++){
            if(i == x && j == y){
                continue;
            }
            if(board[i][j] == num){
                return false;
            }
        }
    }
    return true;
}

void solve(int n){
    if(n == emptySpace.size()){
        for(int i = 0; i < 9; i++){
            for(int j = 0; j < 9; j++){
                cout << board[i][j];
            }
            cout << endl;
        }
        exit(0);
    }
    else{
        int x = emptySpace[n].first;
        int y = emptySpace[n].second;
        for(int i = 1; i <= 9; i++){
            if(canPush(x, y, i)){
                board[x][y] = i;
                solve(n+1);
                board[x][y] = 0;
            }

        }
    }
    return;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    for(int i = 0; i < 9; i++){
        cin >> str;
        for(int j = 0; j < 9; j++){
            board[i][j] = str[j] - '0';
            if(board[i][j] == 0){
                emptySpace.push_back(make_pair(i,j));
            }
        }
    }
    solve(0);
    return 0;
}