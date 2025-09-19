#include <cstring>
#include <vector>

#define MAX_NODE 1000000

struct TrieNode
{
    int child[26];
    int count; // node를 거쳐가는 단어의 개수
    int isEnd;
};

std::vector<TrieNode> trie;
int root[30];
int nodeCount = 31;

void init() {
    trie.clear();
    trie.resize(MAX_NODE + 1);

    for(int i = 1; i <= 30; i++)
    {
        TrieNode rootNode;
        memset(rootNode.child, -1, sizeof(rootNode.child));
        rootNode.count = 0;
        rootNode.isEnd = 0;
        trie[i] = rootNode;
    }

    for(int i = 0; i <= 30; i++) {
        root[i] = i;
    }

    nodeCount = 31;
    return;
}

int add(char str[]) {
    int len = strlen(str);
    int pos = root[len];
    trie[pos].count++; // 해당 길이 단어 개수 나타냄

    for(int i = 0; i < len; i++)
    {
        int charIdx = str[i] - 'a';
        // no nxt node, generate node
        if(trie[pos].child[charIdx] == -1) {
            trie[pos].child[charIdx] = nodeCount;
            
            TrieNode newNode;
            memset(newNode.child, -1, sizeof(newNode.child));
            newNode.count = 0;
            newNode.isEnd = 0;
            trie[nodeCount] = newNode;

            nodeCount++;
        }

        pos = trie[pos].child[charIdx];
        trie[pos].count++;
    }

    // 단어 끝
    trie[pos].isEnd++;

	return trie[pos].isEnd;
}

// remove dfs
int dfs2(int pos, int idx, char* str, int len)
{
    if(pos == -1) return 0;
    // leaf node
    if(idx == len)
    {
        int ret = trie[pos].isEnd;
        if(ret > 0)
        {
            trie[pos].count -= ret;
        }
        trie[pos].isEnd = 0;
        return ret;
    }

    int ret = 0;
    if(str[idx] == '?')
    {
        for(int i = 0; i < 26; i++)
        {
            int nxtId = trie[pos].child[i];
            ret += dfs2(nxtId, idx + 1, str, len);
        }
    }
    else
    {
        int charIdx = str[idx] - 'a';
        int nxtId = trie[pos].child[charIdx];

        if(nxtId == -1) return 0;

        ret = dfs2(nxtId, idx + 1, str, len);
    }

    trie[pos].count -= ret;

    return ret;
}

int remove(char str[]) {
    int len = strlen(str);
    int pos = root[len];

    int ret = dfs2(pos, 0, str, len);
	return ret;
}

int dfs(int pos, int idx, char* str, int len)
{
    if(pos == -1) return 0;
    if(idx == len)  return trie[pos].isEnd;

    int ret = 0;

    if(str[idx] == '?')
    {
        for(int i = 0; i < 26; i++)
        {
            if(trie[pos].child[i] != -1)
            {
                int nxtId = trie[pos].child[i];
                ret += dfs(nxtId, idx + 1, str, len);
            }
        }
    } 
    else
    {
        int charIdx = str[idx] - 'a';
        int nxtId = trie[pos].child[charIdx];

        if(nxtId == -1) return 0;

        ret = dfs(nxtId, idx + 1, str, len);
    }
    return ret;
}

int search(char str[]) {
    int len = strlen(str);
    int pos = root[len];

    int ret = dfs(pos, 0, str, len);
	return ret;
}