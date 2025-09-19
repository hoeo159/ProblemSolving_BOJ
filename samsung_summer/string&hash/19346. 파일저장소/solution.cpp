#include <map>
#include <unordered_map>
#include <set>
#include <unordered_set>
#include <algorithm>
#include <cmath>
#include <vector>
// key: start, value: end
std::map<int, int> freeSegment; 
// key: start, value : <end, id>
std::map<int, std::pair<int, int>> usedSegment; 
// key: id, value : <start, end> list
std::unordered_map<int, std::vector<std::pair<int, int>>> files;  

void addFreeSegment(int start, int end)
{
    int len = end - start + 1;
    auto it = freeSegment.lower_bound(start); // start 이상인 첫 번째 구간
    if(it != freeSegment.begin())
    {
        auto pit = std::prev(it); // {10, 20}, {30, 40}에서 {21, 29} 넣을 때 {10, 20} 확인
        int pstart = pit->first;
        int pend = pit->second;
        int plen = pend - pstart + 1;
        if(pend + 1 == start) // 앞 구간과 연결 가능
        {
            start = pstart;
            len += plen;
            freeSegment.erase(pit);
        }
    }

    it = freeSegment.lower_bound(start); // 뒤 구간이니까 그대로 써도 됨
    if(it != freeSegment.end())
    {
        int nstart = it->first;
        int nend = it->second;
        int nlen = nend - nstart + 1;
        if(end + 1 == nstart) // 뒤 구간과 연결 가능
        {
            end = nend;
            len += nlen;
            freeSegment.erase(it);
        }
    }

    freeSegment[start] = end;
}

void init(int N) {
    freeSegment.clear();
    usedSegment.clear();
    files.clear();
    freeSegment[1] = N;
	return;
}

int add(int mId, int mSize) {
    int size = mSize;
    std::vector<std::pair<int, int>> allocated;
    auto it = freeSegment.begin();
    while(it != freeSegment.end() && size > 0)
    {
        int start = it->first;
        int end = it->second;
        int length = end - start + 1; // 점유할 수 있는 길이
        int take = std::min(size, length); // 실제로 가져갈 길이
        allocated.push_back({start, start + take - 1});
        if(length > take) // 일부 점유, 남는 공간이 있음
        {
            int nxtStart = start + take;
            int nxtEnd = end;
            freeSegment.erase(it++);
            freeSegment[nxtStart] = nxtEnd;
        }
        else // 점부 점유해서 남는 공간 없음
        {
            freeSegment.erase(it++);
        }
        size -= take;
    }

    if(size > 0) // 공간 부족
    {
        for(auto& p : allocated) // 다시 해제
        {
            int start = p.first;
            int end = p.second;
            addFreeSegment(start, end);
        }
        return -1;
    }

    for(auto& p : allocated) // 사용 구간에 추가
    {
        int start = p.first;
        int end = p.second;
        usedSegment[start] = {end, mId};
    }

    files[mId] = allocated; // 파일에 구간 추가

    if(allocated.empty()) return -1;
    return allocated.front().first; // 파일의 시작 위치 반환
}

int remove(int mId) {
    auto iter = files.find(mId);
    if(iter == files.end()) return 0; // 해당 id 파일 없음
    auto &segments = iter->second;
    int count = segments.size();
    for(auto &p : segments)
    {
        int start = p.first;
        int end = p.second;
        usedSegment.erase(start);
        addFreeSegment(start, end);
    }
    files.erase(iter);
	return count;
}

int count(int mStart, int mEnd) {
    
    // std::set<int> countedIds;
    std::unordered_set<int> countedIds;

    auto iter = usedSegment.lower_bound(mStart);
    if(iter != usedSegment.begin())
        iter = std::prev(iter);

    while(iter != usedSegment.end())
    {
        int segStart = iter->first;
        int segEnd = iter->second.first;
        int fileId = iter->second.second;
        if(segStart > mEnd) break;

        if(segEnd >= mStart)
            countedIds.insert(fileId);

        iter++;
    }

    return countedIds.size();
}