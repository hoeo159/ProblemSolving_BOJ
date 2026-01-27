#include <unordered_map>
#include <queue>
#include <vector>
#include <string>
#include <cstring>
#include <algorithm>

// locname ex) "A001", "B002" ...

struct RESULT_E
{
    int success;
    char locname[5];
};

struct RESULT_S
{
    int cnt;
    char carlist[5][8];
};

struct ParkInfo
{
    char locname[5];
    int parkedTime;
    bool isTowed = false; // 이건 견인
    bool isPullOut = false; // 이건 정상 출차
};

struct TowSelection
{
    int towTime;
    char carId[8];

    bool operator>(const TowSelection &other) const
    {
        return towTime > other.towTime;
    }
};

std::priority_queue<int, std::vector<int>, std::greater<int>> freeSlotQueue[26]; // 구역 인덱스 작은 게 우선
std::priority_queue<TowSelection, std::vector<TowSelection>, std::greater<TowSelection>> towSelectionQueue; // 이것도 최소힙 시간 작은 게 우선
int freeSlotCount[26]; // 구역 별 남은 주차 많은 게 우선, 그 뒤가 사전 순
int N, M, L;
std::unordered_map<std::string, ParkInfo> carParkingInfo; // car id -> parking info

int alphaToInt(char input)
{
    return input - 'A';
}

char locnameToAlpha(const char locname[])
{
    return locname[0];
}

int locnameToIndex(const char locname[])
{
    return (locname[1] - '0') * 100 + (locname[2] - '0') * 10 + (locname[3] - '0');
}

std::string indexToLocname(int slot, int index)
{
    char retLocname[5];
    retLocname[0] = 'A' + slot;
    retLocname[1] = (index / 100) + '0';
    retLocname[2] = ((index / 10) % 10) + '0';
    retLocname[3] = (index % 10) + '0';
    retLocname[4] = '\0';
    return std::string(retLocname);
}


void init(int _N, int _M, int _L)
{
    N = _N;
    M = _M;
    L = _L;
    carParkingInfo.clear();

    while(!towSelectionQueue.empty())
    {
        towSelectionQueue.pop();
    }

    for(int i = 0; i < 26; i++)
    {
        while(!freeSlotQueue[i].empty())
        {
            freeSlotQueue[i].pop();
        }
        freeSlotCount[i] = 0;
    }

    for(int i = 0; i < N; i++)
    {
        freeSlotCount[i] = M;
        for(int j = 0; j < M; j++)
        {
            freeSlotQueue[i].push(j);
        }
    }

    return;
}

void updateTowing(int mtime)
{
    while(!towSelectionQueue.empty())
    {
        TowSelection cur = towSelectionQueue.top();
        if(cur.towTime > mtime)  break;
        
        towSelectionQueue.pop();

        auto iter = carParkingInfo.find(cur.carId);
        if(iter == carParkingInfo.end()) continue;

        ParkInfo &pinfo = iter->second;
        if(pinfo.isPullOut || pinfo.isTowed)    continue;
        if(pinfo.parkedTime + L != cur.towTime) continue;

        pinfo.isTowed = true;

        int slot = alphaToInt(locnameToAlpha(pinfo.locname));
        int index = locnameToIndex(pinfo.locname);

        freeSlotQueue[slot].push(index);
        freeSlotCount[slot]++;
    }
}

void outOfTowList(int mtime, char carId[])
{
    auto iter = carParkingInfo.find(carId);
    if(iter == carParkingInfo.end()) return;

    ParkInfo &pinfo = iter->second;
    if(pinfo.isTowed)
    {
        carParkingInfo.erase(iter);
    }
}

int findParkingSlot(int *slot, int *index)
{
    int maxCnt = 0, bestSlot = -1;
    for(int i = 0; i < N; i++)
    {
        if(freeSlotCount[i] > maxCnt)
        {
            maxCnt = freeSlotCount[i];
            bestSlot = i;
        }
    }

    if(bestSlot == -1)  return -1;

    *slot = bestSlot;
    *index = freeSlotQueue[bestSlot].top();

    return 1;
}

RESULT_E enter(int mTime, char mCarNo[])
{
    RESULT_E res_e;

    char carId[8];
    strcpy(carId, mCarNo);

    updateTowing(mTime);
    outOfTowList(mTime, carId);

    int slot, index;
    int ret = findParkingSlot(&slot, &index);
    if(ret == -1)
    {
        res_e.success = 0;
        return res_e;
    }
    freeSlotQueue[slot].pop();
    freeSlotCount[slot]--;

    std::string locname = indexToLocname(slot, index);
    strcpy(res_e.locname, locname.c_str());
    res_e.success = 1;

    ParkInfo pinfo;
    strcpy(pinfo.locname, res_e.locname);
    pinfo.parkedTime = mTime;
    pinfo.isPullOut = false;
    pinfo.isTowed = false;

    carParkingInfo[carId] = pinfo;

    TowSelection towReservation;
    towReservation.towTime = mTime + L;
    strcpy(towReservation.carId, carId);
    towSelectionQueue.push(towReservation);

    return res_e;
}

int pullout(int mTime, char mCarNo[])
{
    char carId[8];
    strcpy(carId, mCarNo);
    updateTowing(mTime);
    
    auto iter = carParkingInfo.find(carId);
    if(iter == carParkingInfo.end())    return -1;
    ParkInfo &pinfo = iter->second;

    if(!pinfo.isTowed && !pinfo.isPullOut) // 정상 출차
    {
        int parkInterval = mTime - pinfo.parkedTime;
        pinfo.isPullOut = true;
        int slot, index;
        slot = alphaToInt(locnameToAlpha(pinfo.locname));
        index = locnameToIndex(pinfo.locname);
        freeSlotQueue[slot].push(index);
        freeSlotCount[slot]++;

        carParkingInfo.erase(iter);
        return parkInterval;
    }
    else if(pinfo.isTowed) // 이미 견인됨
    {
        int parkInterval = L;
        int towInterval = mTime - (pinfo.parkedTime + L);
        int ret = (parkInterval + towInterval * 5) * (-1);
        pinfo.isTowed = false;

        carParkingInfo.erase(iter);
        return ret;
    }

    return -1;
}

struct Candidate
{
    char carId[8];
    bool isTowed; // 주차 : 0, 견인 : 1

    bool operator<(const Candidate &other) const
    {
        if(isTowed != other.isTowed)
        {
            return isTowed < other.isTowed;
        }
        return strcmp(carId, other.carId) < 0;
    }
};


RESULT_S search(int mTime, char mStr[])
{
    RESULT_S res_s;
    char carId[8];
    strcpy(carId, mStr);
    updateTowing(mTime);
    
    std::vector<Candidate> candidates;
    candidates.clear();
    for(auto iter = carParkingInfo.begin(); iter != carParkingInfo.end(); iter++)
    {
        const char* curCarId = iter->first.c_str();
        ParkInfo &pinfo = iter->second;
        if(pinfo.isPullOut && !pinfo.isTowed)  continue;

        if(strcmp(&curCarId[3], carId) == 0)
        {
            Candidate curCand;
            strcpy(curCand.carId, curCarId);
            curCand.isTowed = pinfo.isTowed;
            candidates.push_back(curCand);
        }
    }

    std::sort(candidates.begin(), candidates.end());

    int len = (candidates.size() > 5) ? 5 : candidates.size();
    res_s.cnt = len;

    for(int i = 0; i < len; i++)
    {
        strcpy(res_s.carlist[i], candidates[i].carId);
    }

    return res_s;
}