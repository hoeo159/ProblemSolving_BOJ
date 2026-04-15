#include <iostream>
#include <vector>

using namespace std;

vector<int> inorder;
vector<int> postorder;

int N;

int find(int num)
{
    for (int i = 0; i < N; i++)
    {
        if (inorder[i] == num)
            return i;
    }
}

void preorder(int istart, int iend, int pstart, int pend)
{
    if (istart > iend || pstart > pend)
        return;
    int root = postorder[pend];
    cout << root << " ";
    int index = find(root);
    int leftidx = index - istart;

    preorder(istart, index - 1, pstart, pstart + leftidx - 1);
    preorder(index + 1, iend, pstart + leftidx, pend - 1);
}

int main()
{
    cin >> N;
    inorder.resize(N);
    postorder.resize(N);
    for (int i = 0; i < N; i++)
    {
        cin >> inorder[i];
    }
    for (int i = 0; i < N; i++)
    {
        cin >> postorder[i];
    }

    preorder(0, N - 1, 0, N - 1);
}