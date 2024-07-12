#include <iostream>
#include <queue>
#include <vector>

using namespace std;

int join(const vector<int> &lengths)
{
    int ret = 0;

    priority_queue<int> pq;
    for (int length : lengths)
        pq.push(-length);

    while (pq.size() > 1)
    {
        int min1st = -pq.top();
        pq.pop();
        int min2nd = -pq.top();
        pq.pop();
        int sum = min1st + min2nd;
        ret += sum;

        pq.push(-sum);
    }

    return ret;
}

int main()
{
    int c;
    cin >> c;

    while (c--)
    {
        int n;
        cin >> n;

        vector<int> lengths(n);
        for (int i = 0; i < n; ++i)
            cin >> lengths[i];

        if (n > 1)
            cout << join(lengths) << endl;
        else
            cout << lengths[0] << endl;
    }

    return 0;
}