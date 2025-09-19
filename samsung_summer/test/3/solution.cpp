#include <vector>
#include <algorithm>
#include <unordered_set>
#include <unordered_map>
#include <set>

struct RESULT
{
    int cnt;
    int IDs[5];
};

struct Movie
{
    int mid;
    int genre; // 1 ~ 5
    int total_score;
    int add_time;
};

struct User
{
    std::vector<std::pair<int, int>> watched_movies; 
    std::unordered_set<int> check_watched_movies;
};

struct MovieCompare
{
    bool operator()(Movie* a, Movie* b) const
    {
        if(a->total_score != b->total_score)
            return a->total_score > b->total_score;
        return a->add_time > b->add_time;
    }
};

std::unordered_map<int, Movie*> movies;
std::unordered_map<int, User> users;
std::unordered_map<int, std::vector<int>> movie_watcher;
std::set<Movie*, MovieCompare> movie_set;
std::set<Movie*, MovieCompare> movie_set_genre[6]; // 1 ~ 5
int current_tick = 0;

void init(int N)
{
    for(auto &tmp : movies)
    {
        delete tmp.second;
    }
    movies.clear();
    movie_set.clear();
    for(int i = 1; i <= 5; i++)
        movie_set_genre[i].clear();
    movie_watcher.clear();

    current_tick = 0;
    
    users.clear();
    users.reserve(N + 1);
    for(int i = 1; i <= N; i++)
    {
        users[i] = User();
    }
    return;
}

int add(int mID, int mGenre, int mTotal)
{
    if(movies.find(mID) != movies.end())
    {
        return 0;
    }
    Movie* movie = new Movie();
    movie->mid = mID;
    movie->genre = mGenre;
    movie->total_score = mTotal;
    movie->add_time = current_tick++;

    movies[mID] = movie;

    movie_set.insert(movie);
    movie_set_genre[mGenre].insert(movie);
    return 1;
}

int erase(int mID)
{
    auto movie_iter = movies.find(mID);
    if(movie_iter == movies.end())
    {
        return 0;
    }

    Movie* cur_movie = movie_iter->second;
    movie_set.erase(cur_movie);
    movie_set_genre[cur_movie->genre].erase(cur_movie);

    auto user_iter = movie_watcher.find(mID);
    if(user_iter != movie_watcher.end())
    {
        for(int uid : user_iter->second)
        {
            auto& cur = users[uid];
            cur.check_watched_movies.erase(mID);
            auto& cur_vec = cur.watched_movies;
            cur_vec.erase(
                std::remove_if(cur_vec.begin(), cur_vec.end(), 
                [&](auto &p) { return p.first == mID; }),
                cur_vec.end()
            );
        }
        movie_watcher.erase(user_iter);
    }

    movies.erase(movie_iter);
    delete cur_movie;

    return 1;
}

int watch(int uID, int mID, int mRating)
{
    auto movie_iter = movies.find(mID);
    if(movie_iter == movies.end())
    {
        return 0;
    }
    
    User& current_user = users[uID];
    if(current_user.check_watched_movies.find(mID) != current_user.check_watched_movies.end())
    {
        return 0;
    }
    
    Movie* cur_movie = movie_iter->second;
    movie_set.erase(cur_movie);
    movie_set_genre[cur_movie->genre].erase(cur_movie);
    cur_movie->total_score += mRating;
    movie_set.insert(cur_movie);
    movie_set_genre[cur_movie->genre].insert(cur_movie);

    current_user.watched_movies.push_back({mID, mRating});
    current_user.check_watched_movies.insert(mID);
    movie_watcher[mID].push_back(uID);
    return 1;
}

RESULT suggest(int uID)
{
    RESULT res;
    
    res.cnt = 0;

    User& current_user = users[uID];
    auto& user_movie_list = current_user.watched_movies;
    int user_genre = 0;

    int start = std::max(0, (int)user_movie_list.size() - 5);
    int best_score = 0, best_index = 0;
    int user_movie_len = user_movie_list.size();
    for(int i = start; i < user_movie_len; i++)
    {
        auto [movie_id, rating] = user_movie_list[i];
        if(rating > best_score || (rating == best_score && i > best_index))
        {
            best_score = rating;
            best_index = i;
            user_genre = movies[movie_id]->genre;
        }
    }

    auto &set = (user_genre == 0) ? movie_set : movie_set_genre[user_genre];
    for(auto iter = set.begin(); iter != set.end() && res.cnt < 5; iter++)
    {
        Movie* movie = *iter;
        if(current_user.check_watched_movies.count(movie->mid))
            continue;
        res.IDs[res.cnt++] = movie->mid;
    }
    return res;
}