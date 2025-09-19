// 완전 이진 트리의 중위 순회 코드
#include <iostream>
#include <vector>
#include <string>
#include <cmath>

using namespace std;

typedef struct NODE
{
    char value;

    int left, right;
} Node;

vector<Node> tree;

void inorder(int root, string &ret)
{
    if(root == -1) return;

    inorder(tree[root].left, ret);
    ret += tree[root].value;
    inorder(tree[root].right, ret);

    return;
}

int main(int argc, char** argv)
{
	int test_case;
	int T;

	freopen("input.txt", "r", stdin);
	T = 10;

	for(test_case = 1; test_case <= T; ++test_case)
	{
        int N = 0;
        cin >> N;

        int lastLevel = (int)log2(N);
        tree.clear();
        tree.resize(N + 1);

        for(int i = 0; i < N; i++)
        {
            int curNum = 0, lft = -1, rght = -1;
            char curChar = '\0';
        
            
            if((i + 1) * 2 < N)
            {
                cin >> curNum >> curChar >> lft >> rght;
            }
            else if((i + 1) * 2 == N)
            {
                cin >> curNum >> curChar >> lft;
            }
            else
            {
                cin >> curNum >> curChar;
            }

            tree[curNum].value = curChar;
            tree[curNum].left = lft;
            tree[curNum].right = rght;
        }

        string ret = "";
        inorder(1, ret);
        printf("#%d %s\n", test_case, ret.c_str());
	}
    
	return 0;//정상종료시 반드시 0을 리턴해야합니다.
}