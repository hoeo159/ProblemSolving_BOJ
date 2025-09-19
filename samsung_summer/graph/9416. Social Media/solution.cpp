#include <bits/stdc++.h>

using namespace std;

#define MAX_USER 1001
#define MAX_POST 1001

// 1. 게시된 지 1,000 초 이내인 게시글이 그렇지 않은 게시글보다 우선순위가 높다.
// 2. 게시된 지 1,000 초 이내인 게시글들 중에는 “like” 가 많은 게시글의 우선순위가 높다.
// 3. 게시된 지 1,000 초 이내이면서 “like” 의 개수가 같은 게시글들 중에는 “timestamp” 가 높은 게시글의 우선순위가 높다.
// 4. 게시된 지 1,000 초를 초과한 게시글의 경우, “timestamp” 가 높은 게시글의 우선순위가 높다.

int curTimestamp;

struct Post
{
    int pid;
    int timestamp;
    int like;
    int uid;
};

struct RecentPost
{
    int pid;
    int like;
    int timestamp;

    bool operator<(const RecentPost &other) const
    {
        if(like != other.like)
            return like < other.like;
        return timestamp < other.timestamp;
    }
};

struct OldPost
{
    int pid;
    int timestamp;

    bool operator<(const OldPost &other) const
    {
        return timestamp < other.timestamp;
    }
};

struct FeedPost
{
    int pid;
    int like;
    int postTimeStamp;
    bool operator<(const FeedPost &other) const
    {
        bool curRecent = (curTimestamp - postTimeStamp <= 1000);
        bool otherRecent = (curTimestamp - other.postTimeStamp <= 1000);

        if(curRecent && otherRecent)
        {
            if(like != other.like)
                return like < other.like;
            return postTimeStamp < other.postTimeStamp;
        }
        else if(curRecent || otherRecent)
        {
            return !curRecent;
        }
        else
        {
            return postTimeStamp < other.postTimeStamp;
        }
    }
};

struct User
{
    int postCnt;
    int followeeCnt;
    vector<Post> posts;
    vector<int> followee;

    vector<RecentPost> recentHeap;
    vector<OldPost> oldHeap;
};

// index가 pid와 uid
vector<User> user;
vector<Post> post;

void updatePQ(int uID, int current_timestamp)
{
    user[uID].recentHeap.clear();
    user[uID].oldHeap.clear();

    for(auto &p : user[uID].posts)
    {
        int elapsed = current_timestamp - p.timestamp;
        if(elapsed <= 1000)
        {
            user[uID].recentHeap.push_back({p.pid, p.like, p.timestamp});
        }
        else
        {
            user[uID].oldHeap.push_back({p.pid, p.timestamp});
        }
    }

    std::make_heap(user[uID].recentHeap.begin(), user[uID].recentHeap.end());
    std::make_heap(user[uID].oldHeap.begin(), user[uID].oldHeap.end());
}

void init(int N)
{
    post.clear();
    post.resize(MAX_POST);

    user.clear();
    user.resize(N + 1);
    for(int i = 1; i <= N; i++)
    {
        user[i].postCnt = 0;
        user[i].followeeCnt = 0;
        user[i].posts.clear();
        user[i].followee.clear();
        user[i].recentHeap.clear();
        user[i].oldHeap.clear();
    }
}

void follow(int uID1, int uID2, int timestamp)
{
    curTimestamp = timestamp;

    if(find(user[uID1].followee.begin(), user[uID1].followee.end(), uID2) == user[uID1].followee.end())
    {
        user[uID1].followee.push_back(uID2);
        user[uID2].followeeCnt++;
    }
}

void makePost(int uID, int pID, int timestamp)
{
    curTimestamp = timestamp;

    Post newPost = {pID, timestamp, 0, uID};
    user[uID].posts.push_back(newPost);
    user[uID].postCnt++;
    post[pID] = newPost;

    RecentPost recentPost = {pID, 0, timestamp};
    user[uID].recentHeap.push_back(recentPost);
}

void like(int pID, int timestamp)
{
    curTimestamp = timestamp;

    post[pID].like++;
    int uID = post[pID].uid;
    updatePQ(uID, timestamp);
}

void getFeed(int uID, int timestamp, int pIDList[])
{
    curTimestamp = timestamp;

    updatePQ(uID, timestamp);
    priority_queue<FeedPost> feedPQ;

    for(const auto &p : user[uID].recentHeap)
    {
        feedPQ.push({p.pid, p.like, p.timestamp});
    }
    for(const auto &p : user[uID].oldHeap)
    {
        feedPQ.push({p.pid, 0, p.timestamp});
    }

    // followee 게시글 추가
    for(auto f : user[uID].followee)
    {
        updatePQ(f, timestamp);
        for(const auto &p : user[f].recentHeap)
        {
            feedPQ.push({p.pid, p.like, p.timestamp});
        }
        for(const auto &p : user[f].oldHeap)
        {
            feedPQ.push({p.pid, 0, p.timestamp});
        }
    }

    int idx = 0;
    while(!feedPQ.empty() && idx < 10)
    {
        pIDList[idx++] = feedPQ.top().pid;
        feedPQ.pop();
    }

    while(idx < 10)
    {
        pIDList[idx++] = 0;
    }
}