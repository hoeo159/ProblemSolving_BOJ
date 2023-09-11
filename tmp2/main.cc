#include <iostream>
#include <string>
#include <map>
#include <algorithm>
#include <vector>

using namespace std;

map<string, int> dictPoke;
vector<string> name, ans;
int N, M;

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    cin >> N >> M;
    for(int i = 0; i < N; i++){
        string tmp;
        cin >> tmp;
        name.push_back(tmp);
        dictPoke.insert(make_pair(tmp, i));
    }
    for(int i = 0; i < M; i++){
        string tmp;
        cin >> tmp;
        if(tmp[0] >= 'A' && tmp[0] <= 'Z'){
            ans.push_back(to_string(dictPoke[tmp] + 1));
        }
        else{
            ans.push_back(name[stoi(tmp) - 1]);
        }
    }
    for(auto i : ans){
        cout << i << "\n";
    }
    return 0;
}