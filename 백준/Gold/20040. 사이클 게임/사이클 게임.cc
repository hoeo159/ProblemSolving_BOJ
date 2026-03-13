#include <iostream>
#include <vector>

using namespace std;

int N, M, ans; // N 500000, M 1000000
int idxSet = 0;

int findSet(int num, vector<int>& v){
    if(v[num] == -1){
        return num;
    }
    return v[num] = findSet(v[num], v);
}

void unionSet(int a, int b, vector<int>& v){
    int setA = findSet(a, v);
    int setB = findSet(b, v);
    if(setA != setB){
        v[setA] = setB;
    }
}

int main(){
    cin >> N >> M;
    vector<int> v;
    v.resize(N + 1, -1);
    for(int i = 0; i < M; i++){
        int a, b;
        cin >> a >> b;
        if(findSet(a, v) != findSet(b, v)){
            unionSet(a, b, v);
        }
        else{
            cout << i + 1 << "\n";
            return 0;
        }
    }
    cout << "0\n";
    return 0;
}