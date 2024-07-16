#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <map>

using namespace std;

typedef vector<vector<int>> vvi;

const int MAX = numeric_limits<int>::max();

int incr(int d)
{
    return (d > 0) ? d + 1 : d - 1;
}

int sgn(int x)
{
    if (!x)
        return 0;
    return x > 0 ? 1 : -1;
}

// start부터 end까지 도달하는데 드는 최소 거리 return
int bfs(vvi &start, vvi &end)
{
    if (start == end)
        return 0;

    map<vvi, int> distance;
    queue<vvi> q;

    distance[start] = 1;
    q.push(start);
    distance[end] = -1;
    q.push(end);

    while (!q.empty())
    {
        vvi here = q.front();
        q.pop();

        for (int i = 0; i < here.size(); ++i)
            for (int j = 0; j < here.size(); ++j)
            {
                if (i == j)
                    continue;

                int xi = (here[i].empty()) ? MAX : here[i].back();
                int xj = (here[j].empty()) ? MAX : here[j].back();

                if ((xi < xj) || (!here[i].empty() && here[j].empty()))
                {
                    vvi there = here;

                    int x = there[i].back();
                    there[i].pop_back();
                    there[j].push_back(x);

                    if (distance.count(there) == 0)
                    {
                        distance[there] = incr(distance[here]);
                        q.push(there);
                    }
                    else if (sgn(distance[here]) != sgn(distance[there]))
                        return abs(distance[here]) + abs(distance[there]) - 1;
                }
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

        vvi start(4, vector<int>());
        for (int i = 0; i < 4; ++i)
        {
            int m;
            cin >> m;
            for (int j = 0; j < m; ++j)
            {
                int d;
                cin >> d;
                start[i].push_back(d);
            }
        }

        vvi end(4, vector<int>());
        for (int i = 0; i < 4; ++i)
        {
            int m;
            cin >> m;
            for (int j = 0; j < m; ++j)
            {
                int d;
                cin >> d;
                end[i].push_back(d);
            }
        }

        cout << bfs(start, end) << endl;
    }

    return 0;
}