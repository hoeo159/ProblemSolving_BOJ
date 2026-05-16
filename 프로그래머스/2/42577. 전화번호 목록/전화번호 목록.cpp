#include <string>
#include <vector>
#include <unordered_set>

using namespace std;
unordered_set<string> book;
int N;

bool solution(vector<string> phone_book) {
    bool answer = true;
    N = phone_book.size();
    
    for(auto i : phone_book)
    {
        book.insert(i);
    }
    
    for(int i = 0; i < N; i++)
    {
        string cur = phone_book[i];
        int len = cur.size();
        string tmp = "";
        for(int j = 0; j < len - 1; j++)
        {
            tmp += cur[j];
            if(book.count(tmp))
            {
                return false;
            }
        }
    }
    
    return answer;
}