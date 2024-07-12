#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// vec[begin + a, begin + b)를 slice하여 return
vector<int> slice(const vector<int> &vec, int a, int b)
{
    return vector<int>(vec.begin() + a, vec.begin() + b);
}

// 주어진 preOrder, inOrder를 만족하는 postOrder 출력
void postOrder(const vector<int> &preOrder, const vector<int> &inOrder)
{
    int n = preOrder.size();
    if (n == 0)
        return;

    int root = preOrder[0];
    int L = find(inOrder.begin(), inOrder.end(), root) - inOrder.begin();

    // left subtree
    postOrder(slice(preOrder, 1, L + 1), slice(inOrder, 0, L));
    // right subtree
    postOrder(slice(preOrder, L + 1, n), slice(inOrder, L + 1, n));

    cout << root << ' ';
}

int main()
{
    int C;
    cin >> C;

    while (C--)
    {
        int N, input;
        cin >> N;

        vector<int> preOrder;
        vector<int> inOrder;

        for (int i = 0; i < N; ++i)
        {
            cin >> input;
            preOrder.push_back(input);
        }
        for (int i = 0; i < N; ++i)
        {
            cin >> input;
            inOrder.push_back(input);
        }

        postOrder(preOrder, inOrder);
    }

    return 0;
}