#include <string>
#include <vector>
#include <deque>
#include <algorithm>
#include <unordered_map>
#include <cstring>

const int MAX_USER = 5000;
const int MAX_GROUP = 500; 
const int MAX_TEXT_LEN = 9;

struct Message
{
    int groupID;
    char text[MAX_TEXT_LEN + 1];
};

struct User
{
    std::vector<Message> messages;
};

std::vector<User> users;
int user_count = 0;
// static std::unordered_map<int, std::vector<int>> group_users;
// static std::unordered_map<int, std::vector<bool>> group_on_off;
std::vector<int> group_users[MAX_GROUP + 1];
std::vector<bool> group_on_off[MAX_GROUP + 1];

void init(int N)
{
    user_count = N;
    
    users.clear();
    users.resize(N + 1);

    for(int i = 1; i <= MAX_GROUP; i++)
    {
        group_users[i].clear();
        group_on_off[i].clear();
        group_on_off[i].assign(N + 1, false);
    }

    return;
}

void createGroup(int groupID, int mNum, int uIDs[])
{
    auto& user = group_users[groupID];
    auto& on_off = group_on_off[groupID];

    user.assign(uIDs, uIDs + mNum);
    for(int i = 0; i < mNum; i++)
    {
        int uID = uIDs[i];
        on_off[uID] = true;
    }

    return;
}

int sendMessage(int uID, int groupID, char mText[])
{
    int ret = 0;

    auto& group = group_users[groupID];
    auto& on_off = group_on_off[groupID];

    for(auto reciever : group)
    {
        if(reciever == uID)
            continue;
        if(!on_off[reciever])
            continue;
        Message msg;
        msg.groupID = groupID;
        std::strncpy(msg.text, mText, MAX_TEXT_LEN);
        msg.text[MAX_TEXT_LEN] = '\0';
        users[reciever].messages.push_back(msg);
        ret++;
    }

    return ret;
}

void setOnOff(int uID, int groupID)
{
    auto& on_off = group_on_off[groupID];
    on_off[uID] = !on_off[uID];
    auto& message_box = users[uID].messages;

    int recount = 0;
    int msg_size = static_cast<int>(message_box.size());
    for(int i = 0; i < msg_size; i++)
    {
        if(message_box[i].groupID != groupID || on_off[uID])
        {
            message_box[recount++] = message_box[i];
        }
    }
    message_box.resize(recount);

    return;    
}

int checkMsg(int uID, char mMsg[])
{
    auto& message_box = users[uID].messages;

    int msg_count = static_cast<int>(message_box.size());
    if(msg_count == 0)
        return 0;
    std::strcpy(mMsg, message_box.back().text);
    message_box.clear();
    return msg_count;
}