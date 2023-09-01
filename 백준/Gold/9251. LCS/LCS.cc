#include <iostream>
#include <string>
#include <algorithm>
#include <vector>

using namespace std;

string str1, str2;
int len[1001][1001];
vector<char> lcs;

void solve(){
    int len1 = str1.length(), len2 = str2.length();
    for(int i = 0; i < len1; i++){
        for(int j = 0; j < len2; j++){
            if(str1[i] == str2[j]){
                len[i+1][j+1] = len[i][j] + 1;
            }
            else{
                len[i+1][j+1] = (len[i+1][j] >= len[i][j+1]) ? len[i+1][j] : len[i][j+1];
            }
        }
    }
    cout << len[str1.length()][str2.length()] << endl;

    return;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    cin >> str1;
    cin >> str2;
    solve();
    return 0;
}