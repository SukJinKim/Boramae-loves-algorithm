#include <cstdio>
#include <iostream>
#include <vector>
#include <queue>
#include <utility>
#include <limits>

using namespace std;

const int MAX_V = 10000;
const double INF = numeric_limits<double>::infinity();

// (연결된 정점 번호, 가중치) 저장
vector<pair<int, double>> adj[MAX_V];

vector<double> dijkstra(int src, int V)
{
    vector<double> dist(V, INF);
    dist[src] = 1.0;

    // (src까지의 거리, 정점 번호) 저장
    priority_queue<pair<double, int>> pq;
    pq.push(make_pair(-dist[src], src));

    while (!pq.empty())
    {
        double cost = -pq.top().first;
        int here = pq.top().second;
        pq.pop();

        if (dist[here] < cost)
            continue;

        for (int i = 0; i < adj[here].size(); ++i)
        {
            int there = adj[here][i].first;
            double nextDist = cost * adj[here][i].second;

            if (dist[there] > nextDist)
            {
                dist[there] = nextDist;
                pq.push(make_pair(-nextDist, there));
            }
        }
    }

    return dist;
}

int main()
{
    int c;
    cin >> c;

    while (c--)
    {
        int n, m;
        cin >> n >> m;

        for (int i = 0; i < m; ++i)
        {
            int a, b;
            double c;
            cin >> a >> b >> c;

            adj[a].push_back(make_pair(b, c));
            adj[b].push_back(make_pair(a, c));
        }

        vector<double> dist = dijkstra(0, n);

        printf("%.10lf\n", dist[n - 1]);

        for (int i = 0; i < n; ++i)
            adj[i].clear();
    }

    return 0;
}