#include <iostream>
#include <vector>
using namespace std;

int main(){
    int N;
    vector<int> v;
    int num;

    cin >> N;

    for(int i = 0; i < N; i++){
        cin >> num;
        v.push_back(num);
    }
    
    int cnt = 0;
    cin >> num;

    for(int i = 0; i < N; i++){
        if(v[i] == num) cnt++;
    }

    cout << cnt << endl;

    return 0;
}