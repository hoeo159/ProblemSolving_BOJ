#include <vector>
#include <algorithm>
#include <cstdio>
#include <cmath>

#define HASH 19
#define TABLE_SIZE HASH * HASH * HASH * HASH

int hashTable[TABLE_SIZE + 1];

std::vector<int> wall;

int getHash(int d1, int d2, int d3, int d4)
{
    int hash = 0;
    int offset = (int)HASH / 2;
    hash = (hash * HASH) + (d1 + offset);
    hash = (hash * HASH) + (d2 + offset);
    hash = (hash * HASH) + (d3 + offset);
    hash = (hash * HASH) + (d4 + offset);
    return hash;
}

void init()
{
	wall.clear();
    for(int i = 0; i < TABLE_SIZE; i++)
    {
        hashTable[i] = 0;
    }
}

void makeWall(int mHeights[5])
{
    int oldSize = wall.size();
    for(int i = 0; i < 5; i++)
    {
        wall.push_back(mHeights[i]);
    }
    int start = ((oldSize - 4) > 0) ? (oldSize - 4) : 0;
    int end = oldSize;
    for(int i = start; i <= end; i++){
        int d1 = wall[i + 1] - wall[i];
        int d2 = wall[i + 2] - wall[i + 1];
        int d3 = wall[i + 3] - wall[i + 2];
        int d4 = wall[i + 4] - wall[i + 3];
        int hash = getHash(d1, d2, d3, d4);
        hashTable[hash]++;
    }
}

void removeWall(int index)
{
    int start = std::max(0, index - 4);
    int end = std::min((int)wall.size() - 5, index);

    for (int i = start; i <= end; i++) {
        int d1 = wall[i + 1] - wall[i];
        int d2 = wall[i + 2] - wall[i + 1];
        int d3 = wall[i + 3] - wall[i + 2];
        int d4 = wall[i + 4] - wall[i + 3];
        int hash = getHash(d1, d2, d3, d4);
        hashTable[hash]--;
    }

    wall.erase(wall.begin() + index, wall.begin() + index + 5);

    if (wall.size() >= 5) {
        end = std::min((int)wall.size() - 4, index -1);
        for (int i = start; i <= end; i++) {
             int d1 = wall[i + 1] - wall[i];
             int d2 = wall[i + 2] - wall[i + 1];
             int d3 = wall[i + 3] - wall[i + 2];
             int d4 = wall[i + 4] - wall[i + 3];
             int hash = getHash(d1, d2, d3, d4);
             hashTable[hash]++;
        }
    }
}

int matchPiece(int mHeights[5])
{
    int blockHash = getHash(mHeights[4] - mHeights[3], 
        mHeights[3] - mHeights[2], mHeights[2] - mHeights[1], mHeights[1] - mHeights[0]);

    if(hashTable[blockHash] == 0) return -1;

    int start = wall.size() - 5;
    int ret = -1;

    for(int i = start; i >= 0; i--){
        int d1 = wall[i + 1] - wall[i];
        int d2 = wall[i + 2] - wall[i + 1];
        int d3 = wall[i + 3] - wall[i + 2];
        int d4 = wall[i + 4] - wall[i + 3];
        int wallHash = getHash(d1, d2, d3, d4);

        // printf("%d %d %d %d %d / %d %d %d %d / %d : %d\n",
        //      wall[i], wall[i + 1], wall[i + 2], wall[i + 3], wall[i + 4],
        //      d1, d2, d3, d4, i, wallHash);

        if(blockHash == wallHash)
        {
            removeWall(i);
            return i + 1;
        }

    }
    
    return -1;
}

// void printInfo(int mHeights[5])
// {
//     printf("Current Wall State(%ld): ", wall.size());
//     for (int h : wall) {
//         printf("%d ", h);
//     }
//     printf("\n");

//     int revBlock[5];
//     for(int i = 0; i < 5; i++){
//         revBlock[i] = mHeights[4 - i];
//     }
//     std::vector<int> blockDiff;
//     for (int i = 0; i < 4; i++) {
//         blockDiff.push_back(revBlock[i] - revBlock[i + 1]);
//     }

//     printf("Current Piece State: ");
//     for (int r : revBlock) {
//         printf("%d ", r);
//     }
//     printf("\n");

//     return;
// }