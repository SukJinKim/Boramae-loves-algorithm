#include <vector>
#include <queue>
#include <utility>
#include <iostream>

using namespace std;

int main()
{
    int c;
    cin >> c;

    while (c--)
    {
        priority_queue<pair<int, int>> pq;

        int n;
        cin >> n;

        vector<int> micros(n), eats(n);
        for (int i = 0; i < n; ++i)
            cin >> micros[i];
        for (int i = 0; i < n; ++i)
            cin >> eats[i];
        for (int i = 0; i < n; ++i)
            pq.push(make_pair(eats[i], -micros[i]));

        int eat = pq.top().first;
        int micro = -pq.top().second;
        int lunchTime = micro + eat;
        pq.pop();

        while (!pq.empty())
        {
            int eatNext = pq.top().first;
            int microNext = -pq.top().second;
            pq.pop();

            if (micro + (microNext + eatNext) > lunchTime)
                lunchTime = micro + (microNext + eatNext);

            micro += microNext;
        }

        cout << lunchTime << endl;
    }
    return 0;
}