#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;

unordered_map<string, int> genre_count;
unordered_map<string, vector<pair<int, int>>> genre_song;
vector<pair<int, string>> sorting_genre;
int N;

vector<int> solution(vector<string> genres, vector<int> plays) {
    vector<int> answer;
    N = genres.size();
    for(int i = 0; i < N; i++)
    {
        string cur = genres[i];
        genre_count[cur] += plays[i];
        genre_song[cur].push_back({plays[i], i});
    }
    for(auto i : genre_count)
    {
        sorting_genre.push_back({i.second, i.first});
    }
    
    sort(sorting_genre.begin(), sorting_genre.end(), greater<pair<int, string>>());
    
    for(auto i : sorting_genre)
    {
        string cur = i.second;
        sort(genre_song[cur].begin(), genre_song[cur].end(), [](auto& a, auto& b){
            if(a.first == b.first)  return a.second < b.second;
            return a.first > b.first;
        });
        int len = genre_song[cur].size();
        int last = len >= 2 ? 2 : len;
        for(int j = 0; j < last; j++)
        {
            answer.push_back(genre_song[cur][j].second);
        }
    }
    
    return answer;
}