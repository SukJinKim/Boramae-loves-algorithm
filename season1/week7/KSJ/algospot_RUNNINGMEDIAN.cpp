#include <functional>
#include <iostream>
#include <queue>

using namespace std;

int main()
{
    int C;
    cin >> C;

    while (C--)
    {
        int N, a, b;
        cin >> N >> a >> b;

        priority_queue<int, vector<int>, less<int>> maxHeap;
        priority_queue<int, vector<int>, greater<int>> minHeap;

        int input = 1983, ans = 0;
        for (int i = 0; i < N; ++i)
        {
            if (i > 0)
                input = ((input * (long long)a) + b) % 20090711;

            // 불변식 1 : (최대힙의 크기) >= (최소힙의 크기)
            if (maxHeap.size() == minHeap.size())
                maxHeap.push(input);
            else
                minHeap.push(input);

            // 불변식 2 : maxHeap.top() <= minHeap.top()
            if (!minHeap.empty() && !maxHeap.empty() &&
                minHeap.top() < maxHeap.top())
            {
                int a = maxHeap.top(), b = minHeap.top();
                maxHeap.pop();
                minHeap.pop();
                maxHeap.push(b);
                minHeap.push(a);
            }

            ans = (ans + maxHeap.top()) % 20090711;
        }

        cout << ans << endl;
    }
    return 0;
}