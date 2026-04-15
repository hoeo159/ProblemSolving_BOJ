#include <iostream>
#include <vector>
#include <numeric>
using namespace std;

int main(){
    cout << fixed;
    cout.precision(3);
    int a, b, num;

    float avg;
    cin >> a;
    while (a--){
        float count = 0;
        int sum = 0;
        cin >> b;
        vector<int> v;
        while (b--){
            cin >> num;
            v.push_back(num);
            sum += num;
        }
        for (int i = 0; i < v.size(); i++){
            if (v[i] > (static_cast<float>(sum) / v.size()))   count++;
        }
        cout << static_cast<float>(count) * 100 / v.size() << "%" << endl;
    }
    vector<int> v;
    return 0;
}
