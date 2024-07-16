#include <iostream>
#include <vector>
#include <map>
#include <queue>
#include <algorithm>

using namespace std;

// seq[left, right]에 대해 flip연산한 결과 arr 반환
vector<int> flip(vector<int> seq, int left, int right)
{
    vector<int> arr = seq;

    int mid = (right - left + 1) / 2;
    for (int i = 0; i < mid; ++i)
        swap(arr[left + i], arr[right - i]);

    return arr;
}

int sgn(int x)
{
    if (!x)
        return 0;
    return x > 0 ? 1 : -1;
}

int incr(int x)
{
    if (x < 0)
        return x - 1;
    return x + 1;
}

int bidirectional(vector<int> start, vector<int> end)
{
    map<vector<int>, int> distance;
    queue<vector<int>> q;

    if (start == end)
        return 0;

    q.push(start);
    distance[start] = 1;
    q.push(end);
    distance[end] = -1;

    while (!q.empty())
    {
        vector<int> here = q.front();
        q.pop();

        for (int left = 0; left < here.size(); ++left)
            for (int right = left + 1; right < here.size(); ++right)
            {
                vector<int> there = flip(here, left, right);

                if (distance.count(there) == 0)
                {
                    distance[there] = incr(distance[here]);
                    q.push(there);
                }
                else if (sgn(distance[there]) != sgn(distance[here]))
                    return abs(distance[there]) + abs(distance[here]) - 1;
            }
    }

    return -1;
}

int main()
{
    int c;
    cin >> c;

    while (c--)
    {
        int n;
        cin >> n;

        vector<int> original(n);
        for (int i = 0; i < n; ++i)
            cin >> original[i];

        vector<int> sorted(original);
        sort(sorted.begin(), sorted.end());

        cout << bidirectional(original, sorted) << endl;
    }

    return 0;
}