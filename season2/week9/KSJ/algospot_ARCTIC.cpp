#include <iostream>
#include <vector>
#include <utility>
#include <cstdio>
#include <cmath>
#include <queue>

using namespace std;

const int N = 100;
int n;

vector<pair<double, double>> locations;
double dist[N][N];

// 무전기의 출력 반경이 r일 때, n개의 모든 기지가 직.간접적으로 통신가능한가
bool canCommunicate(double r)
{
    queue<int> q;
    vector<bool> visited(n, false);

    q.push(0);
    visited[0] = true;

    int nCamp = 0;
    while (!q.empty())
    {
        int pos = q.front();
        q.pop();

        for (int next = 0; next < n; ++next)
            if (next != pos && !visited[next] && dist[pos][next] <= r)
            {
                q.push(next);
                visited[next] = true;
            }

        nCamp++;
    }

    return n == nCamp;
}

// n개의 모든 기지가 직.간접적으로 통신가능한 무전기의 최소 출력 반경 반환
double solve()
{
    // 무전기의 출력 범위 = [lo, hi)
    double lo = 0, hi = ceil(1000 * sqrt(2)) + 1;
    int nIter = 100; // 100번 반복시 오차는 항상 10^(-7)보다 작음

    for (int i = 0; i < nIter; ++i)
    {
        double mid = (lo + hi) / 2;

        if (canCommunicate(mid))
            hi = mid;
        else
            lo = mid;
    }

    return lo;
}

int main()
{
    int c;
    cin >> c;

    while (c--)
    {
        cin >> n;

        locations.clear();
        for (int i = 0; i < n; ++i)
        {
            double x, y;
            cin >> x >> y;

            locations.push_back(make_pair(x, y));
        }

        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n; ++j)
                if (i != j)
                {
                    double xi = locations[i].first, xj = locations[j].first;
                    double yi = locations[i].second, yj = locations[j].second;

                    dist[i][j] = sqrt(pow(xi - xj, 2) + pow(yi - yj, 2));
                }

        printf("%.2f\n", solve());
    }

    return 0;
}