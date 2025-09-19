#define NAME_MAXLEN 6
#define PATH_MAXLEN 1999
#define MAX_CHILD 30

#include <cstring>
#include <vector>

#include <cstdio>

// The below commented functions are for your reference. If you want 
// to use it, uncomment these functions.

int mstrcmp(const char *a, const char *b)
{
	int i;
	for (i = 0; a[i] != '\0'; i++)
	{
		if (a[i] != b[i])
			return a[i] - b[i];
	}
	return a[i] - b[i];
}

int mstrlen(const char *a)
{
	int len = 0;

	while (a[len] != '\0')
		len++;

	return len;
}

void mstrcpy(char *dest, const char *src)
{
	int i = 0;
	while (src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = src[i];
}

typedef struct NODE
{
    char name[7];
    int parent;
    int size;
    int children[MAX_CHILD];
    int childCnt;
} Node;

int dirCnt = 0;
std::vector<Node> dir(50002);

// root는 이름 없고 parent = 0
void init(int n) {
    dirCnt = 1;
    for(int i = 1; i <= n + 1; i++)
    {
        dir[i].name[0] = '\0';
        dir[i].parent = 0;
        dir[i].size = 0;
        dir[i].childCnt = 0;
        memset(dir[i].children, 0, sizeof(dir[i].children));
    }
}

// 예시 "/" 라면 root, /aa/ 라면 aa가 parent, /a/b/c/라면 c가 parent
int findPath(const char* path)
{
    int ret = 1;
    int len = mstrlen(path);
    int tokLen = 0;
    char tok[7];

    for(int i = 0; i < len; i++)
    {
        if(path[i] == '/')
        {
            tok[tokLen] = '\0';
            tokLen = 0;
            // tok 을 기반으로 ret의 자식들 중 tok과 같은 이름을 가진 자식이 있는지 확인
            for(int j = 0; j < dir[ret].childCnt; j++)
            {
                if(mstrcmp(dir[dir[ret].children[j]].name, tok) == 0)
                {
                    ret = dir[ret].children[j];
                    break;
                }
            }
        }
        else
        {
            tok[tokLen++] = path[i];
        }
    }

    return ret;
}

void cmd_mkdir(char path[PATH_MAXLEN + 1], char name[NAME_MAXLEN + 1]) {
    int parentId = findPath(path);

    dirCnt++;
    // children dir에서 parent 추가
    int curId = dirCnt;
    dir[curId].parent = parentId;
    mstrcpy(dir[curId].name, name);

    //parent dir에서 child 추가
    int idx = dir[parentId].childCnt++;
    dir[parentId].children[idx] = curId;

    for(int i = parentId; i !=0; i = dir[i].parent)
    {
        dir[i].size++;
    }
}

int removeDirRecursive(int idx)
{
    int totalRemoveCnt = 1;

    // 하위 dir remove
    for(int i = 0; i < dir[idx].childCnt; i++)
    {
        totalRemoveCnt += removeDirRecursive(dir[idx].children[i]);
    }
    dir[idx].childCnt = 0;
    
    // parent의 child에서 idx 제거
    // int parentId = dir[idx].parent;
    // if(parentId != 0)
    // {
    //     for(int i = 0; i < dir[parentId].childCnt; i++)
    //     {
    //         if(dir[parentId].children[i] == idx)
    //         {
    //             dir[parentId].children[i] = dir[parentId].children[--dir[parentId].childCnt];
    //             break;
    //         }
    //     }

    //     // for(int i = parentId; i != 0; i = dir[i].parent)
    //     // {
    //     //     printf("cur id : %s size : %d ->", dir[i].name, dir[i].size);
    //     //     dir[i].size -= totalRemoveCnt;
    //     //     printf("%d\n", dir[i].size);
    //     // }
    // }

    return totalRemoveCnt;
}

void cmd_rm(char path[PATH_MAXLEN + 1]) {
    int curId = findPath(path);
    int parentId = dir[curId].parent;

    int totalRemoveCnt = removeDirRecursive(curId);

    // parent의 child에서 idx 제거
    if(parentId != 0)
    {
        for(int i = 0; i < dir[parentId].childCnt; i++)
        {
            if(dir[parentId].children[i] == curId)
            {
                dir[parentId].children[i] = dir[parentId].children[--dir[parentId].childCnt];
                break;
            }
        }

        for(int i = parentId; i != 0; i = dir[i].parent)
        {
            dir[i].size -= totalRemoveCnt;
        }
    }
}

// srcId total -> dstParentId 밑으로 cpy
int copyDirRecursive(int srcId, int dstParentId) 
{
    dirCnt++;
    int newId = dirCnt;

    dir[newId].parent = dstParentId;
    mstrcpy(dir[newId].name, dir[srcId].name);
    dir[newId].childCnt = 0;
    dir[newId].size = 0;

    // parent의 child에 추가
    dir[dstParentId].children[dir[dstParentId].childCnt++] = newId;

    int totalSize = 1;
    for(int i = 0; i < dir[srcId].childCnt; i++)
    {
        totalSize += copyDirRecursive(dir[srcId].children[i], newId);
    }

    dir[newId].size = totalSize - 1;
    return totalSize;
}

void cmd_cp(char srcPath[PATH_MAXLEN + 1], char dstPath[PATH_MAXLEN + 1])
{
    int srcId = findPath(srcPath);
    int dstParentId = findPath(dstPath);

    int totalSize = copyDirRecursive(srcId, dstParentId);

    for(int i = dstParentId; i != 0; i = dir[i].parent)
    {
        dir[i].size += totalSize;
    }
}


void cmd_mv(char srcPath[PATH_MAXLEN + 1], char dstPath[PATH_MAXLEN + 1])
{
    int srcId = findPath(srcPath);
    int oldParentId = dir[srcId].parent;
    int dstParentId = findPath(dstPath);

    int totalSize = dir[srcId].size + 1;

    // old parent 제거
    for(int i = 0; i < dir[oldParentId].childCnt; i++)
    {
        if(dir[oldParentId].children[i] == srcId)
        {
            dir[oldParentId].children[i] = dir[oldParentId].children[--dir[oldParentId].childCnt];
            break;
        }
    }
    for(int i = oldParentId; i != 0; i = dir[i].parent)
    {
        dir[i].size -= totalSize;
    }

    // dst parent로 branch만 child로 추가해주기
    dir[dstParentId].children[dir[dstParentId].childCnt++] = srcId;
    dir[srcId].parent = dstParentId;
    for(int i = dstParentId; i != 0; i = dir[i].parent)
    {
        dir[i].size += totalSize;
    }
}


int cmd_find(char path[PATH_MAXLEN + 1]) {
    int curId = findPath(path);
    int ret = dir[curId].size;
	return ret;
}