#include<iostream>
#include <vector>

using namespace std;

class MaxHeap
{
    static constexpr size_t MAX_SIZE = 100000;
    int data[MAX_SIZE + 1];
    size_t size = 0;
public:
    MaxHeap() = default;
    void swap(int &a, int &b);
    void push(int x);
    void pop();
    int top() const;
};

void MaxHeap::swap(int &a, int &b)
{
    int temp = a;
    a = b;
    b = temp;
}

void MaxHeap::push(int x)
{
    data[++size] = x;

    int index = size;
    int parent = (index / 2);

    while(parent != 0 && data[index] > data[parent])
    {
        swap(data[index], data[parent]);

        index = parent;
        parent = (index / 2);
    }
}

void MaxHeap::pop()
{
    if(size == 0)
    {
        cout << "Heap is empty" << endl;
        return;
    }

    data[1] = data[size--];

    int parent = 1;
    int large = parent;
    int left = (parent * 2);
    int right = (parent * 2 + 1);

    while(true)
    {
        if(left <= size && data[left] > data[large])
            large = left;
        if(right <= size && data[right] > data[large])
            large = right;
        if(large == parent)
            break;
        swap(data[parent], data[large]);

        parent = large;

        left = (parent * 2);
        right = (parent * 2 + 1);
    }
}

int MaxHeap::top() const
{
    if(size == 0)
    {
        return -1;
    }
    return data[1];
}


int main(int argc, char** argv)
{
	int test_case;
	int T;
	// freopen("input.txt", "r", stdin);
	cin>>T;
	for(test_case = 1; test_case <= T; ++test_case)
	{
        int N;
        cin >> N;
        MaxHeap heap;
        vector<int> ret;

        for(int i = 0; i < N; i++)
        {
            int command;
            cin >> command;
            if(command == 1)
            {
                int num;
                cin >> num;
                heap.push(num);
            }
            else if(command == 2)
            {
                int num = heap.top();
                ret.push_back(num);
                if(num != -1)
                    heap.pop();
            }
        }

        cout << "#" << test_case << " ";
        for(auto &i : ret)
        {
            cout << i << " ";
        }
        cout << endl;
	}
	return 0;//정상종료시 반드시 0을 리턴해야합니다.
}